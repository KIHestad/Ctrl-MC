/**
  *********************************************************************************************
  * @file      cmc_config_hw_mapping.c
  * @brief     Hardware mapping configuration for input pins and output channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "main.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal_gpio.h"

// Hardware mapping for input pins, button 1 = item[0]
const cmc_config_gpio_pin_t cmc_config_hw_digital_in_mapping[CMC_CONFIG_HW_IN_DIGITAL_COUNT] = {
    [0] = {.port = BTN_1_GPIO_Port,  .pin = BTN_1_Pin},  // Input 1
    [1] = {.port = BTN_2_GPIO_Port,  .pin = BTN_2_Pin},  // Input 2
    [2] = {.port = BTN_3_GPIO_Port,  .pin = BTN_3_Pin},  // Input 3
    [3] = {.port = BTN_4_GPIO_Port,  .pin = BTN_4_Pin},  // Input 4
    [4] = {.port = BTN_5_GPIO_Port,  .pin = BTN_5_Pin},  // Input 5
    [5] = {.port = BTN_6_GPIO_Port,  .pin = BTN_6_Pin},  // Input 6
    [6] = {.port = BTN_7_GPIO_Port,  .pin = BTN_7_Pin},  // Input 7
    [7] = {.port = BTN_8_GPIO_Port,  .pin = BTN_8_Pin},  // Input 8
    [8] = {.port = BTN_9_GPIO_Port,  .pin = BTN_9_Pin},  // Input 9
    [9] = {.port = BTN_10_GPIO_Port, .pin = BTN_10_Pin}  // Input 10    
};

// Hardware mapping for analog input pins, item[0] = first analog input pin
const cmc_config_gpio_pin_t cmc_config_hw_analog_in_mapping[CMC_CONFIG_HW_IN_ANALOG_COUNT] = {
    [0] = {.port = SENSOR_ANALOG_GPIO_Port, .pin = SENSOR_ANALOG_Pin} // Analog Input 1
};


const cmc_config_infineon_profet_t cmc_config_hw_out_channel_mapping[CMC_CONFIG_HW_OUT_COUNT] = {
    [0] = { // Output channel 1 - Switch 1
        .in_pin =       {.port = SW1_IN_GPIO_Port, .pin = SW1_IN_Pin},
        .den_pin =      {.port = SW1_DEN_GPIO_Port, .pin = SW1_DEN_Pin},
        .is_pin =       {.port = SW1_IS_GPIO_Port, .pin = SW1_IS_Pin},
        .dual_channel = false,
    },
    [1] = { // Output channel 2 - Switch 2 (dual channel)
        .in_pin =       {.port = SW2_IN0_GPIO_Port, .pin = SW2_IN0_Pin},
        .den_pin =      {.port = SW2_DEN_GPIO_Port, .pin = SW2_DEN_Pin},
        .is_pin =       {.port = SW2_IS_GPIO_Port, .pin = SW2_IS_Pin},
        .dsel_pin =     {.port = SW2_DSEL_GPIO_Port, .pin = SW2_DSEL_Pin}, 
        .dual_channel = true,
        .dsel_value =   GPIO_PIN_RESET // LOW for channel 0 (IN0)
    },
    [2] = { // Output channel 3 - Switch 2 (dual channel)
        .in_pin =       {.port = SW2_IN1_GPIO_Port, .pin = SW2_IN1_Pin},
        .den_pin =      {.port = SW2_DEN_GPIO_Port, .pin = SW2_DEN_Pin},
        .is_pin =       {.port = SW2_IS_GPIO_Port, .pin = SW2_IS_Pin},
        .dsel_pin =     {.port = SW2_DSEL_GPIO_Port, .pin = SW2_DSEL_Pin}, 
        .dual_channel = true,
        .dsel_value =   GPIO_PIN_SET // HIGH for channel 1 (IN1)
    },
    [3] = { // Output channel 4 - Switch 3
        .in_pin =       {.port = SW3_IN_GPIO_Port, .pin = SW3_IN_Pin},
        .den_pin =      {.port = SW3_DEN_GPIO_Port, .pin = SW3_DEN_Pin},
        .is_pin =       {.port = SW3_IS_GPIO_Port, .pin = SW3_IS_Pin},
        .dual_channel = false,
    },
    [4] = { // Output channel 5 - Switch 4 (dual channel)
        .in_pin =       {.port = SW4_IN0_GPIO_Port, .pin = SW4_IN0_Pin},
        .den_pin =      {.port = SW4_DEN_GPIO_Port, .pin = SW4_DEN_Pin},
        .is_pin =       {.port = SW4_IS_GPIO_Port, .pin = SW4_IS_Pin},
        .dsel_pin =     {.port = SW4_DSEL_GPIO_Port, .pin = SW4_DSEL_Pin}, 
        .dual_channel = true,
        .dsel_value =   GPIO_PIN_RESET // LOW for channel 0 (IN0)
    },
    [5] = { // Output channel 6 - Switch 4 (dual channel)
        .in_pin =       {.port = SW4_IN1_GPIO_Port, .pin = SW4_IN1_Pin},
        .den_pin =      {.port = SW4_DEN_GPIO_Port, .pin = SW4_DEN_Pin},
        .is_pin =       {.port = SW4_IS_GPIO_Port, .pin = SW4_IS_Pin},
        .dsel_pin =     {.port = SW4_DSEL_GPIO_Port, .pin = SW4_DSEL_Pin}, 
        .dual_channel = true,
        .dsel_value =   GPIO_PIN_SET // HIGH for channel 1 (IN1)
    } 
};