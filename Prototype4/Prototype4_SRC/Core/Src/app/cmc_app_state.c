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

    // Read unit data from unit info flash store
    cmc_unit_info_init();

    // If unit info is not valid, blink LED and wait for user to set it via button presse before proceeding with the rest of initialization
    // The input number (input[0] = input nr 1) will be taken as unit id, so user can set unit id by pressing the corresponding button during startup
    if (!cmc_app_state.system.unit_info_valid) {
        cmc_onboard_led_blink(50, 950); 
        // Unit info invalid, run loop until unid_id is set from button press. Needs to ever lasting busy-wait loop unitl button press detected.
        // Without valid unit_id we can't proceed with the rest of initialization that relies on it.
        while (!cmc_app_state.system.unit_info_valid) {
            // Check buttons 1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS to allow user to set unit id via button presses
            for (uint8_t i = 0; i < CMC_CONFIG_MAX_SUPPORTED_IO_UNITS; i++) {
                if (HAL_GPIO_ReadPin(cmc_config_hw_digital_in_mapping[i].port,cmc_config_hw_digital_in_mapping[i].pin) == GPIO_PIN_RESET) {
                    // If button is pressed, set unit id to button index + 1 (to make it 1-based)
                    cmc_app_state.system.unit_info.unit_id = i + 1;
                    // Add correct signature to indicated valid unit info and save to flash
                    cmc_app_state.system.unit_info.signature = CMC_UNIT_INFO_SIGNATURE;
                    // save to flash now
                    cmc_unit_info_save();
                    break;                    
                }
            }
            cmc_onboard_led_process(); // Update LED state to reflect any changes (e.g., if user sets unit id, can change LED pattern to indicate success)            
        }
        // Go back to standard init led blinking pattern after unit info is valid
        cmc_onboard_led_startup(); 
    }

    // Set tick from HAL_GetTick() to track how long the system time took
    cmc_app_state.system.init_time_ms  = HAL_GetTick();

    // Set onboard LED to indicate success if no errors occured
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {
        // Blink unit id every 5 seconds to indicate success and show unit id, can be useful for debugging and user feedback
        cmc_onboard_led_blink_interval(cmc_app_state.system.unit_info.unit_id, 5000); 
    } 
}

