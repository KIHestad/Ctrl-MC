/**
  *********************************************************************************************
  * @file      cmc_feature_neutral.c
  * @brief     Neutral sensor feature — drives INSTR_NEUTRAL from the neutral sensor input
  * @details   Reads cmc_app_state.feature.neutral.on (set by NEUTRAL_SENSOR input or CAN RX
  *            from another unit) and drives the INSTR_NEUTRAL indicator output on this unit.
  *            The neutral indicator is active only when ignition is on.
  *            The neutral sensor is active-low: it connects to GND when the gear is in neutral.
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
#include "feature/cmc_feature_neutral.h"

// Whether this unit has an INSTR_NEUTRAL output configured
static bool    this_unit_feature_active = false;

// Output switch ID for the neutral indicator; 0xFF = not present on this unit
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

static void cmc_feature_neutral_broadcast(void)
{
    struct cmc_can_message_feature_neutral_sensor_t msg;
    msg.neutral_engaged = cmc_app_state.feature.neutral.on ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_NEUTRAL_SENSOR_LENGTH];
    if (cmc_can_message_feature_neutral_sensor_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_NEUTRAL_SENSOR_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_FEATURE_NEUTRAL_SENSOR_LENGTH);
}

/* ---- Init -------------------------------------------------------------------------------- */

void cmc_feature_neutral_init(void)
{
    if (cmc_config.feature_neutral.enabled != 1) {
        return;
    }

    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_NEUTRAL)) {
        switch_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_NEUTRAL);
    }

    this_unit_feature_active = (switch_id != 0xFF);

    if (this_unit_feature_active) {
        cmc_features_out_set_switch(switch_id, false);
    }
}

/* ---- Process ----------------------------------------------------------------------------- */

void cmc_feature_neutral_process(void)
{
    // Broadcast neutral state change to other units regardless of local outputs
    if (cmc_app_state.feature.neutral.pending_broadcast) {
        cmc_app_state.feature.neutral.pending_broadcast = false;
        cmc_feature_neutral_broadcast();
    }

    if (!this_unit_feature_active) {
        return;
    }

    // Neutral indicator requires ignition on
    bool resolved = cmc_app_state.vehicle.ignition_on &&
                    cmc_app_state.feature.neutral.on;

    set_output(switch_id, resolved, &prev_out);
}
