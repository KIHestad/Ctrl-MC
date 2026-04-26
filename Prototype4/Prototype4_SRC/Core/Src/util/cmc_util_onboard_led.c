/**
  *********************************************************************************************
  * @file      cmc_util_onboard_led.c
  * @brief     Onboard LED control for status indication
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_onboard_led.h"

static bool is_blinking = false;
static uint32_t turn_off_time = 0;
static bool led_is_on = false;
static uint32_t next_transition_time = 0;
static uint32_t blinks_remaining = 0;
static uint32_t blink_on_duration_ms = 0;
static uint32_t blink_off_duration_ms = 0;
static uint32_t error_blink_total = 0; // >0 means error-blink mode: burst of N blinks then 2s pause, repeat

// Init
void cmc_onboard_led_init(void) {
    // Ensure LED starts turned off
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    // Show startup LED blinking pattern, to be changed according to results of initialization steps
    cmc_onboard_led_startup(); 
}

// Turn LED on/off 
void cmc_onboard_led_set(bool on) {
    if (on) { // turn on
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    } else { // turn off
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        blinks_remaining = 0;
        error_blink_total = 0;
    }
    led_is_on = on;
    is_blinking = false;
}

// Normal startup patter, tiny fast blinking
void cmc_onboard_led_startup(void) {
    cmc_onboard_led_blink(50,150); 
}

// Normal operation pattern, tiny blink once every minute
void cmc_onboard_led_normal_operation(void) {
    cmc_onboard_led_blink(50, 4950); 
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
void cmc_onboard_led_blink_multiple(uint32_t num_of_blinks, uint32_t duration_on_ms, uint32_t duration_off_ms) {
    if ((num_of_blinks == 0U) || (duration_on_ms == 0U)) {
        cmc_onboard_led_set(false); // Invalid durations, turn off LED
        return;
    }
    error_blink_total = 0; // Cancel any active error blink mode
    uint32_t now = HAL_GetTick();
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    is_blinking = true;
    blinks_remaining = num_of_blinks;
    blink_on_duration_ms = duration_on_ms;
    blink_off_duration_ms = duration_off_ms;
    next_transition_time = now + duration_on_ms;
}

// Error blinking pattern, will blink infinite but a repeating pattern of x quick blinks followed by a 2 second pause, where x is the error code number (e.g., 3 blinks for error code 3)
void cmc_onboard_led_blink_error(uint32_t num_of_error_blinks) {
    if (num_of_error_blinks == 0U) {
        num_of_error_blinks = 1; // Avoid zero blinks, use 1 blink for error code 0
    }
    error_blink_total = num_of_error_blinks;
    uint32_t now = HAL_GetTick();
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    is_blinking = true;
    led_is_on = true;
    blinks_remaining = num_of_error_blinks;
    blink_on_duration_ms = 100;
    blink_off_duration_ms = 400;
    next_transition_time = now + 100;
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
            if (error_blink_total > 0U) {
                // Error mode: pause 2 seconds then restart the burst
                blinks_remaining = error_blink_total;
                next_transition_time = now + 2000;
            } else {
                is_blinking = false;
                next_transition_time = 0;
            }
        } else {
            next_transition_time = now + blink_off_duration_ms;
        }
    } else {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        led_is_on = true;
        next_transition_time = now + blink_on_duration_ms;
    }
}