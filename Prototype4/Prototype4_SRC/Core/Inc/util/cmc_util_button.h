/**
  *********************************************************************************************
  * @file      cmc_util_button.h
  * @brief     Button reading, debouncing and event detection (click, double-click, hold)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_BUTTON_H_
#define CMC_UTIL_BUTTON_H_

#include <stdint.h>

// Timing constants (milliseconds)
#define CMC_BTN_DEBOUNCE_MS        50   // Debounce window, filters mechanical bounce on motorcycle buttons
#define CMC_BTN_HOLD_THRESHOLD_MS  600  // Press duration to trigger a hold event
#define CMC_BTN_DBLCLICK_GAP_MS    300  // Max gap between two clicks to count as double-click
#define CMC_BTN_CLICK_MAX_MS       400  // Max press duration that still counts as a click (vs hold)

// Number of buttons handled
// TODO: This could be made dynamic, read from config, based on what unit this is
#define CMC_BTN_COUNT              10

// Initialize button states, read initial GPIO levels into raw/debounced fields
void cmc_util_button_init(void);

// Scan all buttons, debounce and detect events, call once per main loop iteration
void cmc_util_button_scan(void);

#endif /* CMC_UTIL_BUTTON_H_ */
