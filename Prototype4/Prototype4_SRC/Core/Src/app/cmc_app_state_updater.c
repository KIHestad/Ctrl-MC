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
            cmc_app_state.vehicle.ignition_on = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_STARTER_FRAME_ID: {
            struct cmc_can_message_feature_starter_t msg;
            if (cmc_can_message_feature_starter_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.starter.on = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID: {
            struct cmc_can_message_feature_horn_t msg;
            if (cmc_can_message_feature_horn_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.feature.horn.on = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID: {
            struct cmc_can_message_feature_direction_indicator_t msg;
            if (cmc_can_message_feature_direction_indicator_unpack(&msg, data, length) < 0) { break; }
            // Derive direction indicator state from message fields
            bool on        = (msg.value_on_off          == 1); /* 1=on    */
            bool dir_left  = (msg.value_left_right_both == 0 || msg.value_left_right_both == 2); /* 0=left  */
            bool dir_right = (msg.value_left_right_both == 1 || msg.value_left_right_both == 2); /* 1=right */
            // Assign to app state
            cmc_app_state.feature.directional_indicator.left_on  = on && dir_left;
            cmc_app_state.feature.directional_indicator.right_on = on && dir_right;
            cmc_app_state.feature.directional_indicator.hazard_on = on && (dir_left && dir_right);
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
            // TODO
            break;

        default:
            break;
    }
}


