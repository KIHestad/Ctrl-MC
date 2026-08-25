/**
  *********************************************************************************************
  * @file      cmc_feature_horn.c
  * @brief     Horn feature control logic, manages horn activation based on input and configuration
  * @details   Only relevant for these conditions:
  *            - The horn feature is enabled in the configuration: cmc_config.feature_horn.enabled
  *            - This unit has an output configured as a horn: CMC_OUT_HORN (cmc_out_t)
  *            - The horn is not to be powered unless ignition is on, not parameter driven
  *            - The horn is not to be powered when starter motor is engaged, to save battery, not parameter driven
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_logic.h"
#include "app/cmc_app_state.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"
#include "feature/cmc_feature_test_channels.h"
#include "feature/cmc_feature_horn.h"

// Locals
// Static variables to track the horn state and configuration on this unit
static bool this_unit_feature_active = false;   // Set true if relevant in initialization, if false the horn logic will be inactive and do nothing
static uint8_t switch_id             = 0xFF;    // The output index for the horn switch on this unit
// Active state tracking for the horn
static bool this_unit_horn_active    = false;   // True if the horn is currently active (powered on)
static bool button_prev_state        = false;   // Previous horn button state, used to detect a fresh press and prevent re-activation while button is held
static uint32_t horn_on_since_ms     = 0;       // Tick at which the horn was last turned on, used for auto shut-off timeout

static void cmc_feature_horn_broadcast(void)
{
    struct cmc_can_message_feature_horn_t msg;
    msg.horn_on = cmc_app_state.feature.horn.on ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH];
    if (cmc_can_message_feature_horn_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID, payload, CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH);
}

void cmc_feature_horn_init(void) {
  // Check if the horn feature is enabled in the configuration and if this unit has the horn output device enabled, if not, this feature will be inactive and do nothing
  this_unit_feature_active = (cmc_config.feature_horn.enabled == 1) && 
    !cmc_feature_test_channels_suppresses(cmc_config.feature_horn.enabled_on_test) &&
    cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_HORN);
  if (this_unit_feature_active) {
      // Get the output index for the horn switch on this unit, used for controlling the horn output channel when needed
      switch_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_HORN);
      // Ensure the horn starts in the off state on initialization
      cmc_features_out_set_switch(switch_id, false);
  }
}

// Turn Horn on/off
void cmc_feature_horn_process(void) {
  // Broadcast state change if relevant
  if (cmc_app_state.feature.horn.pending_broadcast) {
      cmc_app_state.feature.horn.pending_broadcast = false;
      cmc_feature_horn_broadcast();
  }

  // Feature is not configured or enabled on this unit, do nothing
  if (!this_unit_feature_active) {
      return;
  }

  // Auto shut-off: if configured and horn has been on long enough, turn it off
  if (this_unit_horn_active && (cmc_config.feature_horn.auto_shut_off_sec > 0U)) {
    if ((HAL_GetTick() - horn_on_since_ms) >= ((uint32_t)cmc_config.feature_horn.auto_shut_off_sec * 1000U)) {
      cmc_features_out_set_switch(switch_id, false);
      this_unit_horn_active = false;
    }
  }

  //   Detect a fresh button press: only a new press after a release can activate the horn.
  // This naturally prevents re-activation after auto shut-off while the button is still held.
  bool button_now = cmc_app_state.feature.horn.on;
  bool button_just_pressed = button_now != button_prev_state && button_now;
  bool conditions_met = cmc_app_state.vehicle.ignition_on && !cmc_app_state.feature.starter.on;
  
  if (button_just_pressed && !this_unit_horn_active && conditions_met) {
    // Turn horn on: fresh press with valid conditions
    cmc_features_out_set_switch(switch_id, true);
    horn_on_since_ms = HAL_GetTick();
    this_unit_horn_active = true;
  }
  else if (this_unit_horn_active && (!button_now || !conditions_met)) {
    // Turn horn off: button released, ignition off, or starter engaged
    cmc_features_out_set_switch(switch_id, false);
    this_unit_horn_active = false;
  }

  // Update previous button state for next iteration
  button_prev_state = button_now;
}



