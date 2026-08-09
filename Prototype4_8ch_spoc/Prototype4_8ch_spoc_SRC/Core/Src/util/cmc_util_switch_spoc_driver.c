/**
  *********************************************************************************************
  * @file      cmc_util_switch_spoc_driver.c
  * @brief     Infineon SPOC high-side switch channel implementation (SPI daisy chain)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  *
  * Scaffolding only: the SPOC part number and SPI register/command protocol have not been
  * specified yet, so this module only tracks commanded on/off state and does not talk to
  * hardware. Fill in the SPI transactions once the target SPOC device is chosen.
  */

#include "util/cmc_util_switch_spoc_driver.h"
#include "config/cmc_config_hw_mapping.h"

static bool s_spoc_shadow_on[CMC_CONFIG_HW_OUT_COUNT];

void cmc_util_switch_spoc_init(void) {
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_SPOC) { continue; }
        // TODO: SPI peripheral setup / CS pin init once SPOC part is chosen
        s_spoc_shadow_on[ch] = false;
    }
}

void cmc_util_switch_spoc_set(uint8_t ch, bool on) {
    // TODO: send SPI command to drive the channel; shadow state only for now
    s_spoc_shadow_on[ch] = on;
}

bool cmc_util_switch_spoc_is_on(uint8_t ch) {
    return s_spoc_shadow_on[ch];
}

void cmc_util_switch_spoc_sample_all(cmc_switch_status_t *status) {
    (void)status;
    // TODO: read SPI diagnostic word and populate status[ch] per SPOC channel
}

int32_t cmc_util_switch_spoc_read_current_ma(uint8_t ch) {
    (void)ch;
    return (int32_t)CMC_SWITCH_NOT_SUPPORTED;
}
