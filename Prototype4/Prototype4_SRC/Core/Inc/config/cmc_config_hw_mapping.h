/**
  *********************************************************************************************
  * @file      cmc_config_hw_mapping.h
  * @brief     Hardware mapping configuration for input pins and output channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_HW_MAPPING_H_
#define CMC_CONFIG_HW_MAPPING_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32g4xx.h"

#define CMC_CONFIG_HW_IN_DIGITAL_COUNT 10 // Physical number of buttons possible for usage
#define CMC_CONFIG_HW_IN_ANALOG_COUNT 1 // Physical number of analog input channels possible for usage
#define CMC_CONFIG_HW_OUT_COUNT 6 // Physical number of output channels possible for usage

// For mapping the hardware GPIO input pins
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} cmc_config_gpio_pin_t; 

// Hardware mapping for input pins, button 1 = item[0]
extern const cmc_config_gpio_pin_t cmc_config_hw_digital_in_mapping[CMC_CONFIG_HW_IN_DIGITAL_COUNT]; // tbd, to be defined in cmc_config_hw_mapping.c
extern const cmc_config_gpio_pin_t cmc_config_hw_analog_in_mapping[CMC_CONFIG_HW_IN_ANALOG_COUNT]; // tbd, to be defined in cmc_config_hw_mapping.c

// For mapping the hardware output channels, for the infineon PROFET +2 high side switches
typedef struct {
    cmc_config_gpio_pin_t in_pin; // The GPIO pin used to control the output channel (turn on/off)
    cmc_config_gpio_pin_t den_pin; // The GPIO pin used to reset and control the is_pin
    cmc_config_gpio_pin_t is_pin; // The GPIO pin for reading analog diagnostic feedback from the output channel (current sensing)
    cmc_config_gpio_pin_t dsel_pin; // The first output pin that this channel controls (used for both single and dual channels)
    bool dual_channel; // Set to true if this output channel is a dual channel that controls two outputs, false if it controls one output
  uint8_t dsel_value; // GPIO_PIN_SET/GPIO_PIN_RESET value used for the dsel pin on dual channels
} cmc_config_infineon_profet_t;

// Hardware mapping for output channels, channel 1 = item[0]
extern const cmc_config_infineon_profet_t cmc_config_hw_out_channel_mapping[CMC_CONFIG_HW_OUT_COUNT]; // tbd, to be defined in cmc_config_hw_mapping.c

#endif /* CMC_CONFIG_HW_MAPPING_H_ */   