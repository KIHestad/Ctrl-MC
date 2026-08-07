/**
  *********************************************************************************************
  * @file      cmc_feature_brake_light.c
  * @brief     Brake light feature — drives LIGHT_BRAKE from the resolved brake input state
  * @details   Reads cmc_app_state.feature.brake_light.on (set by BRAKE_LEVER or BRAKE_PEDAL
  *            inputs, or received over CAN from another unit) and drives the LIGHT_BRAKE output
  *            on this unit. The brake light is active whenever ignition is on and the brake
  *            input is active. It is not suppressed by starter engagement.
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
#include "feature/cmc_feature_brake_light.h"

// Whether this unit has a LIGHT_BRAKE output configured
static bool    this_unit_feature_active = false;

// Output switch ID for the brake light; 0xFF = not present on this unit
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

static void cmc_feature_brake_light_broadcast(void)
{
    struct cmc_can_message_feature_brake_light_t msg;
    // Broadcast the locally-resolved brake state (lever OR pedal on this unit).
    // Receiving units store this in brake_light.on (their remote-brake field) and combine
    // it with their own local sources, so neither side can overwrite the other.
    bool local_active = cmc_app_state.feature.brake_lever.on ||
                        cmc_app_state.feature.brake_pedal.on;
    msg.brake_light_on = local_active ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_BRAKE_LIGHT_LENGTH];
    if (cmc_can_message_feature_brake_light_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_BRAKE_LIGHT_FRAME_ID, payload,
                         CMC_CAN_MESSAGE_FEATURE_BRAKE_LIGHT_LENGTH);
}

/* ---- Init -------------------------------------------------------------------------------- */

void cmc_feature_brake_light_init(void)
{
    if (cmc_config.feature_brake_light.enabled != 1) {
        return;
    }

    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_LIGHT_BRAKE)) {
        switch_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_LIGHT_BRAKE);
    }

    this_unit_feature_active = (switch_id != 0xFF);

    if (this_unit_feature_active) {
        cmc_features_out_set_switch(switch_id, false);
    }
}

/* ---- Process ----------------------------------------------------------------------------- */

void cmc_feature_brake_light_process(void)
{
    // Broadcast brake state change to other units regardless of local outputs
    if (cmc_app_state.feature.brake_light.pending_broadcast) {
        cmc_app_state.feature.brake_light.pending_broadcast = false;
        cmc_feature_brake_light_broadcast();
    }

    if (!this_unit_feature_active) {
        return;
    }

    // Brake light requires ignition on; not suppressed by starter.
    // Three independent sources — any one is sufficient:
    //   brake_lever.on  — local lever input (written only by local scanner)
    //   brake_pedal.on  — local pedal input (written only by local scanner)
    //   brake_light.on  — remote brake state received from another unit via CAN
    // Keeping the sources separate ensures a scanner update for one source can never
    // overwrite the state contributed by a different source on this or another unit.
    bool brake_active = cmc_app_state.feature.brake_lever.on ||
                        cmc_app_state.feature.brake_pedal.on ||
                        cmc_app_state.feature.brake_light.on;
    bool resolved = cmc_app_state.vehicle.ignition_on && brake_active;

    set_output(switch_id, resolved, &prev_out);
}
