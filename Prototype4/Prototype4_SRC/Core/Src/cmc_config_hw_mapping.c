/**
  *********************************************************************************************
  * @file      cmc_config_hw_mapping.c
  * @brief     Hardware mapping configuration for input pins and output channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "main.h"
#include "cmc_config_type.h"
#include "stm32g4xx_hal_gpio.h"

/* ====================================================================
 * HARDWARE MAPPING CONFIGURATION
 * This file defines the default mapping of physical input pins and output 
 * channels to the logical buttons/switches and equipment in the system.
 * ==================================================================== */

// Array for each button supported  and which physical pin it's connected to, and how it should be interpreted (eg: toggle, classic, etc)
const cmc_config_hw_pin_t cmc_input_pin_mapping[10] = {
    { .port = BTN_1_GPIO_Port, .pin = BTN_1_Pin }, 
    { .port = BTN_2_GPIO_Port, .pin = BTN_2_Pin }, 
    { .port = BTN_3_GPIO_Port, .pin = BTN_3_Pin }, 
    { .port = BTN_4_GPIO_Port, .pin = BTN_4_Pin }, 
    { .port = BTN_5_GPIO_Port, .pin = BTN_5_Pin }, 
    { .port = BTN_6_GPIO_Port, .pin = BTN_6_Pin }, 
    { .port = BTN_7_GPIO_Port, .pin = BTN_7_Pin }, 
    { .port = BTN_8_GPIO_Port, .pin = BTN_8_Pin }, 
    { .port = BTN_9_GPIO_Port, .pin = BTN_9_Pin }, 
    { .port = BTN_10_GPIO_Port, .pin = BTN_10_Pin }

};

// Array for each output switch supported (10) and which physical pin it's connected to, and how it should be interpreted (eg: toggle, classic, etc)
// const cmc_config_hw_pin_t hw_output_switch_t[10] = {
//     { .port = OUT_1_GPIO_Port, .pin = OUT_1_Pin }, 
//     { .port = OUT_2_GPIO_Port, .pin = OUT_2_Pin }, 
//     { .port = OUT_3_GPIO_Port, .pin = OUT_3_Pin }, 
//     { .port = OUT_4_GPIO_Port, .pin = OUT_4_Pin }, 
//     { .port = OUT_5_GPIO_Port, .pin = OUT_5_Pin }, 
//     { .port = OUT_6_GPIO_Port, .pin = OUT_6_Pin }, 
//     { .port = OUT_7_GPIO_Port, .pin = OUT_7_Pin }, 
//     { .port = OUT_8_GPIO_Port, .pin = OUT_8_Pin }, 
//     { .port = OUT_9_GPIO_Port, .pin = OUT_9_Pin }, 
//     { .port = OUT_10_GPIO_Port, .pin = OUT_10_Pin }

// };
