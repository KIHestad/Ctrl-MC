/**
  *********************************************************************************************
  * @file      cmc_app_state.c
  * @brief     Application state machine, stores the current state of the application 
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"  
#include "app/cmc_app_state.h"
#include "util/cmc_util_onboard_led.h"
#include "util/cmc_util_button.h"
#include <string.h>

// The active app state machine instance
cmc_app_state_t app_state;

// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void) {

    // Only run if configuration is valid and status set to success
    if (app_state.system_status != CMC_SYSTEM_STATUS_SUCCESS) {
        return;
    }

    // Initialize button reading, sample initial GPIO states
    cmc_util_button_init();

    // Set CANBUS interrupts to update app_state when relevant messages are received, not implemented yet



    // Set tick from HAL_GetTick() to track how long the system time took
    app_state.system_init_time_ms  = HAL_GetTick();

    // Set onboard LED to indicate success if no errors occured
    if (app_state.system_status == CMC_SYSTEM_STATUS_SUCCESS) {
        // Keep LED on for 10 sec to indicate success
        cmc_onboard_led_blink_multiple(1, 10000, 0);
    } 
}

