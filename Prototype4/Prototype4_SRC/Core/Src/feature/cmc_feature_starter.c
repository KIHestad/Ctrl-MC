/**
  *********************************************************************************************
  * @file      cmc_feature_starter.c
  * @brief     Starter motor feature control logic
  * @details   Engages the starter motor output (CMC_CONFIG_OUT_DEVICE_STARTER) when:
  *            - The feature is enabled in configuration (enabled=1)
  *            - This unit has the starter output device configured
  *            - The starter button (CMC_CONFIG_IN_DEVICE_STARTER) is pressed
  *            - Ignition is on (cmc_app_state.veichle_state.ignition_on)
  *            The starter output follows the button directly — it is active while held and
  *            immediately disengages when the button is released or ignition turns off.
  *            When disabled (enabled=0): feature is inactive and the output is never driven.
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
#include "feature/cmc_feature_starter.h"

static bool this_unit_feature_active = false; // Set true in init if this unit has the starter output and feature is enabled
static uint8_t switch_id             = 0xFF;  // Output index for the starter switch on this unit
static bool this_unit_starter_active = false; // True if the starter is currently engaged (output on)

static void cmc_feature_starter_broadcast(void)
{
    struct cmc_can_message_feature_starter_t msg;
    msg.value_on_off = cmc_app_state.feature.starter.on ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_STARTER_LENGTH];
    if (cmc_can_message_feature_starter_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_STARTER_FRAME_ID, payload, CMC_CAN_MESSAGE_FEATURE_STARTER_LENGTH);
}

void cmc_feature_starter_init(void) {
    // Feature is active only if enabled in config AND this unit has the starter output configured
    this_unit_feature_active = (cmc_config.feature_starter.enabled == 1) && cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_STARTER);
    if (this_unit_feature_active) {
        switch_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_STARTER);
        // Ensure starter output is off at startup
        cmc_features_out_set_switch(switch_id, false);
        this_unit_starter_active = false;
    }
}

void cmc_feature_starter_process(void) {
    // Broadcast button state change if this unit has the starter input (regardless of output)
    if (cmc_app_state.feature.starter.pending_broadcast) {
        cmc_app_state.feature.starter.pending_broadcast = false;
        cmc_feature_starter_broadcast();
    }

    // Feature is not configured or enabled on this unit, do nothing
    if (!this_unit_feature_active) {
        return;
    }

    bool starter_button_now = cmc_app_state.feature.starter.on;
    bool ignition_on        = cmc_app_state.vehicle.ignition_on;

    // Starter engages only while button is held AND ignition is on
    bool should_engage = starter_button_now && ignition_on;

    if (should_engage && !this_unit_starter_active) {
        // Conditions met and starter is not yet running — engage
        cmc_features_out_set_switch(switch_id, true);
        this_unit_starter_active = true;
    }
    else if (this_unit_starter_active && !should_engage) {
        // Conditions no longer met — disengage immediately
        cmc_features_out_set_switch(switch_id, false);
        this_unit_starter_active = false;
    }
}
