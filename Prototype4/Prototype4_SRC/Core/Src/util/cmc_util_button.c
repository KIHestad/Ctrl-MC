/**
  *********************************************************************************************
  * @file      cmc_util_button.c
  * @brief     Button reading, debouncing and event detection (click, double-click, hold)
  *            Reads GPIO pins via cmc_config_hw_digital_in_mapping and updates app_state.button[]
  *            All buttons are active-low (pulled up, pressed reads GPIO_PIN_RESET)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_button.h"
#include "app/cmc_app_state.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal.h"

// Internal state per button needed for event detection timing (not exposed in app_state)
typedef struct {
    uint32_t press_start_ms;      // Tick when debounced press began (for hold detection)
    uint32_t last_release_ms;     // Tick of last debounced release (for double-click gap)
    bool     hold_fired;          // True once hold_count has been incremented for this press
    bool     awaiting_2nd_click;  // True while waiting to see if a second click arrives
    uint32_t pending_click_ms;    // Tick when the first click released (start of dblclick window)
} cmc_btn_internal_t;

static cmc_btn_internal_t btn_int[CMC_CONFIG_HW_IN_DIGITAL_COUNT];

// Read one button GPIO, returns true if button is physically pressed (active-low)
static bool read_button_raw(uint8_t index) {
    return HAL_GPIO_ReadPin(
        cmc_config_hw_digital_in_mapping[index].port,
        cmc_config_hw_digital_in_mapping[index].pin
    ) == GPIO_PIN_RESET;
}

// Initialize: sample current GPIO state as both raw and debounced, clear all counters
void cmc_util_button_init(void) {
    uint32_t now = HAL_GetTick();
    for (uint8_t i = 0; i < CMC_CONFIG_HW_IN_DIGITAL_COUNT; i++) {
        bool pressed = read_button_raw(i);
        cmc_app_state.button[i].raw                = pressed;
        cmc_app_state.button[i].raw_last_change_ms = now;
        cmc_app_state.button[i].is_pressed         = pressed;
        cmc_app_state.button[i].is_held            = false;
        cmc_app_state.button[i].click_count        = 0;
        cmc_app_state.button[i].double_click_count = 0;
        cmc_app_state.button[i].hold_count         = 0;

        btn_int[i].press_start_ms     = 0;
        btn_int[i].last_release_ms    = 0;
        btn_int[i].hold_fired         = false;
        btn_int[i].awaiting_2nd_click = false;
        btn_int[i].pending_click_ms   = 0;
    }
}

// Scan all configured buttons: debounce, then detect press/release/hold/click/double-click
void cmc_util_button_scan(void) {
    uint32_t now = HAL_GetTick();

    // only loop over configured buttons
    for (uint8_t i = 0; i < this_unit->in_digital_used; i++) {
        cmc_button_state_t* btn = &cmc_app_state.button[i];
        cmc_btn_internal_t* bi  = &btn_int[i];

        // --- Step 1: Read raw and track last change time ---
        bool current_raw = read_button_raw(i);
        if (current_raw != btn->raw) {
            btn->raw = current_raw;
            btn->raw_last_change_ms = now;
        }

        // --- Step 2: Debounce — only accept new state after it has been stable ---
        bool prev_pressed = btn->is_pressed;
        if (btn->raw != btn->is_pressed) {
            if ((now - btn->raw_last_change_ms) >= CMC_BTN_DEBOUNCE_MS) {
                btn->is_pressed = btn->raw;
            }
        }

        // --- Step 3: Detect transitions ---
        bool just_pressed  = (btn->is_pressed && !prev_pressed);
        bool just_released = (!btn->is_pressed && prev_pressed);

        // On press: record start time, reset hold flag
        if (just_pressed) {
            bi->press_start_ms = now;
            bi->hold_fired = false;
        }

        // On release: determine if it was a short click (not a hold)
        if (just_released) {
            bi->last_release_ms = now;
            btn->is_held = false;

            uint32_t press_duration = now - bi->press_start_ms;
            if (!bi->hold_fired && press_duration <= CMC_BTN_CLICK_MAX_MS) {
                // This was a short press — potential click or double-click
                if (bi->awaiting_2nd_click) {
                    // Second click arrived within the double-click window
                    btn->double_click_count++;
                    bi->awaiting_2nd_click = false;
                } else {
                    // First click — start the double-click window
                    bi->awaiting_2nd_click = true;
                    bi->pending_click_ms = now;
                }
            }
        }

        // --- Step 4: Hold detection while pressed ---
        if (btn->is_pressed && !bi->hold_fired) {
            if ((now - bi->press_start_ms) >= CMC_BTN_HOLD_THRESHOLD_MS) {
                btn->is_held = true;
                btn->hold_count++;
                bi->hold_fired = true;
                // Cancel any pending click — this press became a hold
                bi->awaiting_2nd_click = false;
            }
        }

        // --- Step 5: Expire double-click window — promote pending to single click ---
        if (bi->awaiting_2nd_click && !btn->is_pressed) {
            if ((now - bi->pending_click_ms) >= CMC_BTN_DBLCLICK_GAP_MS) {
                btn->click_count++;
                bi->awaiting_2nd_click = false;
            }
        }
    }
}
