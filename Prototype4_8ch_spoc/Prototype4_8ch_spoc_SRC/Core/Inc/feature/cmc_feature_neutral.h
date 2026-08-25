/**
  *********************************************************************************************
  * @file      cmc_feature_neutral.h
  * @brief     Neutral sensor feature — drives the neutral indicator light from the gear sensor
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_NEUTRAL_H_
#define CMC_FEATURE_NEUTRAL_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled;        // 1 = feature enabled, 0 = disabled
    uint8_t enabled_on_test; // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
} cmc_feature_neutral_t;

// Call from cmc_features_init to set up the feature state based on the configuration
void cmc_feature_neutral_init(void);

// Call from the main processing loop in cmc_features_process to maintain neutral indicator output state
void cmc_feature_neutral_process(void);

#endif /* CMC_FEATURE_NEUTRAL_H_ */
