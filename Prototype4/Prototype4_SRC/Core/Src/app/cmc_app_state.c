/**
  *********************************************************************************************
  * @file      cmc_app_state.c
  * @brief     Application state machine, stores the current state of the application 
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"  
#include "config/cmc_config_hw_mapping.h"
#include "app/cmc_app_state.h"
#include "util/cmc_util_onboard_led.h"
#include "input/cmc_input.h"
#include "feature/cmc_features_manager.h"
#include <string.h>

// The active app state machine instance
cmc_app_state_t cmc_app_state;

// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void) {

    // Set default values for the app state machine
    // TODO
    cmc_app_state.vehicle.ignition_on = true; // Set to true for testing, later add logic from config to dertermin if software ignition state should be tracked and used in the system
    cmc_app_state.vehicle.starter_engaged = false; // Set to false for testing, should be replaced with feature

    // Set tick from HAL_GetTick() to track how long the system time took
    cmc_app_state.system.init_time_ms  = HAL_GetTick();

    // Set onboard LED to indicate success if no errors occured
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {
        // Blink unit id every 5 seconds to indicate success and show unit id, can be useful for debugging and user feedback
        cmc_onboard_led_blink_interval(cmc_app_state.system.unit_info.unit_id, 5000); 
    } 
}

