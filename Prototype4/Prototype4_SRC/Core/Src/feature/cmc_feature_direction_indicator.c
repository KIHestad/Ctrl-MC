/**
  *********************************************************************************************
  * @file      cmc_feature_direction_indicator.c
  * @brief     Direction indicator (turn signal) feature — manages left, right and hazard blinking
  * @details   Manages the direction indicator state based on the turn signal button inputs and configuration
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_type_unit.h"
#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "input/cmc_input.h"
#include <stdint.h>
#include "feature/cmc_feature_direction_indicator.h"

// Locals
// Static variables to track the horn state and configuration on this unit
static bool this_unit_feature_active    = false;   // True if the feature is enabled and at least one relevant output exists on this unit
static uint8_t switches_left_count      = 0;             // The number of output channels for the left direction indicator on this unit
static uint8_t switches_right_count     = 0;            // The number of output channels for the right direction indicator on this unit
static uint8_t switch_left_id[5]        = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};    // The output indexes for the left direction indicator on this unit
static uint8_t switch_right_id[5]       = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};    // The output indexes for the right direction indicator on this unit
// Active state tracking for the direction indicator
static bool this_unit_left_active       = false;   // True if the left direction indicator is currently active (output on)
static bool this_unit_right_active      = false;   // True if the right direction indicator is currently active (output on)
static uint32_t interval_speed_ms       = 500;     // Blinking interval in milliseconds, not configurable for now
static uint32_t on_since_ms             = 0;       // Tick at which the direction indicator was last turned on, used for auto shut-off timeout
// State machine edge tracking — prev_app tracks the last seen app_state values for self-detecting change detection
static bool     prev_app_left         = false;  // last seen app_state left_on
static bool     prev_app_right        = false;  // last seen app_state right_on
static uint32_t left_activated_ms     = 0U;     // tick when left was last activated (hazard window)
static uint32_t right_activated_ms    = 0U;     // tick when right was last activated
#define CMC_FEATURE_DI_HAZARD_WINDOW_MS 500U    // both buttons within this window → hazard

// Sync the cancelled side: write false back to app_state, update prev_app, and reset the scanner
// toggle so the very next physical press acts as "turn on" (no dead press required).
static void cancel_left(void) {
    cmc_app_state.feature.directional_indicator.left_on = false;
    prev_app_left = false;
    cmc_input_scanner_reset_toggle_by_device(CMC_CONFIG_IN_DEVICE_TURN_LEFT);
}
static void cancel_right(void) {
    cmc_app_state.feature.directional_indicator.right_on = false;
    prev_app_right = false;
    cmc_input_scanner_reset_toggle_by_device(CMC_CONFIG_IN_DEVICE_TURN_RIGHT);
}

static void set_switch_left(bool on, bool update_active_state) {
    for (uint8_t i = 0; i < switches_left_count; i++) {
        cmc_features_out_set_switch(switch_left_id[i], on);
    }
    if (update_active_state) { this_unit_left_active = on; }
}

static void set_switch_right(bool on, bool update_active_state) {
    for (uint8_t i = 0; i < switches_right_count; i++) {
        cmc_features_out_set_switch(switch_right_id[i], on);
    }
    if (update_active_state) { this_unit_right_active = on; }
}

static void cmc_feature_direction_indicator_broadcast()
{
    // Broadcast over CAN so other units update their cmc_app_state
    struct cmc_can_message_feature_direction_indicator_t di_msg;
    bool hazard = this_unit_left_active && this_unit_right_active;
    di_msg.value_on_off          = (this_unit_left_active || this_unit_right_active) ? 1U : 0U;
    di_msg.value_left_right_both = hazard ? 2U : (this_unit_right_active ? 1U : 0U);
    di_msg.value_front_rear_both = 2U; // both front and rear
    di_msg.value_dashboard_only  = 0U; // normal operation
    uint8_t di_payload[CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH];
    if (cmc_can_message_feature_direction_indicator_pack(di_payload, &di_msg, sizeof(di_payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID, di_payload, CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH);
}

void cmc_feature_direction_indicator_init(void)
{
    // if not this feature is active, do nothing
    if (cmc_config.feature_direction_indicator.enabled != 1) {
       return;
    }
    
    // Check if any outputs are active, could be multiple - first left (+ common)
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL)) {
        switch_left_id[switches_left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT)) {
        switch_left_id[switches_left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR)) {
        switch_left_id[switches_left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_LEFT)) {
        switch_left_id[switches_left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_LEFT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON)) {
        switch_left_id[switches_left_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON);
    }
    // Check if any outputs are active, could be multiple - now right (+ common)
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL)) {
        switch_right_id[switches_right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT)) {
        switch_right_id[switches_right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR)) {
        switch_right_id[switches_right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_RIGHT)) {
        switch_right_id[switches_right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_RIGHT);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON)) {
        switch_right_id[switches_right_count++] = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON);
    }
    // If at least one output is enabled, the feature is active
    this_unit_feature_active = (switches_left_count > 0) || (switches_right_count > 0);
    // Continue if still active    
    if (this_unit_feature_active) {
        // Ensure the direction indicators start in the off state on initialization
        set_switch_left(false, true);
        set_switch_right(false, true);
        // Get blinking speed from config, use default if out of range
        if (cmc_config.feature_direction_indicator.blink_interval_x10ms >= 10 && 
            cmc_config.feature_direction_indicator.blink_interval_x10ms <= 200) {
            interval_speed_ms = (uint32_t)cmc_config.feature_direction_indicator.blink_interval_x10ms * 10U;
        }
    }
    // Seed prev_app from current app_state so the first process() call does not fire spuriously
    prev_app_left  = cmc_app_state.feature.directional_indicator.left_on;
    prev_app_right = cmc_app_state.feature.directional_indicator.right_on;
}

void cmc_feature_direction_indicator_process(void)
{
    // ---- State machine: self-detecting change in app_state (local scanner, CAN RX, or any future writer) ----
    bool cur_left  = cmc_app_state.feature.directional_indicator.left_on;
    bool cur_right = cmc_app_state.feature.directional_indicator.right_on;

    if (cur_left != prev_app_left || cur_right != prev_app_right) {

        bool just_left_on   =  cur_left  && !prev_app_left;
        bool just_right_on  =  cur_right && !prev_app_right;
        bool just_left_off  = !cur_left  &&  prev_app_left;
        bool just_right_off = !cur_right &&  prev_app_right;

        prev_app_left  = cur_left;
        prev_app_right = cur_right;

        bool new_left  = this_unit_left_active;   // default: keep current
        bool new_right = this_unit_right_active;

        bool in_hazard = this_unit_left_active && this_unit_right_active;

        if (just_left_on && just_right_on) {
            // Both toggled on in the same tick → hazard
            new_left = true;  new_right = true;
        } else if (in_hazard && (just_left_off || just_right_off)) {
            // Either side released while in hazard → cancel all
            new_left = false; new_right = false;
        } else if (just_right_on && this_unit_left_active && !this_unit_right_active) {
            // Right pressed while left is active: hazard if within window, else cancel-other
            if ((HAL_GetTick() - left_activated_ms) <= CMC_FEATURE_DI_HAZARD_WINDOW_MS) {
                new_left = true;  new_right = true;
            } else {
                new_left = false; new_right = true;
            }
        } else if (just_left_on && this_unit_right_active && !this_unit_left_active) {
            // Left pressed while right is active: hazard if within window, else cancel-other
            if ((HAL_GetTick() - right_activated_ms) <= CMC_FEATURE_DI_HAZARD_WINDOW_MS) {
                new_left = true;  new_right = true;
            } else {
                new_left = true;  new_right = false;
            }
        } else if (just_left_on)  { new_left  = true;  }
        else if (just_left_off)   { new_left  = false; }
        else if (just_right_on)   { new_right = true;  }
        else if (just_right_off)  { new_right = false; }

        // Track activation timestamps for hazard window
        if (new_left  && !this_unit_left_active)  { left_activated_ms  = HAL_GetTick(); }
        if (new_right && !this_unit_right_active) { right_activated_ms = HAL_GetTick(); }

        // Apply resolved active state and turn off outputs if deactivated.
        // cancel_left/right also resets the scanner toggle so the next press immediately activates.
        if (!new_left  && this_unit_left_active)  { set_switch_left(false, true);  cancel_left(); }
        if (!new_right && this_unit_right_active) { set_switch_right(false, true); cancel_right(); }
        this_unit_left_active  = new_left;
        this_unit_right_active = new_right;
        if (!new_left && !new_right) { on_since_ms = 0U; }

        // Only TX over CAN if the change originated from the local input scanner
        if (cmc_app_state.feature.directional_indicator.pending_broadcast) {
            cmc_app_state.feature.directional_indicator.pending_broadcast = false;
            cmc_feature_direction_indicator_broadcast();
        }
    }

    // ---- Output: only runs on units that have physical turn signal outputs ----
    if (!this_unit_feature_active) { return; }
    if (!this_unit_left_active && !this_unit_right_active) { return; }

    // Auto shut-off (not applied during hazard)
    bool hazard = this_unit_left_active && this_unit_right_active;
    if ((cmc_config.feature_direction_indicator.auto_shut_off_sec > 0U) && !hazard) {
        if (on_since_ms == 0U) { on_since_ms = HAL_GetTick(); }
        if ((HAL_GetTick() - on_since_ms) >=
            ((uint32_t)cmc_config.feature_direction_indicator.auto_shut_off_sec * 1000U)) {
            set_switch_left(false, true);
            set_switch_right(false, true);
            cancel_left();
            cancel_right();
            on_since_ms = 0U;
            cmc_feature_direction_indicator_broadcast();
            return;
        }
    } else {
        on_since_ms = 0U;
    }

    // Blink: drive outputs on/off based on current phase (active state flags are not modified)
    bool phase_on = ((HAL_GetTick() / interval_speed_ms) & 1U) == 0U;
    if (this_unit_left_active)  { set_switch_left(phase_on,  false); }
    if (this_unit_right_active) { set_switch_right(phase_on, false); }
}
