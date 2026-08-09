/**
  *********************************************************************************************
  * @file      cmc_feature_channel_info.h
  * @brief     Per-channel power, supply voltage, and fault reporting over CAN
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURE_CHANNEL_INFO_H_
#define CMC_FEATURE_CHANNEL_INFO_H_

#include <stdint.h>

// Temperature unit display preference (display-only; CAN bus always carries Celsius)
#define CMC_TEMP_UNIT_CELSIUS     0
#define CMC_TEMP_UNIT_FAHRENHEIT  1

typedef struct {
    uint8_t  enabled;
    uint8_t  overview_enabled;        // 1 = also broadcast CHANNEL_OVERVIEW every 1 s (requires CAN FD)
    uint8_t  overview_enabled_01_03;  // 1 = broadcast CHANNEL_OVERVIEW_01_03 every 1 s (classic CAN, ch1-3)
    uint8_t  overview_enabled_04_06;  // 1 = broadcast CHANNEL_OVERVIEW_04_06 every 1 s (classic CAN, ch4-6)
    uint8_t  overview_enabled_07_09;  // 1 = broadcast CHANNEL_OVERVIEW_07_09 every 1 s (classic CAN, ch7-9)
    uint8_t  overview_enabled_10_12;  // 1 = broadcast CHANNEL_OVERVIEW_10_12 every 1 s (classic CAN, ch10-12)
    uint8_t  temp_unit;        // CMC_TEMP_UNIT_CELSIUS or CMC_TEMP_UNIT_FAHRENHEIT
    uint8_t  compensation_enabled; // 1 = apply PROFET current-sense compensation tables; 0 = report raw sensor values (for inspecting new switches)
    uint16_t open_load_ma;     // current below this when switch is ON triggers open-load warning
} cmc_feature_channel_info_t;

// Call from cmc_features_init
void cmc_feature_channel_info_init(void);

// Call from the main processing loop in cmc_features_process
void cmc_feature_channel_info_process(void);

#endif /* CMC_FEATURE_CHANNEL_INFO_H_ */
