/**
  *********************************************************************************************
  * @file      cmc_app_state.h
  * @brief     Application state machine, stores the current state of the application 
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_APP_STATE_H
#define CMC_APP_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include "config/cmc_config_type.h"
#include "util/cmc_util_unit_info.h"

// Overall system status, used to track if the system is fully operational or if there are errors that need to be addressed, can be used to gate certain logic in the app processing loop
typedef enum {
    CMC_APP_STATE_STATUS_SUCCESS = 0,
    CMC_APP_STATE_STATUS_ERROR_CONFIG = 1,
    CMC_APP_STATE_STATUS_INVALID_FLASH_SIGNATURE = 2,
    CMC_APP_STATE_STATUS_INVALID_RAM_SIGNATURE = 3,
    CMC_APP_STATE_STATUS_INVALID_FLASH_CRC = 4,
    CMC_APP_STATE_STATUS_ERROR_SAVE_TO_FLASH = 5,
    CMC_APP_STATE_STATUS_ERROR_LOAD_FROM_FLASH = 6,
} cmc_app_state_status_t; 

// Main system state 
typedef struct {
  cmc_app_state_status_t status; // The status of the system
  cmc_unit_info_t unit_info;                           // This units info, espicially the unit id
  bool unit_info_valid;                                // True if unit_info was loaded from flash with a valid signature
  uint32_t init_time_ms;                        // The time for the system to do fully statup
    
} cmc_app_state_system_t;

// Main vehicle state
typedef struct {
    bool ignition_on; // True if ignition is on
    bool starter_engaged; // True if starter motor is engaged
} cmc_app_state_vehicle_t;

// Button readings
typedef struct {
    bool horn_button_pressed; // True if the horn button is currently pressed
} cmc_app_state_input_t;


// The main application state machine struct, holds the current state of the application
typedef struct {
    cmc_app_state_system_t system; // The overall system state, can be used to gate certain logic in the app processing loop if the system is not fully operational
    cmc_app_state_vehicle_t vehicle; // The current state of the vehicle, can be used for logic that depends on the state of the vehicle (eg: horn should not be on if ignition is off, etc)
    cmc_app_state_input_t input; // The current state of the inputs, can be used for logic that depends on the state of the inputs (eg: horn button pressed, etc)
} cmc_app_state_t;

// Global application state machine instance
extern cmc_app_state_t cmc_app_state;
 
// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void);

#endif /* CMC_APP_STATE_H */