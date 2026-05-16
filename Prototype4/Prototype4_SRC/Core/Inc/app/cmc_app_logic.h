/**
  *********************************************************************************************
  * @file      cmc_app_logic.h
  * @brief     Application logic for initialization and processing loop
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_APP_LOGIC_H
#define CMC_APP_LOGIC_H

#include <stdbool.h>

// Overall system status, used to track if the system is fully operational or if there are errors that need to be addressed, can be used to gate certain logic in the app processing loop
typedef enum {
    CMC_APP_STATE_STATUS_SUCCESS = 0,
    CMC_APP_STATE_STATUS_CONFIG_FLASH_SIGNATURE_INVALID = 1,
    CMC_APP_STATE_STATUS_CONFIG_RAM_SIGNATURE_INVALID = 2,
    CMC_APP_STATE_STATUS_CONFIG_FLASH_CRC_INVALID = 3,
    CMC_APP_STATE_STATUS_CONFIG_SAVE_TO_FLASH_ERROR = 4,
    CMC_APP_STATE_STATUS_CONFIG_LOAD_FROM_FLASH_ERROR = 5,
    CMC_APP_STATE_STATUS_UNIT_INFO_SAVE_ERROR = 6,
    CMC_APP_STATE_STATUS_UNIT_INFO_CRC_INVALID  = 7,
} cmc_app_state_status_t; 

// Main system info, the status and unit info
typedef struct {
  bool success;                   // Success flag, true if the system is fully operational and there are no errors, false if there are errors that need to be addressed 
  cmc_app_state_status_t status;  // The status of the system, should be CMC_APP_STATE_STATUS_SUCCESS when success is true, otherwise should be one of the error status codes that indicate what the error is
} cmc_app_state_t;

// Global application system status
extern cmc_app_state_t   cmc_app_state;

// Public functions for application logic - main init and main loop 
void cmc_app_init(void);
void cmc_app_process(void);

#endif /* CMC_APP_LOGIC_H */