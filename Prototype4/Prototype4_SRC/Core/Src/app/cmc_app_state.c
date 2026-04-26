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
#include "util/cmc_util_button.h"
#include <string.h>

// The active app state machine instance
cmc_app_state_t cmc_app_state;

// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void) {

    // Only run if configuration is valid and status set to success
    if (cmc_app_state.system_status != CMC_SYSTEM_STATUS_SUCCESS) {
        return;
    }
    
    // Initialize button reading, sample initial GPIO states
    cmc_util_button_init();

    // Read unit data from unit info flash store
    cmc_unit_info_init();
    // If unit info is not valid, blink LED and wait for user to set it via button presses before proceeding with the rest of initialization, this ensures we have a valid unit id to work with for the rest of the system
    if (!cmc_app_state.unit_info_valid) {
        cmc_onboard_led_blink(50, 950); 
        // Unit info invalid, run loop until id is set from button press
        while (!cmc_app_state.unit_info_valid) {
            // Check buttons 1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS to allow user to set unit id via button presses
            for (uint8_t i = 0; i < CMC_CONFIG_MAX_SUPPORTED_IO_UNITS; i++) {
                if (HAL_GPIO_ReadPin(cmc_config_hw_digital_in_mapping[i].port,cmc_config_hw_digital_in_mapping[i].pin) == GPIO_PIN_RESET) {
                    // If button is pressed, set unit id to button index + 1 (to make it 1-based)
                    cmc_app_state.unit_info.unit_id = i + 1;
                    // Add correct signature to indicated valid unit info and save to flash
                    cmc_app_state.unit_info.signature = CMC_UNIT_INFO_SIGNATURE;
                    // save to flash now
                    cmc_unit_info_save(&cmc_app_state.unit_info);
                    break;                    
                }
            }
            cmc_onboard_led_process(); // Update LED state to reflect any changes (e.g., if user sets unit id, can change LED pattern to indicate success)            
        }
        // Go back to standard init led blinking pattern after unit info is valid
        cmc_onboard_led_startup(); 
    }

    // Config and unit info should be valid at this point, set this_unit
    this_unit = &cmc_config.io_unit[cmc_app_state.unit_info.unit_id - 1];

    // Set CANBUS interrupts to update app_state when relevant messages are received, not implemented yet


    // Set tick from HAL_GetTick() to track how long the system time took
    cmc_app_state.system_init_time_ms  = HAL_GetTick();

    // Set onboard LED to indicate success if no errors occured
    if (cmc_app_state.system_status == CMC_SYSTEM_STATUS_SUCCESS) {
        // Keep LED on for 10 sec to indicate success
        cmc_onboard_led_normal_operation();
    } 
}

