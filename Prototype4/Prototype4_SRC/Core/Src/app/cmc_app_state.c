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
#include <string.h>

// The active app state machine instance
cmc_app_state_t app_state;

// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void) {

    // Set tick from HAL_GetTick() to track system startup time
    app_state.system_init_time_ms  = HAL_GetTick();
}

