/**
  *********************************************************************************************
  * @file      cmc_feature_horn.h
  * @brief     Horn feature control logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_TYPE_FEATURE_HORN_H_
#define CMC_CONFIG_TYPE_FEATURE_HORN_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled;            // Set 1 if to be used, set 0 if not to be used and the system will ignore it
    uint8_t auto_shut_off_sec;  // Max duration in seconds the horn should stay on when activated, set to 0 for no auto shut-off    
} cmc_feature_horn_t;

extern void cmc_feature_horn_init(void); // Call this in the main initialization to set up the feature state based on the configuration
extern void cmc_feature_horn_process(void); // Call this in the main processing loop to handle horn logic

#endif /* CMC_CONFIG_TYPE_FEATURE_HORN_H_ */