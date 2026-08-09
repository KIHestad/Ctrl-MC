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
// SPI protocol: Infineon BTS72220-4ESA, 2 chips daisy-chained on SPI1 (shared CSN + IS pin)

// Clears the OUT register (all channels off) on both chips; relies on power-on register defaults otherwise
void                 cmc_util_switch_spoc_init(void);

// Writes the OUT register bit for the channel's chip (immediate SPI transaction)
void                 cmc_util_switch_spoc_set(uint8_t ch, bool on);

// Returns the last commanded on/off state (shadow copy of the OUT register bit)
bool                 cmc_util_switch_spoc_is_on(uint8_t ch);

// Reads WRNDIAG/ERRDIAG for both chips, then round-robins DCR.MUX across all 8 channels to sample IS current
void                 cmc_util_switch_spoc_sample_all(cmc_switch_status_t *status);

// Returns cached load current in mA from the last sample_all() call; 0 when switch is off
int32_t              cmc_util_switch_spoc_read_current_ma(uint8_t ch);

#endif /* CMC_UTIL_SWITCH_SPOC_DRIVER_H_ */
