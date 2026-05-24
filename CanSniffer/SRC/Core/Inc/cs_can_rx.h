#ifndef CS_CAN_RX_H
#define CS_CAN_RX_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Captured CAN frame stored in the receive ring buffer.
 */
typedef struct
{
    uint32_t id;        /**< CAN identifier (11-bit standard or 29-bit extended) */
    uint8_t  ide;       /**< 1 = extended frame (29-bit ID), 0 = standard (11-bit) */
    uint8_t  fdf;       /**< 1 = CAN FD frame, 0 = classic CAN 2.0 */
    uint8_t  dlc;       /**< Actual payload byte count (0–64) */
    uint8_t  data[64];  /**< Payload bytes */
    uint32_t timestamp; /**< Capture time in ms from HAL_GetTick() */
} cs_can_frame_t;

/**
 * @brief  Initialise FDCAN reception: configure accept-all global filter,
 *         arm FIFO0 new-message interrupt, and start the peripheral.
 *         Call from main.c within the USER CODE BEGIN 2 section.
 */
void cs_can_rx_init(void);

/**

 * @brief  Main-loop processing hook (reserved for future use).
 *         Call from main.c within the USER CODE BEGIN 3 section.
 */
void cs_can_rx_process(void);

/**
 * @brief  Pop the oldest frame from the ring buffer.
 *
 * @param[out] frame  Destination for the retrieved frame. Must not be NULL.
 * @return  true if a frame was available and copied into @p frame,
 *          false if the buffer was empty.
 *
 * @note  ISR-safe: uses __disable_irq / __enable_irq for atomic access.
 *        Call only from thread (main-loop) context.
 */
bool cs_can_rx_pop(cs_can_frame_t *frame);

/**
 * @brief  Transmit a classic CAN 2.0 frame on FDCAN1.
 *
 * @param id    CAN identifier (11-bit standard or 29-bit extended, without flags).
 * @param ide   true = extended (29-bit) frame.
 * @param dlc   Payload byte count (0–8). Values above 8 are clamped.
 * @param data  Pointer to payload bytes.
 * @return  true if the frame was accepted into the TX FIFO, false if the
 *          TX FIFO was full or the peripheral rejected the request.
 *
 * @note  May be called from interrupt context (e.g. CDC_Receive_FS).
 */
bool cs_can_tx_send(uint32_t id, bool ide, uint8_t dlc, const uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* CS_CAN_RX_H */
