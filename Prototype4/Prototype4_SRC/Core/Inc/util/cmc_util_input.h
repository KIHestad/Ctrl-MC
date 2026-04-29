/**
  *********************************************************************************************
  * @file      cmc_util_input.h
  * @brief     Button reading, debouncing and event detection (click, hold)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_INPUT_H_
#define CMC_UTIL_INPUT_H_

#include <stdint.h>

// Timing constants (milliseconds)
#define CMC_UTIL_IN_DEBOUNCE_MS        50   // Debounce window, filters mechanical bounce on motorcycle buttons
#define CMC_UTIL_IN_HOLD_THRESHOLD_MS  600  // Press duration to trigger a hold event

// Initialize button states, read initial GPIO levels into raw/debounced fields
void cmc_util_input_init(void);

// Scan all buttons, debounce and detect events, call once per main loop iteration
void cmc_util_input_scan(void);

#endif /* CMC_UTIL_INPUT_H_ */
