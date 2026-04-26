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
    CMC_SYSTEM_STATUS_SUCCESS = 0,
    CMC_SYSTEM_STATUS_ERROR_GENERIC = 10,
    CMC_SYSTEM_STATUS_ERROR_CONFIG = 11,
} state_system_status_t;

// Button state structure for debouncing and event detection
typedef struct {
  // Debounce internals
  bool     raw;                   // Last raw GPIO read
  uint32_t raw_last_change_ms;  // HAL_GetTick() at last raw reading change, used for debouncing
  bool     is_pressed;            // Debounced: currently pressed
  bool     is_held;               // Debounced: true while button is being held past threshold
  
  // Event counters, only increment, never reset to enable multiple features to identify new events, 
  // consuming events needs to be managed in the feature logic
  uint32_t click_count;         // Incremented on confirmed single-click
  uint32_t double_click_count;  // Incremented on confirmed double-click
  uint32_t hold_count;          // Incremented when hold threshold is reached
} cmc_button_state_t;

// The main application state machine struct, holds the current state of the application
typedef struct {
  cmc_config_status_t config_status;   // The status of the configuration set at startup
  state_system_status_t system_status; // The status of the system
  bool unit_info_valid;                // True if unit_info was loaded from flash with a valid signature
  cmc_unit_info_t unit_info;           // This units info, espicially the unit id
  uint32_t system_init_time_ms;        // The time for the system to do fully statup
  
  cmc_button_state_t button[10];  // Button states
} cmc_app_state_t;

// Global application state machine instance
extern cmc_app_state_t cmc_app_state;
 
// Initialize the application state machine, set all fields to default values (false/0)
void cmc_app_state_init(void);

#endif /* CMC_APP_STATE_H */