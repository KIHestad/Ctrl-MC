/**
  *********************************************************************************************
  * @file      cmc_feature_ignition.h
  * @brief     Ignition feature control logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_IGNITION_H_
#define CMC_FEATURE_IGNITION_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled; // 0 = disabled (ignition always on, no sensor required), 1 = enabled (follows CMC_CONFIG_IN_DEVICE_IGNITION input pin)
} cmc_feature_ignition_t;

void cmc_feature_ignition_init(void);    // Call from cmc_features_init to set up the feature state based on the configuration
void cmc_feature_ignition_process(void); // Call from main loop in cmc_features_process to maintain ignition state

#endif /* CMC_FEATURE_IGNITION_H_ */
