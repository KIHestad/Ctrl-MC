/**
  *********************************************************************************************
  * @file      cmc_feature_direction_indicator.c
  * @brief     Direction indicator (turn signal) feature — manages left, right and hazard blinking
  * @details   Controls all turn-signal output channels that are configured on this unit:
  *            - CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL / TURN_LEFT_FRONT / TURN_LEFT_REAR
  *            - CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL / TURN_RIGHT_FRONT / TURN_RIGHT_REAR
  *            - CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON / INSTR_TURN_LEFT / INSTR_TURN_RIGHT
  *            The active direction is read from cmc_app_state.direction_indicator which is
  *            maintained by cmc_app_state_updater. Blink phase is derived from HAL_GetTick().
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "feature/cmc_feature_direction_indicator.h"

// Maximum number of physical channels that can be mapped per side or group on one unit
#define CMC_FEATURE_DI_MAX_SIDE_CHANNELS 3U  // TURN_x_ALL, TURN_x_FRONT, TURN_x_REAR

// ---- Local state, not exposed outside this module ----------------------------------------

static bool this_unit_feature_active = false; // True if the feature is enabled and at least one relevant output exists on this unit

// Stored output-channel indices for each device type (0xFF = not present on this unit)
static uint8_t left_ids[CMC_FEATURE_DI_MAX_SIDE_CHANNELS];   // TURN_LEFT_ALL, TURN_LEFT_FRONT, TURN_LEFT_REAR
static uint8_t left_count;
static uint8_t right_ids[CMC_FEATURE_DI_MAX_SIDE_CHANNELS];  // TURN_RIGHT_ALL, TURN_RIGHT_FRONT, TURN_RIGHT_REAR
static uint8_t right_count;
static uint8_t instr_common_id; // INSTR_TURN_COMMON indicator light
static uint8_t instr_left_id;   // INSTR_TURN_LEFT indicator light
static uint8_t instr_right_id;  // INSTR_TURN_RIGHT indicator light

// Previous blink state so we only drive outputs when the phase changes
static bool prev_blink_phase = false;
// Previous direction indicator active state for detecting transitions (on→off / off→on)
static bool prev_active = false;

// ---- Private helpers ---------------------------------------------------------------------

// Turn all managed turn-signal outputs off
static void turn_all_off(void)
{
    for (uint8_t i = 0U; i < left_count; i++) {
        cmc_features_out_set_switch(left_ids[i], false);
    }
    for (uint8_t i = 0U; i < right_count; i++) {
        cmc_features_out_set_switch(right_ids[i], false);
    }
    if (instr_common_id != 0xFFU) { cmc_features_out_set_switch(instr_common_id, false); }
    if (instr_left_id   != 0xFFU) { cmc_features_out_set_switch(instr_left_id,   false); }
    if (instr_right_id  != 0xFFU) { cmc_features_out_set_switch(instr_right_id,  false); }
}

// Apply the current blink phase to all active-side outputs
static void apply_blink(bool left_active, bool right_active, bool phase_on)
{
    // Physical turn lights
    if (left_active) {
        for (uint8_t i = 0U; i < left_count; i++) {
            cmc_features_out_set_switch(left_ids[i], phase_on);
        }
    }
    if (right_active) {
        for (uint8_t i = 0U; i < right_count; i++) {
            cmc_features_out_set_switch(right_ids[i], phase_on);
        }
    }

    // Instrument indicator lights
    bool any_active = left_active || right_active;
    if (instr_common_id != 0xFFU) {
        cmc_features_out_set_switch(instr_common_id, any_active ? phase_on : false);
    }
    if (instr_left_id != 0xFFU) {
        cmc_features_out_set_switch(instr_left_id, left_active ? phase_on : false);
    }
    if (instr_right_id != 0xFFU) {
        cmc_features_out_set_switch(instr_right_id, right_active ? phase_on : false);
    }
}

// ---- Public API --------------------------------------------------------------------------

void cmc_feature_direction_indicator_init(void)
{
    left_count  = 0U;
    right_count = 0U;
    instr_common_id = 0xFFU;
    instr_left_id   = 0xFFU;
    instr_right_id  = 0xFFU;

    // Skip if feature is disabled in config
    if (cmc_config.feature_direction_indicator.enabled == 0U) {
        this_unit_feature_active = false;
        return;
    }

    // Collect left-side physical output channels
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL)) {
        left_ids[left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT)) {
        left_ids[left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR)) {
        left_ids[left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR);
    }

    // Collect right-side physical output channels
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL)) {
        right_ids[right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT)) {
        right_ids[right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR)) {
        right_ids[right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR);
    }

    // Collect instrument indicator channels
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON)) {
        instr_common_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_LEFT)) {
        instr_left_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_LEFT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_RIGHT)) {
        instr_right_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_RIGHT);
    }

    // Feature is only active on this unit if at least one relevant output channel was found
    this_unit_feature_active = (left_count > 0U || right_count > 0U
                                || instr_common_id != 0xFFU
                                || instr_left_id   != 0xFFU
                                || instr_right_id  != 0xFFU);

    if (this_unit_feature_active) {
        turn_all_off();
    }
}

void cmc_feature_direction_indicator_process(void)
{
    if (!this_unit_feature_active) {
        return;
    }

    bool active       = cmc_app_state.direction_indicator.active;
    bool left_active  = cmc_app_state.direction_indicator.left_active;
    bool right_active = cmc_app_state.direction_indicator.right_active;

    // Transition to off: ensure all outputs are turned off immediately
    if (!active) {
        if (prev_active) {
            turn_all_off();
            prev_active     = false;
            prev_blink_phase = false;
        }
        return;
    }

    // Compute current blink phase: alternates every blink_interval_ms milliseconds
    uint32_t interval = (uint32_t)cmc_config.feature_direction_indicator.blink_interval_x10ms * 10U;
    if (interval == 0U) { interval = 500U; } // Guard against zero interval
    bool phase_on = ((HAL_GetTick() / interval) & 1U) == 0U;

    // Apply outputs only when the phase changes or on a fresh activation
    if (phase_on != prev_blink_phase || !prev_active) {
        apply_blink(left_active, right_active, phase_on);
        prev_blink_phase = phase_on;
    }

    prev_active = true;
}
