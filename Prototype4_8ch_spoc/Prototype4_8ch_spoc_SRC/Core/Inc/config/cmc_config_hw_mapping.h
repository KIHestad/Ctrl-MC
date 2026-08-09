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
#define CMC_CONFIG_HW_OUT_COUNT 3 // Physical number of output channels possible for usage

// For mapping the hardware GPIO input pins
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} cmc_config_gpio_pin_t; 

// Hardware mapping for input pins, button 1 = item[0]
extern const cmc_config_gpio_pin_t cmc_config_hw_digital_in_mapping[CMC_CONFIG_HW_IN_DIGITAL_COUNT]; // tbd, to be defined in cmc_config_hw_mapping.c
extern const cmc_config_gpio_pin_t cmc_config_hw_analog_in_mapping[CMC_CONFIG_HW_IN_ANALOG_COUNT]; // tbd, to be defined in cmc_config_hw_mapping.c

// Switch type discriminator for the output channel mapping
typedef enum {
    CMC_CONFIG_SWITCH_TYPE_PROFET = 0, // Infineon PROFET: GPIO (IN/DEN/DSEL) + ADC IS pin
    CMC_CONFIG_SWITCH_TYPE_SPOC   = 1, // Infineon SPOC: SPI-controlled (future)
} cmc_config_switch_type_t;

// One logical output channel — PROFET fields used when switch_type == PROFET, SPOC fields when SPOC
typedef struct {
    cmc_config_switch_type_t switch_type;

    // PROFET fields:
    cmc_config_gpio_pin_t in_pin;       // IN or IN0 for dual channel
    cmc_config_gpio_pin_t den_pin;
    cmc_config_gpio_pin_t is_pin;       // IS analog diagnostic pin
    uint8_t               is_adc_rank;  // ADC1 scan rank (1-based) for this IS pin
    cmc_config_gpio_pin_t dsel_pin;     // DSEL for IS mux; leave {0} for single-channel
    bool                  dual_channel;
    uint8_t               dsel_value;   // DSEL GPIO state that selects this logical channel
    uint16_t              ilis_ratio;   // K_ILIS current mirror ratio (confirm from datasheet)
    uint16_t              ris_ohms;     // IS sense resistor in ohms (confirm from schematic)

    // SPOC fields (used when switch_type == CMC_CONFIG_SWITCH_TYPE_SPOC):
    uint8_t               spoc_channel; // channel address within the SPI daisy chain
    cmc_config_gpio_pin_t spoc_cs_pin;
} cmc_config_switch_t;

// Hardware mapping for output channels, channel 1 = item[0]
extern const cmc_config_switch_t cmc_config_hw_out_channel_mapping[CMC_CONFIG_HW_OUT_COUNT];

#endif /* CMC_CONFIG_HW_MAPPING_H_ */   