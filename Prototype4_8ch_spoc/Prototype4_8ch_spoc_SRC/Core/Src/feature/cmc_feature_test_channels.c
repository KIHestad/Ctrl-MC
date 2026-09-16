/**
  *********************************************************************************************
  * @file      cmc_feature_test_channels.c
  * @brief     Test-only feature: maps each enabled input button directly to the same-indexed
  *            output channel on this unit, bypassing normal feature logic
  * @details   When enabled, input button N (0-based index into cmc_config_this_unit->in[])
  *            drives output channel N (same index into cmc_config_this_unit->out[]) directly,
  *            for enabled buttons and enabled channels only. The button's configured usage_id
  *            (digital_direct or digital_toggle) is honored via cmc_input_scanner_is_pressed(),
  *            which resolves the same logical pressed state used everywhere else in the system.
  *            This feature never sends any CAN messages of its own.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_type.h"
#include "input/cmc_input.h"
#include "feature/cmc_features_output.h"
#include "feature/cmc_feature_test_channels.h"

// Whether the test feature is enabled (cached from config in init to avoid repeated reads)
static bool feature_enabled           = false;

// Resolved output state from the last process() call — used to only drive a switch on change
static bool prev_out[CMC_CONFIG_HW_OUT_COUNT];

bool cmc_feature_test_channels_is_active(void) {
    return cmc_config.feature_test_channels.enabled == 1U;
}

bool cmc_feature_test_channels_suppresses(uint8_t enabled_on_test) {
    return cmc_feature_test_channels_is_active() && (enabled_on_test != 1U);
}

void cmc_feature_test_channels_init(void) {
    feature_enabled = cmc_feature_test_channels_is_active();
    // Reset to match the all-off state set by cmc_features_out_init_all(), so the first
    // genuinely-pressed button is still seen as a change and actually drives its output.
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        prev_out[ch] = false;
    }
}

void cmc_feature_test_channels_process(void) {
    if (!feature_enabled) {
        return;
    }

    for (uint8_t i = 0U; i < CMC_CONFIG_HW_OUT_COUNT; i++) {
        if (i >= cmc_config_this_unit->in_used || i >= cmc_config_this_unit->out_used) {
            continue;
        }
        if (cmc_config_this_unit->in[i].enabled != 1U || cmc_config_this_unit->out[i].enabled != 1U) {
            continue;
        }

        uint8_t usage_id = cmc_config_this_unit->in[i].usage_id;
        if (usage_id != CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT && usage_id != CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE) {
            continue; // ignore/analog buttons are not meaningful for this feature
        }

        bool pressed = cmc_input_scanner_is_pressed(i);
        if (pressed != prev_out[i]) {
            cmc_features_out_set_switch(i, pressed);
            prev_out[i] = pressed;
        }
    }
}
