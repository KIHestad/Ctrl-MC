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

    /* Start byte + command 0x00 (incoming CAN frame) */
    *p++ = 0xF1U;
    *p++ = 0x00U;

    /* Timestamp milliseconds (little-endian) */
    cs_write_u32_le(&p, frame->timestamp);

    /* Timestamp microseconds — not available from HAL_GetTick(), send 0 */
    cs_write_u32_le(&p, 0U);

    /* CAN ID (little-endian); set bit 31 for extended (29-bit) frames */
    uint32_t can_id = frame->id;
    if (frame->ide != 0U)
    {
        can_id |= 0x80000000UL;
    }
    cs_write_u32_le(&p, can_id);

    /* bus_flags: bit 4 = CAN FD frame, bits 3:0 = bus number (always 0) */
    *p++ = (frame->fdf != 0U) ? 0x10U : 0x00U;

    /* Actual data byte count */
    *p++ = frame->dlc;

    /* Payload */
    for (uint8_t i = 0U; i < frame->dlc; i++)
    {
        *p++ = frame->data[i];
    }

    /* Trailing bus number */
    *p++ = 0x00U;

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

        if (cmd == 0x01U) /* Time sync */
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
        else if (cmd == 0x09U) /* Device identity */
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
        /* All other commands: skip silently */
    }
}

void cs_gvret_process(void)
{
    static uint32_t cs_led_off_tick = 0U;

    cs_can_frame_t frame;
    uint8_t        buf[CS_GVRET_FRAME_BUF_SIZE];
    uint16_t       len;

    while (cs_can_rx_pop(&frame))
    {
        cs_gvret_encode_frame(&frame, buf, &len);
        if (CDC_Transmit_FS(buf, len) == USBD_OK)
        {
            /* Turn LED on and record the off-time (non-blocking 20 ms pulse) */
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
            cs_led_off_tick = HAL_GetTick() + 20U;
        }
        else
        {
            /* USB TX not ready; defer remaining frames to the next process call */
            break;
        }
    }

    /* Non-blocking LED off: extinguish once the 20 ms window has elapsed */
    if ((cs_led_off_tick != 0U) && (HAL_GetTick() >= cs_led_off_tick))
    {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        cs_led_off_tick = 0U;
    }
}
