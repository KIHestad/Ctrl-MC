/**
  *********************************************************************************************
  * @file      cmc_feature_horn.c
  * @brief     Horn feature control logic, manages horn activation based on input and configuration
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "feature/cmc_feature_horn.h"

static bool is_on = false;
static uint32_t turned_on_timestamp = 0;

// Init
void cmc_feature_horn_init(void) {
    // Ensure HORN starts turned off
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    is_blinking = false;
    led_is_on = false;
    next_transition_time = 0;
    blinks_remaining = 0;
    blink_on_duration_ms = 0;
    blink_off_duration_ms = 0;
}

// Turn LED on/off 
void cmc_onboard_led_set(bool on) {
    if (on) {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        is_blinking = false;
        led_is_on = true;
    } else {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        is_blinking = false;
        led_is_on = false;
        blinks_remaining = 0;
    }
}
