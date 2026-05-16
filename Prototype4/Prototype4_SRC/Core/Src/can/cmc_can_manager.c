/**
  *********************************************************************************************
  * @file      cmc_can_manager.c
  * @brief     CAN manager for sending and receiving CAN messages.
  *            Builds on top of the cantools-generated cmc_can_message pack/unpack layer
  *            and the STM32 HAL FDCAN driver. Handles filter configuration, TX framing,
  *            and RX dispatch via user-registered callbacks.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "can/cmc_can_manager.h"
#include "app/cmc_app_logic.h"
#include <string.h>

/* ---- Private state ------------------------------------------------------------------------ */

extern FDCAN_HandleTypeDef hfdcan1; // FDCAN peripheral handle, defined in main.c
static volatile cmc_can_rx_callback_t rx_callback = NULL; // User-registered RX callback, called from ISR on frame reception 

/* ---- Helpers ------------------------------------------------------------------------------- */

// Convert a payload length (bytes) to the FDCAN DLC register value.
static uint32_t length_to_dlc(uint8_t len)
{
    if (len <= 8u)  return (uint32_t)len << 16u;
    if (len <= 12u) return FDCAN_DLC_BYTES_12;
    if (len <= 16u) return FDCAN_DLC_BYTES_16;
    if (len <= 20u) return FDCAN_DLC_BYTES_20;
    if (len <= 24u) return FDCAN_DLC_BYTES_24;
    if (len <= 32u) return FDCAN_DLC_BYTES_32;
    if (len <= 48u) return FDCAN_DLC_BYTES_48;
    return FDCAN_DLC_BYTES_64;
}

// Convert an FDCAN DLC register value back to payload length in bytes.
static uint8_t dlc_to_length(uint32_t dlc)
{
    static const uint8_t table[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64 };
    uint8_t idx = (uint8_t)(dlc >> 16u);
    if (idx >= sizeof(table)) return 0u;
    return table[idx];
}

/* ---- Public functions ----------------------------------------------------------------------------- */

HAL_StatusTypeDef cmc_can_manager_init(void)
{
    // Accept all standard-ID frames, reject extended and remote
    HAL_StatusTypeDef status;

    status = HAL_FDCAN_ConfigGlobalFilter(
        &hfdcan1,
        FDCAN_ACCEPT_IN_RX_FIFO0,
        FDCAN_REJECT,
        FDCAN_REJECT_REMOTE,
        FDCAN_REJECT_REMOTE);
    if (status != HAL_OK) return status;

    // Enable RX FIFO 0 new-message interrupt
    status = HAL_FDCAN_ActivateNotification(
        &hfdcan1, 
        FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 
        0);
    if (status != HAL_OK) return status;

    // Start the peripheral 
    status = HAL_FDCAN_Start(&hfdcan1);
    return status;

}

// Send a CAN message
cmc_can_status_t cmc_can_manager_send(uint32_t frame_id, const uint8_t *data, uint8_t length)
{
    if (data == NULL) {
        return CMC_CAN_ERROR_PARAM;
    }
    FDCAN_TxHeaderTypeDef tx_header;
    tx_header.Identifier          = frame_id;
    tx_header.IdType              = FDCAN_STANDARD_ID;
    tx_header.TxFrameType         = FDCAN_DATA_FRAME;
    tx_header.DataLength          = length_to_dlc(length);
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch       = (length > 8u) ? FDCAN_BRS_ON : FDCAN_BRS_OFF; // Auto switch to BRS for FD frames
    tx_header.FDFormat            = (length > 8u) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN; // Auto switch to FD format for payloads > 8 bytes
    tx_header.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker       = 0;
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &tx_header, (uint8_t *)data) != HAL_OK) {
        return CMC_CAN_ERROR_TX;
    }
    return CMC_CAN_OK;
}

// Register a callback for received CAN messages. The callback is invoked from ISR context – keep processing short. 
// Use the frame_id to identify the message type and call the appropriate cmc_can_message_*_unpack() function.
void cmc_can_manager_on_receive(cmc_can_rx_callback_t callback)
{
    rx_callback = callback;
}

/* ---- HAL RX callback (overrides default) ---------------------------------------------------------------------- */

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == 0u) return;
    // Read the received frame (header + data) and invoke the user callback with raw data for unpacking.
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[64];
    // Note: HAL_FDCAN_GetRxMessage() must be called to release the FIFO and clear the interrupt, even if we don't use the data.
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data) != HAL_OK) {
        return;
    }
    // Invoke user callback if it is registered
    uint8_t length = dlc_to_length(rx_header.DataLength);
    cmc_can_rx_callback_t callback = rx_callback;
    if (callback != NULL) {
        callback(rx_header.Identifier, rx_data, length);
    }
}
