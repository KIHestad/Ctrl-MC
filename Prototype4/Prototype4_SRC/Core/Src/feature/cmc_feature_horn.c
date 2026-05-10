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
#include "app/cmc_app_state.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "feature/cmc_feature_horn.h"

// Local state for the horn feature, not exposed outside this module
static bool this_unit_horn_active = false;      // True if the horn is currently active (powered on)
static bool this_unit_feature_active = false;   // Set true if relevant in initialization, if false the horn logic will be inactive and do nothing
static uint8_t switch_id = 0xFF;                // The output index for the horn switch on this unit, set in initialization if the horn feature is enabled and the horn output device is enabled on this unit, used for controlling the horn output channel when needed
static uint32_t horn_on_since_ms = 0;           // Tick at which the horn was last turned on, used for auto shut-off timeout
static bool timeout_latched = false;            // Set true after timeout auto-off, cleared when horn button is released

void cmc_feature_horn_init(void) {
  // Check if the horn feature is enabled in the configuration and if this unit has the horn output device enabled, if not, this feature will be inactive and do nothing
  this_unit_feature_active = (cmc_config.feature_horn.enabled == 1) && cmc_util_out_is_device_enabled(CMC_OUT_HORN);
  if (this_unit_feature_active) {
      // Get the output index for the horn switch on this unit, used for controlling the horn output channel when needed
      switch_id = cmc_util_out_get_id(CMC_OUT_HORN);
      // Ensure the horn starts in the off state on initialization
      cmc_util_out_set_switch(switch_id, false);
  }
}

// Turn Horn on/off
void cmc_feature_horn_process() {

  // Feature is not configured or enabled on this unit, do nothing
  if (!this_unit_feature_active) {
      return;
  }

  // After timeout-triggered auto-off, require button release before allowing a new horn activation.
  if (timeout_latched) {
    if (!cmc_app_state.input.horn_button_pressed) {
      timeout_latched = false;
    }
    else {
      return;
    }
  }

  if (!this_unit_horn_active) {
    // Horn in currently off, if button pressed, ignition is on and starter not engaged - turn on the horn
    if (cmc_app_state.input.horn_button_pressed && cmc_app_state.vehicle.ignition_on && !cmc_app_state.vehicle.starter_engaged) {
      cmc_util_out_set_switch(switch_id, true); // Turn on the horn
      horn_on_since_ms = HAL_GetTick(); // Start timer for auto shut-off
      this_unit_horn_active = true; // Update local state
    }
  }
  else {
    // Horn is currently on, if button released, ignition turned off, starter engaged or auto shut-off timeout reached - turn off the horn
    bool time_overdue = (cmc_config.feature_horn.auto_shut_off_sec > 0U) &&
                        ((HAL_GetTick() - horn_on_since_ms) >= ((uint32_t)cmc_config.feature_horn.auto_shut_off_sec * 1000U));
    if (!cmc_app_state.input.horn_button_pressed || !cmc_app_state.vehicle.ignition_on || cmc_app_state.vehicle.starter_engaged || time_overdue) {
      cmc_util_out_set_switch(switch_id, false); // Turn off the horn
      this_unit_horn_active = false; // Update local state
      if (time_overdue) {
        timeout_latched = true;
      }
    }
  }
}



