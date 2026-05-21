/**
  *********************************************************************************************
  * @file      cmc_app_state_updater.h
  * @brief     Write gateway for raw input state in cmc_app_state. Handles two paths:
  *              1. CAN RX  — incoming CAN frames update local cmc_app_state (no re-broadcast)
  *              2. Raw input — button/sensor changes from cmc_input_scanner update
  *                            cmc_app_state and broadcast over CAN
  *            Feature modules that compute logical/derived state own their own fields in
  *            cmc_app_state and write them directly from their process() function, using
  *            a private static publish function within the feature module itself.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_APP_STATE_UPDATER_H_
#define CMC_APP_STATE_UPDATER_H_

#include <stdint.h>
#include "config/cmc_config_type.h"
#include "input/cmc_input.h"

// Register the CAN RX callback that updates cmc_app_state from incoming CAN messages.
// Call once at system initialisation, after cmc_can_manager_init.
void cmc_app_state_updater_init(void);

// Update cmc_app_state from a locally scanned button/sensor and broadcast the change over
// CAN. Called once per input per main loop iteration from cmc_input_scanner_execute.
void cmc_app_state_update(const cmc_config_in_t *config_in, cmc_input_button_state_t *in_state);

#endif /* CMC_APP_STATE_UPDATER_H_ */
