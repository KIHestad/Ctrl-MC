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
#include "stm32g4xx_hal_gpio.h"

// Returns true only if the output device exists on the active unit and is enabled.
bool cmc_util_out_is_device_enabled(cmc_config_out_device_t device_id) {
    
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
uint8_t cmc_util_out_get_id(cmc_config_out_device_t device_id) {
    
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

void cmc_util_out_set_switch(uint8_t switch_id, bool on) {

    // Get the hardware mapping for this output channel from the configuration
    const cmc_config_infineon_profet_t* channel = &cmc_config_hw_out_channel_mapping[switch_id];

    // Ensure the PROFET channel is enabled before driving its input command.
    HAL_GPIO_WritePin(channel->den_pin.port, channel->den_pin.pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(channel->in_pin.port, channel->in_pin.pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

bool cmc_util_out_is_switch_on(uint8_t switch_id) {

    // Get the hardware mapping for this output channel from the configuration
    const cmc_config_infineon_profet_t* channel = &cmc_config_hw_out_channel_mapping[switch_id];
    return HAL_GPIO_ReadPin(channel->in_pin.port, channel->in_pin.pin) == GPIO_PIN_SET;
}



