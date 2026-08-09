/**
  *********************************************************************************************
  * @file      cmc_feature_oil_pressure.h
  * @brief     Oil pressure sensor feature — drives the oil pressure warning light
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_OIL_PRESSURE_H_
#define CMC_FEATURE_OIL_PRESSURE_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled;  // 1 = feature enabled, 0 = disabled
} cmc_feature_oil_pressure_t;

// Call from cmc_features_init to set up the feature state based on the configuration
void cmc_feature_oil_pressure_init(void);

// Call from the main processing loop in cmc_features_process to maintain oil pressure warning output state
void cmc_feature_oil_pressure_process(void);

#endif /* CMC_FEATURE_OIL_PRESSURE_H_ */
