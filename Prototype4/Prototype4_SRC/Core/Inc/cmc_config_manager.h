#ifndef CMC_CONFIG_MANAGER_H_
#define CMC_CONFIG_MANAGER_H_

#include "cmc_config_type.h"
#include <stdbool.h>

/* ====================================================================
 * PUBLIC FUNCTIONS (The API for the rest of the motorcycle)
 * ==================================================================== */

// Called exactly once when the STM32 boots up
bool CMC_ConfigManager_Init(void);

// Mathematically verifies the memory using the CRC hardware
bool CMC_ConfigManager_Validate(cmc_global_config_t* target_config);

// Writes a newly received web configuration into the STM32 Flash
bool CMC_ConfigManager_SaveToFlash(cmc_global_config_t* new_config);

#endif /* CMC_CONFIG_MANAGER_H_ */