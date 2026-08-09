/**
  *********************************************************************************************
  * @file      cmc_config_defaults.h
  * @brief     Configuration defaults
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_DEFAULTS_H_
#define CMC_CONFIG_DEFAULTS_H_

#include "config/cmc_config_type.h"

// Public variable to control if the default config should be loaded on boot if missing in flash, or if it should wait for config to be loaded over CAN
extern const bool cmc_config_default_for_demo_use;
// The default configuration values for the system, to be used on first boot if none is found in flash and not reset
extern const cmc_config_t cmc_config_default_for_demo;


#endif /* CMC_CONFIG_DEFAULTS_H_ */

