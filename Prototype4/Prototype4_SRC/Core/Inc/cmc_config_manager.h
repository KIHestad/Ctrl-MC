/**
  *********************************************************************************************
  * @file      cmc_config_manager.h
  * @brief     Configuration manager for handling loading, validating, and saving system configuration
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_MANAGER_H_
#define CMC_CONFIG_MANAGER_H_

#include "cmc_config_type.h"
#include <stdbool.h>

/* ====================================================================
 * PUBLIC FUNCTIONS (The API for the rest of the motorcycle)
 * ==================================================================== */

// Called exactly once when the STM32 boots up
bool cmc_config_manager_init(void);

// Mathematically verifies the memory using the CRC hardware
bool cmc_config_manager_validate(cmc_config_t* target_config);

// Writes a newly received web configuration into the STM32 Flash
bool cmc_config_manager_save_to_flash(cmc_config_t* new_config);

#endif /* CMC_CONFIG_MANAGER_H_ */