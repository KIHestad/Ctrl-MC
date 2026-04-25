/**
  *********************************************************************************************
  * @file      cmc_can_manager.h
  * @brief     CAN manager for sending and receiving CAN messages.
  *            Builds on top of the cantools-generated cmc_can_message pack/unpack layer
  *            and the STM32 HAL FDCAN driver. Handles filter configuration, TX framing,
  *            and RX dispatch via user-registered callbacks.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CAN_MANAGER_H
#define CMC_CAN_MANAGER_H

#include "stm32g4xx_hal.h"
#include "can/cmc_can_message.h"

/**
 * Status codes for CAN manager operations.
 */
typedef enum {
    CMC_CAN_OK          = 0,
    CMC_CAN_ERROR       = 1,
    CMC_CAN_ERROR_PARAM = 2,
    CMC_CAN_ERROR_PACK  = 3,
    CMC_CAN_ERROR_TX    = 4,
} cmc_can_status_t;

/**
 * Callback type for received CAN messages. Called from Interrupt Service Routine (ISR) context – keep processing short.
 * @param frame_id  CAN frame identifier of the received frame, this refers to the Message ID set in the dbc-file.
 * @param data      Pointer to the raw payload bytes.
 * @param length    Number of payload bytes.
 */
typedef void (*cmc_can_rx_callback_t)(uint32_t frame_id, const uint8_t *data, uint8_t length);

/**
 * Initialize the CAN manager.
 * @return HAL_OK on success, HAL error code on failure.
 */
HAL_StatusTypeDef cmc_can_manager_init(void);

/**
 * Send a pre-packed CAN frame. The caller is responsible for packing the payload using the
 * appropriate cmc_can_message_*_pack() function before calling this.
 * @param frame_id  CAN frame identifier (use CMC_CAN_MESSAGE_*_FRAME_ID).
 * @param data      Pointer to the packed payload bytes.
 * @param length    Payload length in bytes (use CMC_CAN_MESSAGE_*_LENGTH).
 * @return CMC_CAN_OK on success, error code on failure.
 */
cmc_can_status_t cmc_can_manager_send(uint32_t frame_id, const uint8_t *data, uint8_t length);

/**
 * Register a callback for all received CAN messages. The callback is invoked from ISR context – keep processing short.
 * Use the frame_id to identify the message type and call the appropriate cmc_can_message_*_unpack() function.
 * @param callback Callback function, or NULL to unregister.
 */
void cmc_can_manager_on_receive(cmc_can_rx_callback_t callback);

#endif /* CMC_CAN_MANAGER_H */
