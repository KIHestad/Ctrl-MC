/**
  *********************************************************************************************
  * @file      cmc_feature_channel_info.c
  * @brief     Per-channel power and status reporting over CAN
  * @details   cmc_util_switch_sample_all() runs every 100 ms for fault detection.
  *            CHANNEL_STATUS (208, 3 bytes) is sent immediately on status change and every 1 s
  *            per configured channel.
 *            UNIT_INFO (210, 6 bytes) is sent every 1 s: supply voltage, MCU temperature,
 *            total watts, VDDA via VREFINT.
  *            CHANNEL_OVERVIEW (209, 32 bytes CAN FD) is sent every 1 s when
  *            overview_enabled = 1 in config. *            CHANNEL_OVERVIEW_01_03/04_06/07_09/10_12 (211-214, 8 bytes classic CAN) are
 *            per-group alternatives sent every 1 s when their overview_enabled_* flag is set.  *            Supply voltage defaults to 12.0 V (no sensing hardware on current PCB).
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "util/cmc_util_switch_driver.h"
#include "util/cmc_util_mcu_driver.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"
#include "feature/cmc_feature_channel_info.h"

#define SAMPLE_INTERVAL_MS        100U
#define PERIODIC_INTERVAL_MS     1000U
#define REBROADCAST_INTERVAL_MS  5000U

#define MCU_TEMP_FALLBACK_RAW     400U  // raw 400 = 0.0°C in 0.1°C encoding; shown when reading is out of range
#define SUPPLY_VOLTAGE_DEFAULT_MV 11930U // Measured supply voltage on PCB v1.0.0 to 11.93V, 12.0 V nominal from PSU

static bool     s_enabled          = false;
static bool     s_overview_enabled = false;
static bool     s_overview_enabled_01_03 = false;
static bool     s_overview_enabled_04_06 = false;
static bool     s_overview_enabled_07_09 = false;
static bool     s_overview_enabled_10_12 = false;
static uint32_t s_last_sample_ms   = 0U;
static uint32_t s_last_periodic_ms = 0U;
static uint32_t s_last_recast_ms   = 0U;
static uint8_t  s_prev_status[CMC_CONFIG_HW_OUT_COUNT];

/* ---- CAN broadcast helpers -------------------------------------------------------------- */

static void broadcast_channel_status(uint8_t ch) {
    struct cmc_can_message_channel_status_t msg;
    msg.channel_number = ch + 1U;
    msg.is_on      = cmc_util_switch_is_on(ch) ? 1U : 0U;
    msg.status     = cmc_app_state_channel_info.ch[ch].fault_code;
    msg.watts      = cmc_app_state_channel_info.ch[ch].power_cw;
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_STATUS_LENGTH];
    if (cmc_can_message_channel_status_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_STATUS_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_STATUS_LENGTH);
}

static void broadcast_unit_info(void) {
    struct cmc_can_message_unit_info_t msg;
    msg.supply_voltage = (uint16_t)(cmc_app_state_channel_info.supply_voltage_mv / 10U);
    // t in tenths of °C; raw = t + 400 (DBC: scale=0.1, offset=-40 → raw=(phys+40)/0.1=tenths+400)
    int16_t t          = cmc_util_mcu_read_temp();
    bool out_of_range  = (t < -400 || t > 2140);
    msg.mcu_temp_c             = out_of_range ? MCU_TEMP_FALLBACK_RAW : (uint16_t)((int32_t)t + 400);
    msg.mcu_temp_out_of_range  = out_of_range ? 1U : 0U;
    uint32_t total_cw = 0U;
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        total_cw += cmc_app_state_channel_info.ch[ch].power_cw;
    }
    // power_cw is in 0.01 W units; total_watts signal uses 0.1 W units
    msg.total_watts = (uint16_t)(total_cw / 10U);
    // vfref: VDDA in mV / 10 gives 0.01 V units (2 decimal places)
    uint32_t vdda_mv = cmc_util_mcu_read_vdda_mv();
    msg.vfref = (uint16_t)(vdda_mv / 10U);
    uint8_t payload[CMC_CAN_MESSAGE_UNIT_INFO_LENGTH];
    if (cmc_can_message_unit_info_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_UNIT_INFO_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_UNIT_INFO_LENGTH);
}

static void broadcast_channel_overview(void) {
    struct cmc_can_message_channel_overview_t msg;
    if (cmc_can_message_channel_overview_init(&msg) < 0) { return; }
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        uint8_t  is_on  = cmc_util_switch_is_on(ch) ? 1U : 0U;
        uint8_t  status = cmc_app_state_channel_info.ch[ch].fault_code;
        uint16_t watts  = cmc_app_state_channel_info.ch[ch].power_cw;
        switch (ch) {
            case  0: msg.ch01_is_on  = is_on; msg.ch01_status  = status; msg.ch01_watts  = watts; break;
            case  1: msg.ch02_is_on  = is_on; msg.ch02_status  = status; msg.ch02_watts  = watts; break;
            case  2: msg.ch03_is_on  = is_on; msg.ch03_status  = status; msg.ch03_watts  = watts; break;
            case  3: msg.ch04_is_on  = is_on; msg.ch04_status  = status; msg.ch04_watts  = watts; break;
            case  4: msg.ch05_is_on  = is_on; msg.ch05_status  = status; msg.ch05_watts  = watts; break;
            case  5: msg.ch06_is_on  = is_on; msg.ch06_status  = status; msg.ch06_watts  = watts; break;
            case  6: msg.ch07_is_on  = is_on; msg.ch07_status  = status; msg.ch07_watts  = watts; break;
            case  7: msg.ch08_is_on  = is_on; msg.ch08_status  = status; msg.ch08_watts  = watts; break;
            case  8: msg.ch09_is_on  = is_on; msg.ch09_status  = status; msg.ch09_watts  = watts; break;
            case  9: msg.ch10_is_on = is_on; msg.ch10_status = status; msg.ch10_watts = watts; break;
            case 10: msg.ch11_is_on = is_on; msg.ch11_status = status; msg.ch11_watts = watts; break;
            case 11: msg.ch12_is_on = is_on; msg.ch12_status = status; msg.ch12_watts = watts; break;
            default: break;
        }
    }
    msg.supply_voltage = (uint16_t)(cmc_app_state_channel_info.supply_voltage_mv / 100U);
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_LENGTH];
    if (cmc_can_message_channel_overview_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_LENGTH);
}

// Reads channel state for a 1-based channel number, defaulting to off/POWER_GOOD/0W if out of hardware range
static void read_channel(uint8_t channel_number, uint8_t *is_on, uint8_t *status, uint16_t *watts) {
    uint8_t ch = channel_number - 1U;
    if (ch < CMC_CONFIG_HW_OUT_COUNT) {
        *is_on  = cmc_util_switch_is_on(ch) ? 1U : 0U;
        *status = cmc_app_state_channel_info.ch[ch].fault_code;
        *watts  = cmc_app_state_channel_info.ch[ch].power_cw;
    } else {
        *is_on  = 0U;
        *status = (uint8_t)CMC_SWITCH_POWER_GOOD;
        *watts  = 0U;
    }
}

// Classic-CAN alternative to CHANNEL_OVERVIEW, split into groups of 3 channels to fit an 8-byte frame
static void broadcast_channel_overview_01_03(void) {
    struct cmc_can_message_channel_overview_01_03_t msg;
    read_channel(1U, &msg.ch01_is_on, &msg.ch01_status, &msg.ch01_watts);
    read_channel(2U, &msg.ch02_is_on, &msg.ch02_status, &msg.ch02_watts);
    read_channel(3U, &msg.ch03_is_on, &msg.ch03_status, &msg.ch03_watts);
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_01_03_LENGTH];
    if (cmc_can_message_channel_overview_01_03_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_01_03_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_01_03_LENGTH);
}

static void broadcast_channel_overview_04_06(void) {
    struct cmc_can_message_channel_overview_04_06_t msg;
    read_channel(4U, &msg.ch04_is_on, &msg.ch04_status, &msg.ch04_watts);
    read_channel(5U, &msg.ch05_is_on, &msg.ch05_status, &msg.ch05_watts);
    read_channel(6U, &msg.ch06_is_on, &msg.ch06_status, &msg.ch06_watts);
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_04_06_LENGTH];
    if (cmc_can_message_channel_overview_04_06_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_04_06_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_04_06_LENGTH);
}

static void broadcast_channel_overview_07_09(void) {
    struct cmc_can_message_channel_overview_07_09_t msg;
    read_channel(7U, &msg.ch07_is_on, &msg.ch07_status, &msg.ch07_watts);
    read_channel(8U, &msg.ch08_is_on, &msg.ch08_status, &msg.ch08_watts);
    read_channel(9U, &msg.ch09_is_on, &msg.ch09_status, &msg.ch09_watts);
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_07_09_LENGTH];
    if (cmc_can_message_channel_overview_07_09_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_07_09_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_07_09_LENGTH);
}

static void broadcast_channel_overview_10_12(void) {
    struct cmc_can_message_channel_overview_10_12_t msg;
    read_channel(10U, &msg.ch10_is_on, &msg.ch10_status, &msg.ch10_watts);
    read_channel(11U, &msg.ch11_is_on, &msg.ch11_status, &msg.ch11_watts);
    read_channel(12U, &msg.ch12_is_on, &msg.ch12_status, &msg.ch12_watts);
    uint8_t payload[CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_10_12_LENGTH];
    if (cmc_can_message_channel_overview_10_12_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_10_12_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_CHANNEL_OVERVIEW_10_12_LENGTH);
}

/* ---- Init / Process --------------------------------------------------------------------- */

void cmc_feature_channel_info_init(void) {
    s_enabled          = (cmc_config.feature_channel_info.enabled == 1U);
    s_overview_enabled = (cmc_config.feature_channel_info.overview_enabled == 1U);
    s_overview_enabled_01_03 = (cmc_config.feature_channel_info.overview_enabled_01_03 == 1U);
    s_overview_enabled_04_06 = (cmc_config.feature_channel_info.overview_enabled_04_06 == 1U);
    s_overview_enabled_07_09 = (cmc_config.feature_channel_info.overview_enabled_07_09 == 1U);
    s_overview_enabled_10_12 = (cmc_config.feature_channel_info.overview_enabled_10_12 == 1U);
    if (!s_enabled) { return; }

    cmc_app_state_channel_info.supply_voltage_mv = SUPPLY_VOLTAGE_DEFAULT_MV;

    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        cmc_app_state_channel_info.ch[ch].power_cw   = 0U;
        cmc_app_state_channel_info.ch[ch].fault_code = CMC_SWITCH_POWER_GOOD;
        s_prev_status[ch] = CMC_SWITCH_POWER_GOOD;
    }
}

void cmc_feature_channel_info_process(void) {
    if (!s_enabled) { return; }

    uint32_t now = HAL_GetTick();

    // 100 ms: sample IS pins, update power and status, broadcast immediately on status change
    if (now - s_last_sample_ms >= SAMPLE_INTERVAL_MS) {
        s_last_sample_ms = now;
        cmc_util_switch_sample_all();

        for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
            int32_t ma = cmc_util_switch_read_current_ma(ch);
            if (ma < 0) { ma = 0; }
            // Power [0.01 W] = V [mV] * I [mA] / 10000
            uint32_t pcw = (uint32_t)(((uint64_t)cmc_app_state_channel_info.supply_voltage_mv
                                       * (uint32_t)ma) / 10000UL);
            cmc_app_state_channel_info.ch[ch].power_cw = (pcw > 20000U) ? 20000U : (uint16_t)pcw;

            uint8_t new_status;
            cmc_switch_status_t drv = cmc_util_switch_get_status(ch);
            if (drv != CMC_SWITCH_POWER_GOOD) {
                new_status = (uint8_t)drv;
            } else if (cmc_util_switch_is_on(ch) &&
                       (uint32_t)ma < cmc_config.feature_channel_info.open_load_ma) {
                new_status = (uint8_t)CMC_SWITCH_FAULT_OPEN_LOAD;
            } else {
                new_status = (uint8_t)CMC_SWITCH_POWER_GOOD;
            }

            if (new_status != s_prev_status[ch]) {
                s_prev_status[ch]                             = new_status;
                cmc_app_state_channel_info.ch[ch].fault_code = new_status;
                broadcast_channel_status(ch);
                s_last_recast_ms = now;
            }
        }
    }

    // 1 s: periodic broadcast of all channel statuses, unit info, and optional overview
    if (now - s_last_periodic_ms >= PERIODIC_INTERVAL_MS) {
        s_last_periodic_ms = now;
        for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
            broadcast_channel_status(ch);
        }
        broadcast_unit_info();
        if (s_overview_enabled) {
            broadcast_channel_overview();
        }
        if (s_overview_enabled_01_03) { broadcast_channel_overview_01_03(); }
        if (s_overview_enabled_04_06) { broadcast_channel_overview_04_06(); }
        if (s_overview_enabled_07_09) { broadcast_channel_overview_07_09(); }
        if (s_overview_enabled_10_12) { broadcast_channel_overview_10_12(); }
    }

    // 5 s: re-broadcast channels with active faults so late-joining units stay informed
    bool any_fault = false;
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        if (cmc_app_state_channel_info.ch[ch].fault_code != CMC_SWITCH_POWER_GOOD) {
            any_fault = true;
            break;
        }
    }
    if (any_fault && (now - s_last_recast_ms >= REBROADCAST_INTERVAL_MS)) {
        s_last_recast_ms = now;
        for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
            if (cmc_app_state_channel_info.ch[ch].fault_code != CMC_SWITCH_POWER_GOOD) {
                broadcast_channel_status(ch);
            }
        }
    }
}
