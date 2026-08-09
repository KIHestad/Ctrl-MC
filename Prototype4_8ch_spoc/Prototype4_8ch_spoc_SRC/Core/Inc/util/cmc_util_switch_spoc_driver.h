/**
  *********************************************************************************************
  * @file      cmc_util_switch_spoc_driver.h
  * @brief     Internal SPOC-specific implementation for cmc_util_switch_driver
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_SWITCH_SPOC_DRIVER_H_
#define CMC_UTIL_SWITCH_SPOC_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>
#include "util/cmc_util_switch_driver.h"

// Not part of the public API; included only by cmc_util_switch_driver.c
// SPI register/command protocol is not yet defined — see cmc_util_switch_spoc_driver.c

// Placeholder init; no SPI transaction yet
void                 cmc_util_switch_spoc_init(void);

// Placeholder set; tracks commanded state only, no SPI transaction yet
void                 cmc_util_switch_spoc_set(uint8_t ch, bool on);

// Returns the last commanded on/off state (not read back from hardware yet)
bool                 cmc_util_switch_spoc_is_on(uint8_t ch);

// Placeholder sample; no SPI diagnostic read yet, status left unchanged
void                 cmc_util_switch_spoc_sample_all(cmc_switch_status_t *status);

// Not yet implemented; always returns CMC_SWITCH_NOT_SUPPORTED
int32_t              cmc_util_switch_spoc_read_current_ma(uint8_t ch);

#endif /* CMC_UTIL_SWITCH_SPOC_DRIVER_H_ */
