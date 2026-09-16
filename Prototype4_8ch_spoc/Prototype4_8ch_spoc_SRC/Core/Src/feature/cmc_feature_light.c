/**
  *********************************************************************************************
  * @file      cmc_feature_light.c
  * @brief     Lighting feature — controls park, low beam and high beam outputs
  * @details   Resolves the physical light outputs on this unit from the shared light state in
  *            cmc_app_state, applying the following priority rules on every process() call:
  *              1. Ignition off  → all lights off, no exceptions.
  *              2. Starter active or within 2 s after release → low beam and high beam off;
  *                 park/tail remain on so the motorcycle is still visible.
  *              3. High beam active and high_beam_keeps_low_beam == 0 → low beam off.
  *              4. Otherwise follow cmc_app_state.feature.light exactly.
  *            The park output and tail output both follow (park_on || low_beam_on) so that
  *            the tail lamp is always lit whenever any headlight mode is active, and the park
  *            lamp comes on in both park-only mode and full-lights mode.
  *            Instrument indicator outputs (INSTR_LO, INSTR_HI) are driven in parallel when
  *            those output devices are configured on this unit.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "feature/cmc_features_manager.h"
#include "feature/cmc_features_output.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"
#include "feature/cmc_feature_test_channels.h"
#include "feature/cmc_feature_light.h"

#define CMC_FEATURE_LIGHT_STARTER_RESTORE_MS  2000U  // Delay (ms) after starter release before beams are restored 

// Whether this unit has any light output configured (init sets this)
static bool     this_unit_feature_out_enabled    = false;

// Output switch IDs for each light type; 0xFF = not present on this unit
static uint8_t  switch_park_id              = 0xFF;
static uint8_t  switch_low_beam_id          = 0xFF;
static uint8_t  switch_high_beam_id         = 0xFF;
static uint8_t  switch_tail_id              = 0xFF;
static uint8_t  switch_instr_lo_id          = 0xFF;
static uint8_t  switch_instr_hi_id          = 0xFF;

// Resolved output state from the last process() call — used to detect changes
static bool     prev_park_out               = false;
static bool     prev_low_beam_out           = false;
static bool     prev_high_beam_out          = false;
static bool     prev_tail_out               = false;
static bool     prev_instr_lo_out           = false;
static bool     prev_instr_hi_out           = false;

// Starter suppression tracking
static bool     starter_was_active          = false;
static bool     starter_beam_suppressed     = false;
static uint32_t starter_released_ms         = 0U;

/* ---- Helpers ----------------------------------------------------------------------------- */

static void set_output(uint8_t id, bool on, bool *prev)
{
    if (id != 0xFF && on != *prev) {
        cmc_features_out_set_switch(id, on);
        *prev = on;
    }
}

static void cmc_feature_light_broadcast(void)
{
    struct cmc_can_message_feature_light_t msg;
    msg.park_on      = cmc_app_state.feature.light.park_on      ? 1U : 0U;
    msg.low_beam_on  = cmc_app_state.feature.light.low_beam_on  ? 1U : 0U;
    msg.high_beam_on = cmc_app_state.feature.light.high_beam_on ? 1U : 0U;
    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_LIGHT_LENGTH];
    if (cmc_can_message_feature_light_pack(payload, &msg, sizeof(payload)) < 0) { return; }
    cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_LIGHT_FRAME_ID, payload, CMC_CAN_MESSAGE_FEATURE_LIGHT_LENGTH);
}

/* ---- Init -------------------------------------------------------------------------------- */

void cmc_feature_light_init(void)
{
    // Discover which output devices are wired on this unit
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_LIGHT_PARK)) {
        switch_park_id     = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_LIGHT_PARK);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM)) {
        switch_low_beam_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM)) {
        switch_high_beam_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_LIGHT_TAIL)) {
        switch_tail_id     = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_LIGHT_TAIL);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_LO)) {
        switch_instr_lo_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_LO);
    }
    if (cmc_features_out_is_device_enabled(CMC_CONFIG_OUT_DEVICE_INSTR_HI)) {
        switch_instr_hi_id = cmc_features_out_get_device_id(CMC_CONFIG_OUT_DEVICE_INSTR_HI);
    }

    // Explicit single source of truth: enabled, not test-suppressed, AND this unit has an output
    bool has_any_output = (switch_park_id     != 0xFF) ||
                          (switch_low_beam_id  != 0xFF) ||
                          (switch_high_beam_id != 0xFF) ||
                          (switch_tail_id      != 0xFF) ||
                          (switch_instr_lo_id  != 0xFF) ||
                          (switch_instr_hi_id  != 0xFF);
    this_unit_feature_out_enabled = (cmc_config.feature_light.enabled == 1) &&
        !cmc_feature_test_channels_suppresses(cmc_config.feature_light.enabled_on_test) &&
        has_any_output;

    if (this_unit_feature_out_enabled) {
        // Ensure all lights start in the off state
        if (switch_park_id      != 0xFF) { cmc_features_out_set_switch(switch_park_id,      false); }
        if (switch_low_beam_id  != 0xFF) { cmc_features_out_set_switch(switch_low_beam_id,  false); }
        if (switch_high_beam_id != 0xFF) { cmc_features_out_set_switch(switch_high_beam_id, false); }
        if (switch_tail_id      != 0xFF) { cmc_features_out_set_switch(switch_tail_id,      false); }
        if (switch_instr_lo_id  != 0xFF) { cmc_features_out_set_switch(switch_instr_lo_id,  false); }
        if (switch_instr_hi_id  != 0xFF) { cmc_features_out_set_switch(switch_instr_hi_id,  false); }
    }
}

/* ---- Process ----------------------------------------------------------------------------- */

void cmc_feature_light_process(void)
{
    // Broadcast user-intent light state change to other units, regardless of local outputs
    if (cmc_app_state.feature.light.pending_broadcast) {
        cmc_app_state.feature.light.pending_broadcast = false;
        cmc_feature_light_broadcast();
    }

    if (!this_unit_feature_out_enabled) {
        return;
    }

    // ---- Starter suppression tracking ----
    bool starter_active = cmc_app_state.feature.starter.on;

    if (!starter_active && starter_was_active) {
        // Starter just released — begin 2 s restore delay
        starter_released_ms     = HAL_GetTick();
        starter_beam_suppressed = true;
    }
    if (starter_beam_suppressed && !starter_active) {
        if ((HAL_GetTick() - starter_released_ms) >= CMC_FEATURE_LIGHT_STARTER_RESTORE_MS) {
            starter_beam_suppressed = false;
        }
    }
    starter_was_active = starter_active;

    // ---- Resolve output state ----
    bool resolved_park      = false;
    bool resolved_low_beam  = false;
    bool resolved_high_beam = false;

    if (cmc_app_state.vehicle.ignition_on) {

        bool user_park  = cmc_app_state.feature.light.park_on;
        bool user_low   = cmc_app_state.feature.light.low_beam_on;
        bool user_high  = cmc_app_state.feature.light.high_beam_on;

        // Starter active or within the post-starter delay window: suppress beams only
        bool beams_allowed = !starter_active && !starter_beam_suppressed;

        // Park output: on when user has park or main lights on (and park is physically installed)
        resolved_park = cmc_config.feature_light.park_light_enabled &&
                        (user_park || user_low);

        // Low beam: respect high-beam exclusivity config
        if (beams_allowed && user_low) {
            bool hi_active = user_high && beams_allowed;
            resolved_low_beam = user_low &&
                                (!hi_active || (cmc_config.feature_light.high_beam_keeps_low_beam == 1));
        }

        // High beam
        if (beams_allowed) {
            resolved_high_beam = user_high;
        }
    }

    // Tail follows park/main state (independent of beam suppression)
    bool resolved_tail      = cmc_app_state.vehicle.ignition_on &&
                              (cmc_app_state.feature.light.park_on || cmc_app_state.feature.light.low_beam_on);

    // ---- Drive outputs only on change ----
    set_output(switch_park_id,      resolved_park,      &prev_park_out);
    set_output(switch_low_beam_id,  resolved_low_beam,  &prev_low_beam_out);
    set_output(switch_high_beam_id, resolved_high_beam, &prev_high_beam_out);
    set_output(switch_tail_id,      resolved_tail,      &prev_tail_out);
    set_output(switch_instr_lo_id,  resolved_low_beam,  &prev_instr_lo_out);
    set_output(switch_instr_hi_id,  resolved_high_beam, &prev_instr_hi_out);
}
