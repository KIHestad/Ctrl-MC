/**
  *********************************************************************************************
  * @file      cmc_feature_light.h
  * @brief     Lighting feature — controls park, low beam and high beam outputs
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_LIGHT_H_
#define CMC_FEATURE_LIGHT_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>

// Main-light input modes
#define CMC_FEATURE_LIGHT_MAIN_MODE_DEDICATED            0  // Separate LIGHT_PARK + LIGHTS_MAIN buttons
#define CMC_FEATURE_LIGHT_MAIN_MODE_MULTIFUNCTION_TOGGLE 1 // Single LIGHT_MULTIFUNCTION button (cycles: off → park → main)

// Hi/lo beam input modes
#define CMC_FEATURE_LIGHT_HIBEAM_MODE_DEDICATED 0  // Separate LIGHT_LOW_BEAM + LIGHT_HIGH_BEAM buttons
#define CMC_FEATURE_LIGHT_HIBEAM_MODE_TOGGLE    1  // Single LIGHT_HI_LOW_BEAM_TOGGLE (toggle: off=low, on=high)

typedef struct {
    uint8_t enabled;                    // 1 = feature enabled, 0 = disabled
    uint8_t enabled_on_test;            // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
    uint8_t park_light_enabled;         // 1 = motorcycle has a park/side light output; 0 = no park light
    uint8_t high_beam_keeps_low_beam;   // 1 = low beam stays on when high beam is active; 0 = low beam off when high beam is on
    uint8_t main_light_input_mode;      // CMC_FEATURE_LIGHT_MAIN_MODE_* — how the park/main input is wired
    uint8_t hi_lo_beam_input_mode;      // CMC_FEATURE_LIGHT_HIBEAM_MODE_* — how the hi/lo beam input is wired
} cmc_feature_light_t;

// Call from cmc_features_init to set up the feature state based on the configuration
void cmc_feature_light_init(void);

// Call from the main processing loop in cmc_features_process to maintain light output state
void cmc_feature_light_process(void);

#endif /* CMC_FEATURE_LIGHT_H_ */
