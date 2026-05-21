/**
  *********************************************************************************************
  * @file      cmc_input.h
  * @brief     Button reading, debouncing, event detection (click, hold) and app state updating based on inputs
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_INPUT_SCANNER_H_
#define CMC_INPUT_SCANNER_H_

#include <stdint.h>
#include "config/cmc_config_type.h"

// Timing constants (milliseconds)
#define CMC_UTIL_IN_DEBOUNCE_MS        50   // Debounce window, filters mechanical bounce on motorcycle buttons
#define CMC_UTIL_IN_HOLD_THRESHOLD_MS  600  // Press duration to trigger a hold event

// State per button needed for event detection timing (not exposed outside this module)
typedef struct {
    bool     pressed_raw;          // Last raw GPIO read (physical level, active-low mapped to pressed=true)
    uint32_t pressed_raw_ms;       // Tick at latest raw state change (debounce timer base)
    bool     pressed_physical;     // Debounced physical pressed state
    bool     pressed;              // Logical pressed state (direct follows physical, toggle flips on press edge)
    bool     toggle_hold;          // True while toggle input is physically held past hold threshold
    uint8_t  toggle_hold_sec;      // Whole seconds toggle input has been held after threshold
    uint32_t toggle_hold_start_ms; // Tick when toggle input debounced press began
} cmc_input_button_state_t;

// Initialize button states, read initial GPIO levels into raw/debounced fields
void cmc_input_scanner_init(void);

// Scan all buttons, debounce and detect events, call once per main loop iteration
void cmc_input_scanner_execute(void);

// Reset the logical toggle state for any DIGITAL_TOGGLE input mapped to the given device ID.
// Call when a feature externally overrides an indicator's active state (e.g. cancel-other, auto
// shut-off) so the scanner's toggle stays in sync and the next physical press acts as "turn on".
void cmc_input_scanner_reset_toggle_by_device(cmc_config_in_device_t device_id);

#endif /* CMC_INPUT_SCANNER_H_ */
