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

#include "feature/cmc_feature_horn.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "util/cmc_util_output.h"
#include "util/cmc_util_onboard_led.h"

// Local state for the horn feature, not exposed outside this module
static bool this_unit_horn_active = false; // True if the horn is currently active (powered on)
static bool this_unit_feature_active = false;  // Set true if relevant in initialization, if false the horn logic will be inactive and do nothing
static uint8_t switch_id = 0xFF; // The output index for the horn switch on this unit, set in initialization if the horn feature is enabled and the horn output device is enabled on this unit, used for controlling the horn output channel when needed

void cmc_feature_horn_init(void) {
    // Check if the horn feature is enabled in the configuration and if this unit has the horn output device enabled, if not, this feature will be inactive and do nothing
    this_unit_feature_active = cmc_config.feature_horn.enabled && cmc_util_out_is_device_enabled(CMC_OUT_HORN);
    if (this_unit_feature_active) {
        // Get the output index for the horn switch on this unit, used for controlling the horn output channel when needed
        switch_id = cmc_util_out_get_id(CMC_OUT_HORN);
        // Ensure the horn starts in the off state on initialization
        // TODO        
    }
}

// Turn Horn on/off
void cmc_feature_horn_process() {
  
  // Compare this units horn active state with the app state
  // The app state is set from input processing logic or received from other unit from CANBUS
  if (!this_unit_feature_active || this_unit_horn_active == cmc_app_state.input.horn_button_pressed) {
    // Feature is not present or active, or no change in state, do nothing
    return;
  }
  
  // Horn feature logic
  // Horn is configured and enabled on this unit, check if it should be turned on or off based on logic
  bool this_unit_horn_active_new_status = false; // Default to off, only turn on if conditions are met below
  if (cmc_app_state.vehicle.ignition_on && !cmc_app_state.vehicle.starter_engaged && cmc_app_state.input.horn_button_pressed) {
    this_unit_horn_active_new_status = true;
  }

  // Check for change in horn active state, if changed, update the state and send CAN message to other units to inform them of the change if needed
  if (this_unit_horn_active != this_unit_horn_active_new_status) {

    // Turn on of off the horn output on this unit based on the new status, not implemented yet, just update the state variable for now
    // Send signal to Infion Profet switches

    
    // TODO: Send CAN message to other units to inform them of the horn state change if needed, not implemented yet

    // Update the horn active state for this unit
    this_unit_horn_active = this_unit_horn_active_new_status;
    
    // temp code to turn onboard led on when horn is active for testing, remove when actual horn output control is implemented
    cmc_onboard_led_set(this_unit_horn_active);
  }


}
   


