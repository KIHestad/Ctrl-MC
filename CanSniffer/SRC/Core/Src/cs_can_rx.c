#include "cs_can_rx.h"
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"

/* --------------------------------------------------------------------------
 * External handle declared in main.c
 * -------------------------------------------------------------------------- */
extern FDCAN_HandleTypeDef hfdcan1;

/* --------------------------------------------------------------------------
 * Ring buffer
 * -------------------------------------------------------------------------- */
#define CS_CAN_RX_BUF_DEPTH 32U

typedef struct
{
    cs_can_frame_t   buf[CS_CAN_RX_BUF_DEPTH];
    volatile uint32_t head; /**< Written by ISR  */
    volatile uint32_t tail; /**< Read  by caller */
} cs_can_rx_ring_t;

static cs_can_rx_ring_t cs_ring;

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */

/**
 * @brief  Convert HAL-encoded DataLength field (FDCAN_DLC_BYTES_x) to an
 *         actual byte count.  The HAL stores the DLC index in bits [19:16].
 */
static uint8_t cs_dlc_to_len(uint32_t dlc_code)
{
    static const uint8_t k_table[16] =
    {
        0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U,    /* DLC 0–8  → 0–8 bytes  */
        8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U  /* DLC 9–15 → FD lengths */
    };
    uint8_t idx = (uint8_t)((dlc_code >> 16U) & 0x0FU);
    return k_table[idx];
}

/* --------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

void cs_can_rx_init(void)
{
    /* Accept all standard and extended frames — both matching and
     * non-matching — into FIFO0.  With StdFiltersNbr = 0 and
     * ExtFiltersNbr = 0 every received frame is "non-matching", so the
     * global filter setting below is the only rule that applies.
     * FDCAN_FILTER_REMOTE (= 0) lets remote frames follow the same path
     * instead of being discarded unconditionally. */
    if (HAL_FDCAN_ConfigGlobalFilter(
            &hfdcan1,
            FDCAN_ACCEPT_IN_RX_FIFO0,   /* NonMatchingStd  */
            FDCAN_ACCEPT_IN_RX_FIFO0,   /* NonMatchingExt  */
            FDCAN_FILTER_REMOTE,         /* RejectRemoteStd */
            FDCAN_FILTER_REMOTE)         /* RejectRemoteExt */
        != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(
            &hfdcan1,
            FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
            0U)
        != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
    {
        Error_Handler();
    }
}

void cs_can_rx_process(void)
{
    /* Intentionally empty — consumers call cs_can_rx_pop() directly from
     * the main loop or wherever they need a frame. */
}

bool cs_can_rx_pop(cs_can_frame_t *frame)
{
    __disable_irq();

    bool available = (cs_ring.tail != cs_ring.head);
    if (available)
    {
        *frame       = cs_ring.buf[cs_ring.tail];
        cs_ring.tail = (cs_ring.tail + 1U) % CS_CAN_RX_BUF_DEPTH;
    }

    __enable_irq();
    return available;
}

/* --------------------------------------------------------------------------
 * FDCAN RX FIFO0 callback  (overrides HAL weak stub)
 * -------------------------------------------------------------------------- */

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((hfdcan->Instance != FDCAN1) ||
        ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == 0U))
    {
        return;
    }

    FDCAN_RxHeaderTypeDef rx_hdr;
    uint8_t               rx_data[64];

    /* Drain all pending messages from FIFO0 in one ISR invocation. */
    while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0) > 0U)
    {
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_hdr, rx_data) != HAL_OK)
        {
            break;
        }

        uint32_t next_head = (cs_ring.head + 1U) % CS_CAN_RX_BUF_DEPTH;

        /* If the buffer is full, drop the oldest frame to make room. */
        if (next_head == cs_ring.tail)
        {
            cs_ring.tail = (cs_ring.tail + 1U) % CS_CAN_RX_BUF_DEPTH;
        }

        cs_can_frame_t *slot = &cs_ring.buf[cs_ring.head];
        slot->id        = rx_hdr.Identifier;
        slot->ide       = (rx_hdr.IdType  == FDCAN_EXTENDED_ID) ? 1U : 0U;
        slot->fdf       = (rx_hdr.FDFormat == FDCAN_FD_CAN)     ? 1U : 0U;
        slot->dlc       = cs_dlc_to_len(rx_hdr.DataLength);
        slot->timestamp = HAL_GetTick();

        for (uint8_t i = 0U; i < slot->dlc; i++)
        {
            slot->data[i] = rx_data[i];
        }

        cs_ring.head = next_head;
    }
}
