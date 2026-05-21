/**
  *********************************************************************************************
  * @file      cmc_features_output.h
  * @brief     Output utility helpers for device availability checks on the active unit
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURES_OUTPUT_H_
#define CMC_FEATURES_OUTPUT_H_

#include <stdbool.h>
#include <stdint.h>
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type_unit.h"

// Returns true only if the output device exists on the active unit and is enabled.
bool cmc_features_out_is_device_enabled(cmc_config_out_device_t device_id);

// Returns the output index (0-based) for the given device_id if it exists and is enabled on this unit, or 0xFF if not found or not enabled
uint8_t cmc_features_out_get_device_id(cmc_config_out_device_t device_id);

// Clears any latched fault on all PROFET channels at startup by pulsing DEN LOW then HIGH.
void cmc_features_out_init_all(void);

// Drives one physical PROFET output channel on or off using the hardware output mapping.
void cmc_features_out_set_switch(uint8_t switch_id, bool on);

// Returns true if the physical PROFET output channel is currently being driven on.
bool cmc_features_out_is_switch_on(uint8_t switch_id);

#endif /* CMC_FEATURES_OUTPUT_H_ */
