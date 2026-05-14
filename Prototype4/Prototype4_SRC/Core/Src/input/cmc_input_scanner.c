/**
  *********************************************************************************************
  * @file      cmc_input_scanner.c
  * @brief     Button reading, debouncing and event detection (click, hold)
  *            Reads GPIO pins via cmc_config_hw_digital_in_mapping
  *            All buttons are active-low (pulled up, pressed reads GPIO_PIN_RESET)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type.h"
#include "config/cmc_config_type_unit.h"
#include "app/cmc_app_state.h"
#include "input/cmc_input.h"

static cmc_input_state_t cmc_input_state[CMC_CONFIG_HW_IN_DIGITAL_COUNT];

// Read one button GPIO, returns true if button is physically pressed (active-low)
static bool read_button_raw(uint8_t index) {
    return HAL_GPIO_ReadPin(
        cmc_config_hw_digital_in_mapping[index].port,
        cmc_config_hw_digital_in_mapping[index].pin
    ) == GPIO_PIN_RESET;
}

// Initialize: sample current GPIO state as both raw and debounced, clear all counters
void cmc_input_scanner_init(void) {
    uint32_t now = HAL_GetTick();
    for (uint8_t i = 0; i < CMC_CONFIG_HW_IN_DIGITAL_COUNT; i++) {
        bool pressed = read_button_raw(i);
        cmc_input_state[i].pressed_raw      = pressed;
        cmc_input_state[i].pressed_physical = pressed;
        cmc_input_state[i].pressed          = pressed;
        cmc_input_state[i].toggle_hold      = false;
        cmc_input_state[i].toggle_hold_sec  = 0;
        cmc_input_state[i].pressed_raw_ms   = now;
        cmc_input_state[i].toggle_hold_start_ms = now;
    }
}

// Scan all configured buttons: debounce, then detect press/release/hold/click
void cmc_input_scanner_execute(void) {
    // Get timestamp
    uint32_t now = HAL_GetTick();
    // only loop over configured buttons
    for (uint8_t i = 0; i < cmc_config_this_unit->in_used; i++) {
        
        // First get the button configuration for this input pin from the unit configuration
        uint8_t type_id = cmc_config_this_unit->in[i].type_id;
        if (type_id == CMC_INTYPE_IGNORE) {
            continue; // skip processing for this button if it's configured to be ignored
        }

        // Reference to the button state struct for easier access
        cmc_input_state_t* in_state  = &cmc_input_state[i];

        // Read inputs depending on digital or analog type
        if (type_id != CMC_INTYPE_ANALOG) {
            
            // Digital button, read the raw GPIO state, compare to last raw state for debounce logic
            bool current_pressed_raw = read_button_raw(i);
            if (current_pressed_raw != in_state->pressed_raw) {
                in_state->pressed_raw = current_pressed_raw;
                in_state->pressed_raw_ms = now;
            }

            // Debounce — only accept new state after it has been stable
            bool prev_physical_pressed = in_state->pressed_physical;
            if (in_state->pressed_raw != in_state->pressed_physical) {
                if ((now - in_state->pressed_raw_ms) >= CMC_UTIL_IN_DEBOUNCE_MS) {
                    in_state->pressed_physical = in_state->pressed_raw;
                }
            }

            bool just_pressed = (in_state->pressed_physical && !prev_physical_pressed);
            bool just_released = (!in_state->pressed_physical && prev_physical_pressed);

            // Direct output follows debounced physical state. Toggle output flips once per press edge.
            if (type_id == CMC_INTYPE_DIGITAL_DIRECT) {
                in_state->pressed = in_state->pressed_physical;
            }
            //  type_id == CMC_INTYPE_DIGITAL_TOGGLE
            else { 
                if (just_pressed) {
                    in_state->pressed = !in_state->pressed;
                    // Hold tracking is based on physical debounced press, not logical toggle state.
                    in_state->toggle_hold_start_ms = now;
                    in_state->toggle_hold = false;
                    in_state->toggle_hold_sec = 0;
                }
                // Hold detection based on physical debounced state, only for toggle type
                if (in_state->pressed_physical) {
                    uint32_t hold_elapsed_ms = now - in_state->toggle_hold_start_ms;
                    if (hold_elapsed_ms >= CMC_UTIL_IN_HOLD_THRESHOLD_MS) {
                        in_state->toggle_hold = true;
                        in_state->toggle_hold_sec = (uint8_t)(hold_elapsed_ms / 1000U);
                    }
                } 
                else if (just_released) {
                    in_state->toggle_hold = false;
                    in_state->toggle_hold_sec = 0;
                }
            }
            
        }
        else {

            // Analog input processing can be implemented here if needed, for now we will skip it as the current focus is on button inputs
            // TODO: Not implemented yet

        }

        // After button state is recorded, check if cmc_app_state needs updating depending on the button type
        cmc_input_app_state_update(&cmc_config_this_unit->in[i], in_state);

    }
}
