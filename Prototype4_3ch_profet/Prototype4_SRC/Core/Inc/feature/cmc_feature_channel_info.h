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
    uint8_t  overview_enabled; // 1 = also broadcast CHANNEL_OVERVIEW every 1 s
    uint8_t  temp_unit;        // CMC_TEMP_UNIT_CELSIUS or CMC_TEMP_UNIT_FAHRENHEIT
    uint8_t  _pad;
    uint16_t open_load_ma;     // current below this when switch is ON triggers open-load warning
} cmc_feature_channel_info_t;

// Call from cmc_features_init
void cmc_feature_channel_info_init(void);

// Call from the main processing loop in cmc_features_process
void cmc_feature_channel_info_process(void);

#endif /* CMC_FEATURE_CHANNEL_INFO_H_ */
