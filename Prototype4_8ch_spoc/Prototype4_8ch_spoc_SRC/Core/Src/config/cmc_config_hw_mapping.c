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
    // TODO: curently not in use
    [0] = {.port = GPIOB, .pin = GPIO_PIN_15} // PB15 = ADC2_IN15
};

// Board-wide ADC1 scan ranks for VREFINT/TEMPSENSOR (see MX_ADC1_Init() in main.c)
// If ADC2 is to be used instead for reading these values, the ranks must be updated in MX_ADC2_Init() and the cmc_util_mcu_driver.c code must be modified to use ADC2 instead of ADC1.
const uint8_t cmc_config_hw_vref_adc_rank       = 2U;
const uint8_t cmc_config_hw_tempsensor_adc_rank = 3U;

// hardware mapping for SPOC switches
// Shared CSN for the whole 2-chip SPOC daisy chain (SPI1, software-controlled NSS)
const cmc_config_gpio_pin_t cmc_config_hw_spoc_cs_pin   = {.port = SW_CSN_GPIO_Port,  .pin = SW_CSN_Pin};
// Shared current-sense pin, multiplexed across all 8 channels via SPI (DCR.MUX), read on ADC1 rank 1
const cmc_config_gpio_pin_t cmc_config_hw_spoc_is_pin   = {.port = SW_IS_GPIO_Port,   .pin = SW_IS_Pin};
const uint8_t               cmc_config_hw_spoc_is_adc_rank = 1U;
// SPI1 bus pins; informational only, actual routing is done by CubeMX in MX_SPI1_Init()
const cmc_config_gpio_pin_t cmc_config_hw_spoc_sclk_pin = {.port = SW_SCLK_GPIO_Port, .pin = SW_SCLK_Pin};
const cmc_config_gpio_pin_t cmc_config_hw_spoc_miso_pin = {.port = SW_MISO_GPIO_Port, .pin = SW_MISO_Pin};
const cmc_config_gpio_pin_t cmc_config_hw_spoc_mosi_pin = {.port = SW_MOSI_GPIO_Port, .pin = SW_MOSI_Pin};


// Hardware mapping for output channels, channel 1 = item[0]
const cmc_config_switch_t cmc_config_hw_out_channel_mapping[CMC_CONFIG_HW_OUT_COUNT] = {

    // 2x BTS72220-4ESA (SPOC) daisy-chained on SPI1, 4 channels each = 8 total.
    // Channels 0 and 3 of each chip are the 7 A outputs (KILIS=5500 typ.)
    // Channels 1 and 2 of each chip are the 4 A outputs (KILIS=2500 typ.)
    // Ref datasheet Table 1. RSENSE = 1.2 kOhm shared
    // IS pin (SW_IS) for both chips, current-sense-multiplexed via SPI (DCR.MUX).
    [0] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 0, .ilis_ratio = 5500, .ris_ohms = 1200 },
    [1] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 1, .ilis_ratio = 2500, .ris_ohms = 1200 },
    [2] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 2, .ilis_ratio = 2500, .ris_ohms = 1200 },
    [3] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 3, .ilis_ratio = 5500, .ris_ohms = 1200 },
    [4] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 4, .ilis_ratio = 5500, .ris_ohms = 1200 },
    [5] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 5, .ilis_ratio = 2500, .ris_ohms = 1200 },
    [6] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 6, .ilis_ratio = 2500, .ris_ohms = 1200 },
    [7] = { .switch_type = CMC_CONFIG_SWITCH_TYPE_SPOC, .spoc_channel = 7, .ilis_ratio = 5500, .ris_ohms = 1200 },

    // Sample configuration for 3 output channels for Profet switches, using 2 dual-channel PROFET switches and 1 single-channel PROFET switch. 
    // Uncomment and modify as needed for your specific hardware setup.
    // [0] = { // Output channel 1 - Switch 2 dual channel 0
    //     .switch_type  = CMC_CONFIG_SWITCH_TYPE_PROFET,
    //     .in_pin       = {.port = SW2_IN0_GPIO_Port, .pin = SW2_IN0_Pin},
    //     .den_pin      = {.port = SW2_DEN_GPIO_Port, .pin = SW2_DEN_Pin},
    //     .is_pin       = {.port = SW2_IS_GPIO_Port,  .pin = SW2_IS_Pin},
    //     .is_adc_rank  = 2,
    //     .dsel_pin     = {.port = SW2_DSEL_GPIO_Port, .pin = SW2_DSEL_Pin},
    //     .dual_channel = true,
    //     .dsel_value   = GPIO_PIN_RESET, // LOW selects channel 0 (IN0)
    //     .ilis_ratio   = 3700, // BTS7020-2EPA K_ILIS confirmed from datasheet
    //     .ris_ohms     = 1200, // Rsense2 = 1.2k from schematic
    // },
    // [1] = { // Output channel 2 - Switch 2 dual channel 1
    //     .switch_type  = CMC_CONFIG_SWITCH_TYPE_PROFET,
    //     .in_pin       = {.port = SW2_IN1_GPIO_Port, .pin = SW2_IN1_Pin},
    //     .den_pin      = {.port = SW2_DEN_GPIO_Port, .pin = SW2_DEN_Pin},
    //     .is_pin       = {.port = SW2_IS_GPIO_Port,  .pin = SW2_IS_Pin},
    //     .is_adc_rank  = 2,
    //     .dsel_pin     = {.port = SW2_DSEL_GPIO_Port, .pin = SW2_DSEL_Pin},
    //     .dual_channel = true,
    //     .dsel_value   = GPIO_PIN_SET,   // HIGH selects channel 1 (IN1)
    //     .ilis_ratio   = 3700, // BTS7020-2EPA K_ILIS confirmed from datasheet
    //     .ris_ohms     = 1200, // Rsense2 = 1.2k from schematic
    // },
    // [2] = { // Output channel 3 - Switch 1 single channel
    //     .switch_type  = CMC_CONFIG_SWITCH_TYPE_PROFET,
    //     .in_pin       = {.port = SW1_IN_GPIO_Port,  .pin = SW1_IN_Pin},
    //     .den_pin      = {.port = SW1_DEN_GPIO_Port, .pin = SW1_DEN_Pin},
    //     .is_pin       = {.port = SW1_IS_GPIO_Port,  .pin = SW1_IS_Pin},
    //     .is_adc_rank  = 1,
    //     .dual_channel = false,
    //     .ilis_ratio   = 20000, // BTS7004-1EPP K_ILIS confirmed from datasheet
    //     .ris_ohms     = 1200,  // Rsense2 = 1.2k from schematic 
    // },
};
