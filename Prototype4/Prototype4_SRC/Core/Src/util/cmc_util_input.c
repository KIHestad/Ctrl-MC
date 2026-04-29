/**
  *********************************************************************************************
  * @file      cmc_util_input.c
  * @brief     Button reading, debouncing and event detection (click, hold)
  *            Reads GPIO pins via cmc_config_hw_digital_in_mapping
  *            All buttons are active-low (pulled up, pressed reads GPIO_PIN_RESET)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_input.h"
#include "app/cmc_app_state.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal.h"

// State per button needed for event detection timing (not exposed outside this module)
typedef struct {
    bool     pressed_raw;          // Last raw GPIO read (physical level, active-low mapped to pressed=true)
    uint32_t pressed_raw_ms;       // Tick at latest raw state change (debounce timer base)
    bool     pressed_physical;     // Debounced physical pressed state
    bool     pressed;              // Logical pressed state (direct follows physical, toggle flips on press edge)
    bool     toggle_hold;          // True while toggle input is physically held past hold threshold
    uint8_t  toggle_hold_sec;      // Whole seconds toggle input has been held after threshold
    uint32_t toggle_hold_start_ms; // Tick when toggle input debounced press began
} cmc_util_in_state_t;

static cmc_util_in_state_t cmc_util_in_state[CMC_CONFIG_HW_IN_DIGITAL_COUNT];

// Read one button GPIO, returns true if button is physically pressed (active-low)
static bool read_button_raw(uint8_t index) {
    return HAL_GPIO_ReadPin(
        cmc_config_hw_digital_in_mapping[index].port,
        cmc_config_hw_digital_in_mapping[index].pin
    ) == GPIO_PIN_RESET;
}

// Initialize: sample current GPIO state as both raw and debounced, clear all counters
void cmc_util_input_init(void) {
    uint32_t now = HAL_GetTick();
    for (uint8_t i = 0; i < CMC_CONFIG_HW_IN_DIGITAL_COUNT; i++) {
        bool pressed = read_button_raw(i);
        cmc_util_in_state[i].pressed_raw      = pressed;
        cmc_util_in_state[i].pressed_physical = pressed;
        cmc_util_in_state[i].pressed          = pressed;
        cmc_util_in_state[i].toggle_hold      = false;
        cmc_util_in_state[i].toggle_hold_sec  = 0;
        cmc_util_in_state[i].pressed_raw_ms   = now;
        cmc_util_in_state[i].toggle_hold_start_ms = now;
    }
}

// Scan all configured buttons: debounce, then detect press/release/hold/click
void cmc_util_input_scan(void) {
    // Get timestamp
    uint32_t now = HAL_GetTick();
    // only loop over configured buttons
    for (uint8_t i = 0; i < cmc_config_this_unit->in_used; i++) {
        
        // First get the button configuration for this input pin from the unit configuration
        uint8_t type_id = cmc_config_this_unit->in[i].type_id;
        if (type_id == CMC_IN_TYPE_IGNORE) {
            continue; // skip processing for this button if it's configured to be ignored
        }

        // Reference to the button state struct for easier access
        cmc_util_in_state_t* in  = &cmc_util_in_state[i];

        // Read inputs depending on digital or analog type
        if (type_id != CMC_IN_TYPE_ANALOG) {
            
            // Digital button, read the raw GPIO state, compare to last raw state for debounce logic
            bool current_pressed_raw = read_button_raw(i);
            if (current_pressed_raw != in->pressed_raw) {
                in->pressed_raw = current_pressed_raw;
                in->pressed_raw_ms = now;
            }

            // Debounce — only accept new state after it has been stable
            bool prev_physical_pressed = in->pressed_physical;
            if (in->pressed_raw != in->pressed_physical) {
                if ((now - in->pressed_raw_ms) >= CMC_UTIL_IN_DEBOUNCE_MS) {
                    in->pressed_physical = in->pressed_raw;
                }
            }

            bool just_pressed = (in->pressed_physical && !prev_physical_pressed);
            bool just_released = (!in->pressed_physical && prev_physical_pressed);

            // Direct output follows debounced physical state. Toggle output flips once per press edge.
            if (type_id == CMC_IN_TYPE_DIGITAL_DIRECT) {
                in->pressed = in->pressed_physical;
            }
            //  type_id == CMC_IN_TYPE_DIGITAL_TOGGLE
            else { 
                if (just_pressed) {
                    in->pressed = !in->pressed;
                    // Hold tracking is based on physical debounced press, not logical toggle state.
                    in->toggle_hold_start_ms = now;
                    in->toggle_hold = false;
                    in->toggle_hold_sec = 0;
                }
                // Hold detection based on physical debounced state, only for toggle type
                if (in->pressed_physical) {
                    uint32_t hold_elapsed_ms = now - in->toggle_hold_start_ms;
                    if (hold_elapsed_ms >= CMC_UTIL_IN_HOLD_THRESHOLD_MS) {
                        in->toggle_hold = true;
                        in->toggle_hold_sec = (uint8_t)(hold_elapsed_ms / 1000U);
                    }
                } 
                else if (just_released) {
                    in->toggle_hold = false;
                    in->toggle_hold_sec = 0;
                }
            }
            
        }
        else {

            // Analog input processing can be implemented here if needed, for now we will skip it as the current focus is on button inputs
            // TODO: Not implemented yet

        }

        // After button state is recorded, check if cmc_app_state needs updating depending on the button type
        if (cmc_config_this_unit->in[i].device_id == CMC_IN_HORN) {
            cmc_app_state.input.horn_button_pressed = in->pressed;
        }

    }
}
