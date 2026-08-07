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

#include "app/cmc_app_logic.h"
#include "config/cmc_config_type.h"
#include <stdbool.h>

// Init
void cmc_config_manager_init(void);

// Manager methods
cmc_app_status_code_t cmc_config_manager_save_to_flash(const cmc_config_t* new_config);
cmc_app_status_code_t cmc_config_manager_load_from_flash(cmc_config_t* target);

#endif /* CMC_CONFIG_MANAGER_H_ */