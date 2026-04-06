#include "cmc_output_onboard_led.h"

static bool is_blinking = false;
static uint32_t turn_off_time = 0;
static bool led_is_on = false;
static uint32_t next_transition_time = 0;
static uint32_t blinks_remaining = 0;
static uint32_t blink_on_duration_ms = 0;
static uint32_t blink_off_duration_ms = 0;

void cmc_output_onboard_led_init(void) {
    // Ensure LED starts turned off
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    is_blinking = false;
    led_is_on = false;
    next_transition_time = 0;
    blinks_remaining = 0;
    blink_on_duration_ms = 0;
    blink_off_duration_ms = 0;
}

void cmc_output_onboard_led_blink_once(uint32_t duration_ms) {
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET); // Turn ON
    turn_off_time = HAL_GetTick() + duration_ms;             // Calculate future off-time
    is_blinking = true;
    led_is_on = true;
    blinks_remaining = 0;
    next_transition_time = 0;
}

void cmc_output_onboard_led_blink_multiple(uint32_t numOfBlinks, uint32_t duration_on_ms, uint32_t duration_off_ms) {
    if ((numOfBlinks == 0U) || (duration_on_ms == 0U)) {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        is_blinking = false;
        led_is_on = false;
        blinks_remaining = 0;
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

void cmc_output_onboard_led_process(void) {
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