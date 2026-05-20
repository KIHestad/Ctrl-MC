/**
  *********************************************************************************************
  * @file      cmc_feature_direction_indicator.h
  * @brief     Direction indicator (turn signal) feature control logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_DIRECTION_INDICATOR_H_
#define CMC_FEATURE_DIRECTION_INDICATOR_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

// Configuration for the direction indicator feature
typedef struct {
    uint8_t enabled;              // 1 = enabled, 0 = disabled
    uint8_t blink_interval_x10ms; // Blink on/off interval in 1/100 second (e.g. 100 = 1 second, 50 = 0.5 second)
} cmc_feature_direction_indicator_t;

// Call this in the main initialization to set up the feature state based on the configuration
void cmc_feature_direction_indicator_init(void);

// Call this in the main processing loop to handle direction indicator blink logic
void cmc_feature_direction_indicator_process(void);

#endif /* CMC_FEATURE_DIRECTION_INDICATOR_H_ */
