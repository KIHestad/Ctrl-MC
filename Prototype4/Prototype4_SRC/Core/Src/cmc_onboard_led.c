/**
  *********************************************************************************************
  * @file      cmc_onboard_led.c
  * @brief     Onboard LED control for status indication
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "cmc_onboard_led.h"

static bool is_blinking = false;
static uint32_t turn_off_time = 0;
static bool led_is_on = false;
static uint32_t next_transition_time = 0;
static uint32_t blinks_remaining = 0;
static uint32_t blink_on_duration_ms = 0;
static uint32_t blink_off_duration_ms = 0;

// Init
void cmc_onboard_led_init(void) {
    // Ensure LED starts turned off
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

// Blink repeatedly with specified on/off durations
void cmc_onboard_led_blink(uint32_t duration_on_ms, uint32_t duration_off_ms) {
    cmc_onboard_led_blink_multiple(0xFFFFFFFF, duration_on_ms, duration_off_ms); // Effectively infinite    
}

// Blink once for a specified duration (ms)
void cmc_onboard_led_blink_once(uint32_t duration_ms) {
    cmc_onboard_led_blink_multiple(1, duration_ms, 0); // Blink once    
}

// Blink multiple times with specified on/off durations
void cmc_onboard_led_blink_multiple(uint32_t numOfBlinks, uint32_t duration_on_ms, uint32_t duration_off_ms) {
    if ((numOfBlinks == 0U) || (duration_on_ms == 0U)) {
        cmc_onboard_led_set(false); // Invalid durations, turn off LED
        return;
    }
    uint32_t now = HAL_GetTick();
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    is_blinking = true;
    blinks_remaining = numOfBlinks;
    blink_on_duration_ms = duration_on_ms;
    blink_off_duration_ms = duration_off_ms;
    next_transition_time = now + duration_on_ms;
}

// process function to be called regularly from main loop to handle LED state updates
void cmc_onboard_led_process(void) {
    if (!is_blinking) {
        return;
    }
    uint32_t now = HAL_GetTick();
    if (blinks_remaining == 0U) {
        if (now >= turn_off_time) {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
            is_blinking = false;
            led_is_on = false;
        }
        return;
    }
    if (now < next_transition_time) {
        return;
    }
    if (led_is_on) {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        led_is_on = false;
        blinks_remaining--;
        if (blinks_remaining == 0U) {
            is_blinking = false;
            next_transition_time = 0;
        } else {
            next_transition_time = now + blink_off_duration_ms;
        }
    } else {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        led_is_on = true;
        next_transition_time = now + blink_on_duration_ms;
    }
}