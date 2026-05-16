/**
  *********************************************************************************************
  * @file      cmc_app_state_updater.h
  * @brief     Owns all writes to cmc_app_state — both from local inputs (TX path) and from
  *            incoming CAN messages (RX path). No other module should write to cmc_app_state.
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

// Update cmc_app_state from a locally scanned input and broadcast the change over CAN.
// Call once per button per main loop iteration, from cmc_input_scanner_execute.
void cmc_app_state_update(const cmc_config_in_t *config_in, cmc_input_button_state_t *in_state);

#endif /* CMC_APP_STATE_UPDATER_H_ */
