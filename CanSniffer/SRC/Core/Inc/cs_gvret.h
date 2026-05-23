#ifndef CS_GVRET_H
#define CS_GVRET_H

#include <stdint.h>
#include "cs_can_rx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum buffer size for a single GVRET-encoded CAN frame.
 * 17 bytes of fixed header/footer + up to 64 bytes of CAN FD payload = 81 bytes.
 */
#define CS_GVRET_FRAME_BUF_SIZE  81U

/**
 * Maximum buffer size for a single GVRET host-command response.
 * Largest response is the device identity reply: 3-byte header +
 * 24-char string + 1-byte NUL terminator = 28 bytes.
 */
#define CS_GVRET_RESP_BUF_SIZE   28U

/**
 * @brief  Encode a captured CAN frame into a GVRET binary frame (cmd 0x00).
 *
 * Wire format:
 *   0xF1 0x00 | timestamp_ms[4 LE] | timestamp_us[4 LE] |
 *   CAN_ID[4 LE, bit31=extended] | bus_flags[1] | data_len[1] |
 *   data[0..64] | bus[1]
 *
 * @param[in]  frame  Source CAN frame; must not be NULL.
 * @param[out] buf    Output buffer; caller must provide at least
 *                    CS_GVRET_FRAME_BUF_SIZE bytes.
 * @param[out] len    Number of bytes written to @p buf.
 */
void cs_gvret_encode_frame(const cs_can_frame_t *frame,
                            uint8_t *buf,
                            uint16_t *len);

/**
 * @brief  Parse bytes received from the host and produce a response.
 *
 * Handled commands:
 *   0xF1 0x01  Time sync  → 0xF1 0x01 + HAL_GetTick()[4 LE]
 *   0xF1 0x09  Identity   → 0xF1 0x09 0x00 "EVTV Motors Garage GVRET" 0x00
 *
 * Unknown commands are silently ignored.
 *
 * @param[in]  in       Bytes received from the host.
 * @param[in]  in_len   Number of bytes in @p in.
 * @param[out] out      Response buffer; caller must provide at least
 *                      CS_GVRET_RESP_BUF_SIZE bytes.
 * @param[out] out_len  Number of response bytes written; 0 if no response.
 */
void cs_gvret_process_host_cmd(const uint8_t *in, uint16_t in_len,
                                uint8_t *out,      uint16_t *out_len);

/**
 * @brief  Main-loop processing: drain the CAN RX ring buffer, encode each
 *         frame as a GVRET packet, and transmit over USB CDC.
 *         Call from main.c within the USER CODE BEGIN 3 section.
 */
void cs_gvret_process(void);

#ifdef __cplusplus
}
#endif

#endif /* CS_GVRET_H */
