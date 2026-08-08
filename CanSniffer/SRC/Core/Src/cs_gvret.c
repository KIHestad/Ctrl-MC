#include "cs_gvret.h"
#include "cs_can_rx.h"
#include "main.h"
#include "usbd_cdc_if.h"

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */

/**
 * @brief  Serialise a uint32_t into four bytes, little-endian, and advance
 *         the write pointer by four.
 */
static inline void cs_write_u32_le(uint8_t **p, uint32_t value)
{
    (*p)[0] = (uint8_t)(value);
    (*p)[1] = (uint8_t)(value >>  8U);
    (*p)[2] = (uint8_t)(value >> 16U);
    (*p)[3] = (uint8_t)(value >> 24U);
    *p += 4U;
}

/* --------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

void cs_gvret_encode_frame(const cs_can_frame_t *frame,
                            uint8_t *buf,
                            uint16_t *len)
{
    uint8_t *p = buf;

    /* CAN ID word; set bit 31 for extended (29-bit) frames */
    uint32_t can_id = frame->id;
    if (frame->ide != 0U)
    {
        can_id |= 0x80000000UL;
    }

    if (frame->fdf == 0U)
    {
        /* ---- Classic CAN frame: command 0x00 ----
         * Layout: F1 00 | ts[4] | id[4] | (bus<<4|dlc)[1] | data[dlc]
         * bus is always 0 on this single-bus device. */
        *p++ = 0xF1U;
        *p++ = 0x00U;
        cs_write_u32_le(&p, frame->timestamp);
        cs_write_u32_le(&p, can_id);
        *p++ = (uint8_t)(frame->dlc & 0x0FU); /* high nibble=bus(0), low nibble=dlc */
        for (uint8_t i = 0U; i < frame->dlc; i++)
        {
            *p++ = frame->data[i];
        }
    }
    else
    {
        /* SavvyCAN BUILD_FD_FRAME uses buildData[rx_step-9]; data at rx_step=10 skips index 0.
         * dlc+1 shifts all bytes to valid indices 1..N; two trailing bytes trigger completion.
         * Cap at 62: (62+1)&0x3F=63 is safe; (63+1)&0x3F wraps to 0 and corrupts the stream. */
        uint8_t send_len = (frame->dlc <= 62U) ? frame->dlc : 62U;
        *p++ = 0xF1U;
        *p++ = 0x14U;
        cs_write_u32_le(&p, frame->timestamp);
        cs_write_u32_le(&p, can_id);
        *p++ = (uint8_t)((send_len + 1U) & 0x3FU);
        *p++ = 0x00U; /* bus 0 */
        for (uint8_t i = 0U; i < send_len; i++)
        {
            *p++ = frame->data[i];
        }
        *p++ = 0x00U; /* absorbed mid-loop (OOB write to buildData[N+1]) */
        *p++ = 0x00U; /* triggers BUILD_FD_FRAME else -> frame enqueued */
    }

    *len = (uint16_t)(p - buf);
}

void cs_gvret_process_host_cmd(const uint8_t *in, uint16_t in_len,
                                uint8_t *out,      uint16_t *out_len)
{
    /* Identity string as a static byte literal — avoids strlen at runtime */
    static const uint8_t k_identity[] =
    {
        0xF1U, 0x09U, 0x00U,
        'E', 'V', 'T', 'V', ' ', 'M', 'o', 't', 'o', 'r', 's', ' ',
        'G', 'a', 'r', 'a', 'g', 'e', ' ', 'G', 'V', 'R', 'E', 'T',
        0x00U
    };

    *out_len = 0U;

    /* Scan for 0xF1 start bytes; need at least two bytes for a valid command */
    for (uint16_t i = 0U; (i + 1U) < in_len; i++)
    {
        if (in[i] != 0xF1U)
        {
            continue;
        }

        uint8_t cmd = in[i + 1U];

        if (cmd == 0x00U) /* Transmit CAN frame from host */
        {
            /* Host TX format: F1 00 | ID[4 LE, bit31=ext] | bus[1] | len[1] | data[len] | 0x00
             * No response expected — SavvyCAN ignores replies to cmd 0x00. */
            if ((i + 8U) > in_len) /* need at least: cmd+ID+bus+len */
            {
                break;
            }
            uint8_t tx_len = in[i + 7U];
            if (tx_len > 8U) { tx_len = 8U; } /* clamp to classic CAN */
            if ((i + 8U + (uint16_t)tx_len) > in_len)
            {
                break; /* data bytes not fully in this packet */
            }
            uint32_t raw_id = (uint32_t)in[i + 2U]
                            | ((uint32_t)in[i + 3U] <<  8U)
                            | ((uint32_t)in[i + 4U] << 16U)
                            | ((uint32_t)in[i + 5U] << 24U);
            /* in[i + 6U] = bus number — ignored (single-bus device) */
            bool tx_ide   = (raw_id & 0x80000000U) != 0U;
            uint32_t can_id = tx_ide ? (raw_id & 0x1FFFFFFFU) : (raw_id & 0x7FFU);
            cs_can_tx_send(can_id, tx_ide, tx_len, &in[i + 8U]);
            i += 7U + (uint16_t)tx_len; /* skip: cmd+ID+bus+len+data; loop i++ moves past trailing 0x00 */
        }
        else if (cmd == 0x01U) /* Time sync */
        {
            /* Guard: ensure response fits in the caller's output buffer */
            if ((*out_len + 6U) > CS_GVRET_RESP_BUF_SIZE)
            {
                break;
            }
            uint8_t *p = out + *out_len;
            *p++ = 0xF1U;
            *p++ = 0x01U;
            cs_write_u32_le(&p, HAL_GetTick());
            *out_len += 6U;
            i += 1U; /* skip the command byte so the next iteration advances past it */
        }
        else if (cmd == 0x09U) /* Device identity / comm validation */
        {
            if ((*out_len + (uint16_t)sizeof(k_identity)) > CS_GVRET_RESP_BUF_SIZE)
            {
                break;
            }
            for (uint16_t j = 0U; j < (uint16_t)sizeof(k_identity); j++)
            {
                out[*out_len + j] = k_identity[j];
            }
            *out_len += (uint16_t)sizeof(k_identity);
            i += 1U;
        }
        else if (cmd == 0x06U) /* Report canbus params — triggers SavvyCAN CONNECTED state */
        {
            /* Response: F1 06 | can0_flags[1] | can0_baud[4 LE] | can1_flags[1] | can1_baud[4 LE]
             * can0: enabled (bit 0), not listen-only, 1 000 000 bps (0x000F4240 LE)
             * can1: disabled, baud 0 */
            if ((*out_len + 12U) > CS_GVRET_RESP_BUF_SIZE)
            {
                break;
            }
            uint8_t *p = out + *out_len;
            *p++ = 0xF1U;
            *p++ = 0x06U;
            *p++ = 0x01U;              /* can0 enabled, not listen-only */
            *p++ = 0x40U;              /* can0 baud 1 000 000 LE: byte 0 */
            *p++ = 0x42U;              /* byte 1 */
            *p++ = 0x0FU;              /* byte 2 */
            *p++ = 0x00U;              /* byte 3 */
            *p++ = 0x00U;              /* can1 disabled */
            *p++ = 0x00U;              /* can1 baud 0 LE */
            *p++ = 0x00U;
            *p++ = 0x00U;
            *p++ = 0x00U;
            *out_len += 12U;
            i += 1U;
        }
        else if (cmd == 0x05U && (i + 2U) < in_len)  /* Set bus active */
        {
            if ((*out_len + 4U) > CS_GVRET_RESP_BUF_SIZE)
            {
                break;
            }
            uint8_t bus_num = in[i + 2U];
            out[(*out_len)++] = 0xF1U;
            out[(*out_len)++] = 0x05U;
            out[(*out_len)++] = bus_num;
            out[(*out_len)++] = 0x01U;  /* bus enabled */
            i += 2U;
        }
        /* All other commands: skip silently */
    }
}

void cs_gvret_process(void)
{
    static uint8_t  cs_tx_buf[CS_GVRET_FRAME_BUF_SIZE];
    static uint16_t cs_tx_pending_len = 0U;

    /* -----------------------------------------------------------------------
     * Retry any frame whose USB transmission was deferred because CDC was
     * busy last call.  cs_tx_buf must not be overwritten while a USB DMA
     * transfer sourced from it may still be in progress.
     * ----------------------------------------------------------------------- */
    if (cs_tx_pending_len > 0U)
    {
        if (CDC_Transmit_FS(cs_tx_buf, cs_tx_pending_len) == USBD_OK)
        {
            cs_tx_pending_len = 0U;
        }
        /* Still BUSY: leave pending, retry on the next call. */
    }
    else
    {
        cs_can_frame_t frame;
        if (cs_can_rx_pop(&frame))
        {
            cs_gvret_encode_frame(&frame, cs_tx_buf, &cs_tx_pending_len);
            if (CDC_Transmit_FS(cs_tx_buf, cs_tx_pending_len) == USBD_OK)
            {
                cs_tx_pending_len = 0U;
            }
            /* If BUSY: cs_tx_buf holds the encoded frame, retry next call. */
        }
    }
}
