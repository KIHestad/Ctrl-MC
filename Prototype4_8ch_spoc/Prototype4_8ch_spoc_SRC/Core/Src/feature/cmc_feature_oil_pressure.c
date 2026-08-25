/**
  *********************************************************************************************
  * @file      cmc_feature_oil_pressure.c
  * @brief     Oil pressure sensor feature — drives INSTR_OIL from the oil pressure sensor input
  * @details   Reads cmc_app_state.feature.oil_pressure.on (set by OIL_SENSOR input or CAN RX
  *            from another unit) and drives the INSTR_OIL warning output on this unit.
  *            The warning light is active only when ignition is on.
  *            The oil pressure sensor is active-low: it connects to GND when oil pressure is
  *            absent or critically low, triggering the warning light.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"
#include "feature/cmc_feature_test_channels.h"
#include "feature/cmc_feature_oil_pressure.h"

// Whether this unit has an INSTR_OIL output configured
static bool    this_unit_feature_out_enabled = false;

// Output switch ID for the oil pressure warning light; 0xFF = not present on this unit
static uint8_t switch_id                = 0xFF;

// Resolved output state from the last process() call — used to detect changes
static bool    prev_out                 = false;

/* ---- Helpers ----------------------------------------------------------------------------- */

static void set_output(uint8_t id, bool on, bool *prev)
{
    if (id != 0xFF && on != *prev) {
        cmc_features_out_set_switch(id, on);
        *prev = on;
    }
}

static void cmc_feature_oil_pressure_broadcast(void)
{
    struct cmc_can_message_feature_oil_pressure_sensor_t msg;
    msg.oil_pressure_low_detected = cmc_app_state.feature.oil_pressure.on ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_OIL_PRESSURE_SENSOR_LENGTH];
    if (cmc_can_message_feature_oil_pressure_sensor_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_OIL_PRESSURE_SENSOR_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_FEATURE_OIL_PRESSURE_SENSOR_LENGTH);
}

/* ---- Init -------------------------------------------------------------------------------- */

void cmc_feature_oil_pressure_init(void)
{
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_OIL)) {
        switch_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_OIL);
    }

    // Explicit single source of truth: enabled, not test-suppressed, AND this unit has the output
    this_unit_feature_out_enabled = (cmc_config.feature_oil_pressure.enabled == 1) &&
        !cmc_feature_test_channels_suppresses(cmc_config.feature_oil_pressure.enabled_on_test) &&
        (switch_id != 0xFF);

    if (this_unit_feature_out_enabled) {
        cmc_features_out_set_switch(switch_id, false);
    }
}

/* ---- Process ----------------------------------------------------------------------------- */

void cmc_feature_oil_pressure_process(void)
{
    // Broadcast oil pressure state change to other units regardless of local outputs
    if (cmc_app_state.feature.oil_pressure.pending_broadcast) {
        cmc_app_state.feature.oil_pressure.pending_broadcast = false;
        cmc_feature_oil_pressure_broadcast();
    }

    if (!this_unit_feature_out_enabled) {
        return;
    }

    // Warning light requires ignition on
    bool resolved = cmc_app_state.vehicle.ignition_on &&
                    cmc_app_state.feature.oil_pressure.on;

    set_output(switch_id, resolved, &prev_out);
}
