/**
  *********************************************************************************************
  * @file      cmc_feature_test_channels.h
  * @brief     Test-only feature: maps each enabled input button directly to the same-indexed
  *            output channel on this unit, bypassing normal feature logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_TEST_CHANNELS_H_
#define CMC_FEATURE_TEST_CHANNELS_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t enabled; // Set to 1 to enable the test channel feature, set to 0 to disable it and the system will ignore any test channel-related logic
} cmc_feature_test_channels_t;

// Returns true if the test-channels feature is currently enabled in the configuration.
bool cmc_feature_test_channels_is_active(void);

// Returns true if test mode is active AND the given feature's enabled_on_test flag does not
// override it (enabled_on_test != 1). Every other feature calls this with its own
// enabled_on_test config value, alongside its normal .enabled check, so that enabling the test
// feature suppresses all other features without needing to reconfigure the rest of cmc_config.
bool cmc_feature_test_channels_suppresses(uint8_t enabled_on_test);

// Call from cmc_features_init
void cmc_feature_test_channels_init(void);

// Call from the main processing loop in cmc_features_process
void cmc_feature_test_channels_process(void);

#endif /* CMC_FEATURE_TEST_CHANNELS_H_ */
