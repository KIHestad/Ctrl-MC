/**
  *********************************************************************************************
  * @file      cmc_feature_starter.h
  * @brief     Starter motor feature control logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_STARTER_H_
#define CMC_FEATURE_STARTER_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled; // 0 = disabled (starter output never activates), 1 = enabled (follows CMC_CONFIG_IN_DEVICE_STARTER input pin)
    uint8_t enabled_on_test; // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
} cmc_feature_starter_t;

void cmc_feature_starter_init(void);    // Call from cmc_features_init to set up the feature state based on the configuration
void cmc_feature_starter_process(void); // Call from main loop in cmc_features_process to control starter output

#endif /* CMC_FEATURE_STARTER_H_ */
