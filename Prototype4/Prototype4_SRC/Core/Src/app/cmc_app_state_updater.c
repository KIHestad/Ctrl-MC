/**
  *********************************************************************************************
  * @file      cmc_app_state_updater.c
 * @brief     Write gateway for raw input state in cmc_app_state. Handles two paths:
 *              1. CAN RX — incoming CAN frames update local cmc_app_state (no re-broadcast)
 *              2. Raw input — button/sensor state from cmc_input_scanner is written to
 *                             cmc_app_state; CAN broadcast is delegated to each feature module.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "app/cmc_app_state_updater.h"
#include "app/cmc_app_state.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"

/* ---- RX path: CAN → cmc_app_state -------------------------------------------------------- */

// Called from ISR context on every received CAN frame. Keep processing short.
// Updates cmc_app_state from incoming messages; does NOT re-broadcast (no feedback loop).
static void on_can_receive(uint32_t frame_id, const uint8_t *data, uint8_t length)
{
    switch (frame_id) {

        case CMC_CAN_MESSAGE_FEATURE_IGNITION_FRAME_ID: {
            struct cmc_can_message_feature_ignition_t msg;
            if (cmc_can_message_feature_ignition_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.vehicle.ignition_on = (bool)msg.ignition_on;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_STARTER_FRAME_ID: {
            struct cmc_can_message_feature_starter_t msg;
            if (cmc_can_message_feature_starter_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.starter.on = (bool)msg.starter_on;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID: {
            struct cmc_can_message_feature_horn_t msg;
            if (cmc_can_message_feature_horn_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.horn.on = (bool)msg.horn_on;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID: {
            struct cmc_can_message_feature_direction_indicator_t msg;
            if (cmc_can_message_feature_direction_indicator_unpack(&msg, data, length) < 0) { break; }
            // Derive direction indicator state from message fields
            bool on        = (msg.turn_signal_on          == 1); /* 1=on    */
            bool dir_left  = (msg.turn_signal_direction == 0 || msg.turn_signal_direction == 2); /* 0=left, 2=both */
            bool dir_right = (msg.turn_signal_direction == 1 || msg.turn_signal_direction == 2); /* 1=right, 2=both */
            // Assign to app state
            cmc_app_state.feature.directional_indicator.left_on  = on && dir_left;
            cmc_app_state.feature.directional_indicator.right_on = on && dir_right;
            cmc_app_state.feature.directional_indicator.hazard_on = on && (dir_left && dir_right);
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_LIGHT_FRAME_ID: {
            struct cmc_can_message_feature_light_t msg;
            if (cmc_can_message_feature_light_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.light.park_on      = (bool)msg.park_on;
            cmc_app_state.feature.light.low_beam_on  = (bool)msg.low_beam_on;
            cmc_app_state.feature.light.high_beam_on = (bool)msg.high_beam_on;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_BRAKE_LIGHT_FRAME_ID: {
            struct cmc_can_message_feature_brake_light_t msg;
            if (cmc_can_message_feature_brake_light_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.brake_light.on = (bool)msg.brake_light_on;
            break;
        }

        default:
            break;
    }
}

void cmc_app_state_updater_init(void)
{
    cmc_can_manager_on_receive(on_can_receive);
}

/* ---- TX path: local input → cmc_app_state → CAN ----------------------------------------- */

// Called from cmc_input_scanner_execute once per button per loop iteration.
void cmc_app_state_update(const cmc_config_in_t *config_in, cmc_input_button_state_t *in_state)
{
    switch (config_in->device_id) {

        case CMC_CONFIG_IN_DEVICE_IGNITION:
            if (cmc_app_state.vehicle.ignition_on != in_state->pressed) {
                cmc_app_state.vehicle.ignition_on = in_state->pressed;
                cmc_app_state.vehicle.ignition_on_pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_STARTER:
            if (cmc_app_state.feature.starter.on != in_state->pressed) {
                cmc_app_state.feature.starter.on = in_state->pressed;
                cmc_app_state.feature.starter.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_HORN:
            if (cmc_app_state.feature.horn.on != in_state->pressed) {
                cmc_app_state.feature.horn.on = in_state->pressed;
                cmc_app_state.feature.horn.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_TURN_LEFT: {
            if (cmc_app_state.feature.directional_indicator.left_on != in_state->pressed) {
                cmc_app_state.feature.directional_indicator.left_on = in_state->pressed;
                cmc_app_state.feature.directional_indicator.pending_broadcast = true;
            }
            break;
        }
        case CMC_CONFIG_IN_DEVICE_TURN_RIGHT: {
            if (cmc_app_state.feature.directional_indicator.right_on != in_state->pressed) {
                cmc_app_state.feature.directional_indicator.right_on = in_state->pressed;
                cmc_app_state.feature.directional_indicator.pending_broadcast = true;
            }
            break;
        }

        case CMC_CONFIG_IN_DEVICE_BRAKE_LEVER:
            if (cmc_app_state.feature.brake_light.on != in_state->pressed_physical) {
                cmc_app_state.feature.brake_light.on = in_state->pressed_physical;
                cmc_app_state.feature.brake_light.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_BRAKE_PEDAL:
            if (cmc_app_state.feature.brake_light.on != in_state->pressed_physical) {
                cmc_app_state.feature.brake_light.on = in_state->pressed_physical;
                cmc_app_state.feature.brake_light.pending_broadcast = true;
            }
            break;

        // ---- Light inputs ----

        case CMC_CONFIG_IN_DEVICE_LIGHT_PARK:
            // Direct latching park switch: park_on follows button state
            if (cmc_app_state.feature.light.park_on != in_state->pressed) {
                cmc_app_state.feature.light.park_on = in_state->pressed;
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_LIGHTS_MAIN:
            // Direct latching main-lights switch: low_beam_on follows button state.
            // Reset high_beam_on when turning off so lights-on always defaults to low beam.
            if (cmc_app_state.feature.light.low_beam_on != in_state->pressed) {
                cmc_app_state.feature.light.low_beam_on = in_state->pressed;
                if (!in_state->pressed) { cmc_app_state.feature.light.high_beam_on = false; }
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_LIGHT_MULTIFUNCTION: {
            // Momentary button cycles on each rising edge: off → park → main (park+low) → off.
            // Use pressed_physical so every physical press advances the cycle regardless of
            // whether the input is configured as DIGITAL_DIRECT or DIGITAL_TOGGLE — a
            // DIGITAL_TOGGLE usage would only raise `pressed` on odd-numbered presses, causing
            // every second press to be skipped.
            static bool     mf_prev  = false;
            static uint8_t  mf_cycle = 0U;
            bool pressed_now = in_state->pressed_physical;
            if (pressed_now && !mf_prev) {  // Rising edge on physical level
                mf_cycle = (mf_cycle >= 2U) ? 0U : (mf_cycle + 1U);
                cmc_app_state.feature.light.park_on     = (mf_cycle >= 1U);
                cmc_app_state.feature.light.low_beam_on = (mf_cycle >= 2U);
                // Reset high beam when stepping back below main-lights level
                if (mf_cycle < 2U) { cmc_app_state.feature.light.high_beam_on = false; }
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            mf_prev = pressed_now;
            break;
        }

        case CMC_CONFIG_IN_DEVICE_LIGHT_LOW_BEAM:
            // Direct dedicated low-beam button.
            // Reset high_beam_on when turning off so lights-on always defaults to low beam.
            if (cmc_app_state.feature.light.low_beam_on != in_state->pressed) {
                cmc_app_state.feature.light.low_beam_on = in_state->pressed;
                if (!in_state->pressed) { cmc_app_state.feature.light.high_beam_on = false; }
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_LIGHT_HIGH_BEAM:
            // Toggle dedicated high-beam button: each press flips high_beam_on
            if (cmc_app_state.feature.light.high_beam_on != in_state->pressed) {
                cmc_app_state.feature.light.high_beam_on = in_state->pressed;
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            break;

        case CMC_CONFIG_IN_DEVICE_LIGHT_HI_LOW_BEAM_TOGGLE: {
            // Dual behaviour depending on main light state:
            //   Low beam on  → toggle mode:   own flip-flop (hl_state) advances on each rising
            //                                 edge and holds through button release.
            //   Lights off / park only → flasher mode: pressed_physical (momentary).
            //                                 hl_state is reset to false so that when low beam
            //                                 is next enabled the beam always starts at low.
            // NOTE: in_state->pressed (scanner flip-flop) cannot be reset externally, so we
            //       maintain hl_state instead of relying on it.
            static bool hl_prev  = false;
            static bool hl_state = false;
            bool pressed_now = in_state->pressed_physical;
            bool new_high_beam;
            if (cmc_app_state.feature.light.low_beam_on) {
                if (pressed_now && !hl_prev) { hl_state = !hl_state; }  // Rising edge → flip
                new_high_beam = hl_state;
            } else {
                hl_state      = false;   // Reset so next lights-on starts at low beam
                new_high_beam = pressed_now;
            }
            hl_prev = pressed_now;
            if (cmc_app_state.feature.light.high_beam_on != new_high_beam) {
                cmc_app_state.feature.light.high_beam_on = new_high_beam;
                cmc_app_state.feature.light.pending_broadcast = true;
            }
            break;
        }

        default:
            break;
    }
}


