/**
  *********************************************************************************************
  * @file      cmc_util_output.h
  * @brief     Output utility helpers for device availability checks on the active unit
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_OUTPUT_H_
#define CMC_UTIL_OUTPUT_H_

#include <stdbool.h>
#include <stdint.h>
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type_unit.h"

// Returns true only if the output device exists on the active unit and is enabled.
bool cmc_util_out_is_device_enabled(cmc_out_t device_id);
// Returns the output index (0-based) for the given device_id if it exists and is enabled on this unit, or 0xFF if not found or not enabled
uint8_t cmc_util_out_get_id(cmc_out_t device_id);
// Drives one physical PROFET output channel on or off using the hardware output mapping.
void cmc_util_out_set_switch(uint8_t switch_id, bool on);
// Returns true if the physical PROFET output channel is currently being driven on.
bool cmc_util_out_is_switch_on(uint8_t switch_id);

#endif /* CMC_UTIL_OUTPUT_H_ */
