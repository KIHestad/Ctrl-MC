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

#include "cmc_config_type.h"

// Default configuration values for the system, to be used used on first boot if none is found in flash and not reset
void cmc_config_defaults_load(void);

#endif /* CMC_CONFIG_DEFAULTS_H_ */

