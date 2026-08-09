/**
  *********************************************************************************************
  * @file      cmc_util_switch_profet_driver.h
  * @brief     Internal PROFET-specific implementation for cmc_util_switch_driver
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_SWITCH_PROFET_DRIVER_H_
#define CMC_UTIL_SWITCH_PROFET_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>
#include "util/cmc_util_switch_driver.h"

// Not part of the public API; included only by cmc_util_switch_driver.c

// Pulses IN low then DEN low->high on every PROFET channel to clear latched faults
void                 cmc_util_switch_profet_init(void);

// Drives IN (and forces DEN high) for a PROFET channel
void                 cmc_util_switch_profet_set(uint8_t ch, bool on);

// Returns true if the PROFET channel's IN pin is currently driven high
bool                 cmc_util_switch_profet_is_on(uint8_t ch);

// Scans all PROFET IS pins and caches raw readings; writes status for matching channels only
void                 cmc_util_switch_profet_sample_all(cmc_switch_status_t *status);

// Returns cached load current in mA from the last sample_all() call
int32_t              cmc_util_switch_profet_read_current_ma(uint8_t ch);

#endif /* CMC_UTIL_SWITCH_PROFET_DRIVER_H_ */
