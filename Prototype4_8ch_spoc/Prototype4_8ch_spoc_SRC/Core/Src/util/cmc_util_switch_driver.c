/**
  *********************************************************************************************
  * @file      cmc_util_switch_driver.c
  * @brief     Hardware abstraction for Infineon PROFET and SPOC high-side switch channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_switch_driver.h"
#include "util/cmc_util_switch_profet_driver.h"
#include "util/cmc_util_switch_spoc_driver.h"
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type.h"

// Dispatches each call to the vendor driver selected by switch_type; see
// cmc_util_switch_profet_driver.c / cmc_util_switch_spoc_driver.c for the implementations.
static cmc_switch_status_t s_status[CMC_CONFIG_HW_OUT_COUNT];

void cmc_util_switch_init(void) {
    cmc_util_switch_profet_init();
    cmc_util_switch_spoc_init();
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        s_status[ch] = CMC_SWITCH_POWER_GOOD;
    }
}

void cmc_util_switch_set(uint8_t ch, bool on) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
        cmc_util_switch_profet_set(ch, on);
    } else if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_SPOC) {
        cmc_util_switch_spoc_set(ch, on);
    }
}

int8_t cmc_util_switch_set_pwm(uint8_t ch, uint8_t duty_pct) {
    (void)ch; (void)duty_pct;
    return (int8_t)CMC_SWITCH_NOT_SUPPORTED;
}

bool cmc_util_switch_is_on(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return false; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
        return cmc_util_switch_profet_is_on(ch);
    } else if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_SPOC) {
        return cmc_util_switch_spoc_is_on(ch);
    }
    return false;
}

void cmc_util_switch_sample_all(void) {
    cmc_util_switch_profet_sample_all(s_status);
    cmc_util_switch_spoc_sample_all(s_status);
}

int32_t cmc_util_switch_read_current_ma(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return 0; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
        return cmc_util_switch_profet_read_current_ma(ch);
    } else if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_SPOC) {
        return cmc_util_switch_spoc_read_current_ma(ch);
    }
    return (int32_t)CMC_SWITCH_NOT_SUPPORTED;
}

cmc_switch_status_t cmc_util_switch_get_status(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return CMC_SWITCH_FAULT_OVERCURRENT; }
    return s_status[ch];
}
