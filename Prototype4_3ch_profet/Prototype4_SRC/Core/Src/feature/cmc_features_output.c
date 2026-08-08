/**
  *********************************************************************************************
  * @file      cmc_features_output.c
  * @brief     Output helpers for device availability checks on the active unit
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "feature/cmc_features_output.h"
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type.h"
#include "util/cmc_util_switch_driver.h"
#include "stm32g4xx_hal_gpio.h"

// Returns true only if the output device exists on the active unit and is enabled.
bool cmc_features_out_is_device_enabled(cmc_config_out_device_t device_id) {
    
    // Loop over the outputs configured on this unit and check if the given device_id is both present and enabled
    for (uint8_t i = 0; i < cmc_config_this_unit->out_used; i++) {
        if (cmc_config_this_unit->out[i].device_id == (uint8_t)device_id) {
            if (cmc_config_this_unit->out[i].enabled == 1U) {
                return true;
            }
        }
    }
    return false;
}

// Returns true only if the output device exists on the active unit and is enabled.
uint8_t cmc_features_out_get_device_id(cmc_config_out_device_t device_id) {
    
    // Loop over the outputs configured on this unit and check if the given device_id is both present and enabled
    for (uint8_t i = 0; i < cmc_config_this_unit->out_used; i++) {
        if (cmc_config_this_unit->out[i].device_id == (uint8_t)device_id) {
            if (cmc_config_this_unit->out[i].enabled == 1U) {
                return i;
            }
        }
    }
    return 0xFF; // Return 0xFF if the device is not found or not enabled
}

void cmc_features_out_set_switch(uint8_t switch_id, bool on) {
    cmc_util_switch_set(switch_id, on);
}

bool cmc_features_out_is_switch_on(uint8_t switch_id) {
    return cmc_util_switch_is_on(switch_id);
}

void cmc_features_out_init_all(void) {
    cmc_util_switch_init();
}



