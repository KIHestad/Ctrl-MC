/**
  *********************************************************************************************
  * @file      cmc_app_state_updater.c
  * @brief     Owns all writes to cmc_app_state — both from local inputs (TX path) and from
  *            incoming CAN messages (RX path). No other module should write to cmc_app_state.
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
            cmc_app_state.veichle_state.ignition_on = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_STARTER_FRAME_ID: {
            struct cmc_can_message_feature_starter_t msg;
            if (cmc_can_message_feature_starter_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.button.starter_button_pressed = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID: {
            struct cmc_can_message_feature_horn_t msg;
            if (cmc_can_message_feature_horn_unpack(&msg, data, length) < 0) { break; }
            cmc_app_state.button.horn_button_pressed = (bool)msg.value_on_off;
            break;
        }

        case CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID: {
            struct cmc_can_message_feature_direction_indicator_t msg;
            if (cmc_can_message_feature_direction_indicator_unpack(&msg, data, length) < 0) { break; }
            bool on = (msg.value_on_off == 1U);
            bool left  = on && (msg.value_left_right_both == 0U || msg.value_left_right_both == 2U);
            bool right = on && (msg.value_left_right_both == 1U || msg.value_left_right_both == 2U);
            bool hazard = left && right;
            cmc_app_state.direction_indicator.active       = on;
            cmc_app_state.direction_indicator.left_active  = left;
            cmc_app_state.direction_indicator.right_active = right;
            cmc_app_state.direction_indicator.hazard_active = hazard;
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
            if (cmc_app_state.veichle_state.ignition_on != in_state->pressed) {
                cmc_app_state.veichle_state.ignition_on = in_state->pressed;
                // Broadcast change to all units over CAN
                struct cmc_can_message_feature_ignition_t ign_msg;
                ign_msg.value_on_off = in_state->pressed ? 1u : 0u;
                uint8_t ign_payload[CMC_CAN_MESSAGE_FEATURE_IGNITION_LENGTH];
                if (cmc_can_message_feature_ignition_pack(ign_payload, &ign_msg, sizeof(ign_payload)) < 0) { break; }
                cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_IGNITION_FRAME_ID, ign_payload, CMC_CAN_MESSAGE_FEATURE_IGNITION_LENGTH);
            }
            break;

        case CMC_CONFIG_IN_DEVICE_STARTER:
            if (cmc_app_state.button.starter_button_pressed != in_state->pressed) {
                cmc_app_state.button.starter_button_pressed = in_state->pressed;
                // Broadcast change to all units over CAN
                struct cmc_can_message_feature_starter_t str_msg;
                str_msg.value_on_off = in_state->pressed ? 1u : 0u;
                uint8_t str_payload[CMC_CAN_MESSAGE_FEATURE_STARTER_LENGTH];
                if (cmc_can_message_feature_starter_pack(str_payload, &str_msg, sizeof(str_payload)) < 0) { break; }
                cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_STARTER_FRAME_ID, str_payload, CMC_CAN_MESSAGE_FEATURE_STARTER_LENGTH);
            }
            break;

        case CMC_CONFIG_IN_DEVICE_HORN:
            if (cmc_app_state.button.horn_button_pressed != in_state->pressed) {
                cmc_app_state.button.horn_button_pressed = in_state->pressed;
                // Broadcast change to all units over CAN
                struct cmc_can_message_feature_horn_t msg;
                msg.value_on_off = in_state->pressed ? 1u : 0u;
                uint8_t payload[CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH];
                if (cmc_can_message_feature_horn_pack(payload, &msg, sizeof(payload)) < 0) { break; }
                cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID, payload, CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH);
            }
            break;

        case CMC_CONFIG_IN_DEVICE_TURN_LEFT:
            if (cmc_app_state.button.turn_signal.left_on != in_state->pressed) {
                cmc_app_state.button.turn_signal.left_on = in_state->pressed;
                // Re-derive direction indicator state from both button states
                bool left  = cmc_app_state.button.turn_signal.left_on;
                bool right = cmc_app_state.button.turn_signal.right_on;
                bool hazard = left && right;
                cmc_app_state.direction_indicator.active        = left || right;
                cmc_app_state.direction_indicator.left_active   = left;
                cmc_app_state.direction_indicator.right_active  = right;
                cmc_app_state.direction_indicator.hazard_active = hazard;
                // Broadcast over CAN
                struct cmc_can_message_feature_direction_indicator_t di_msg;
                di_msg.value_on_off          = (left || right) ? 1U : 0U;
                di_msg.value_left_right_both = hazard ? 2U : (right ? 1U : 0U);
                di_msg.value_front_rear_both = 2U; // both front and rear
                di_msg.value_dashboard_only  = 0U; // normal operation
                uint8_t di_payload[CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH];
                if (cmc_can_message_feature_direction_indicator_pack(di_payload, &di_msg, sizeof(di_payload)) < 0) { break; }
                cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID, di_payload, CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH);
            }
            break;

        case CMC_CONFIG_IN_DEVICE_TURN_RIGHT:
            if (cmc_app_state.button.turn_signal.right_on != in_state->pressed) {
                cmc_app_state.button.turn_signal.right_on = in_state->pressed;
                // Re-derive direction indicator state from both button states
                bool left  = cmc_app_state.button.turn_signal.left_on;
                bool right = cmc_app_state.button.turn_signal.right_on;
                bool hazard = left && right;
                cmc_app_state.direction_indicator.active        = left || right;
                cmc_app_state.direction_indicator.left_active   = left;
                cmc_app_state.direction_indicator.right_active  = right;
                cmc_app_state.direction_indicator.hazard_active = hazard;
                // Broadcast over CAN
                struct cmc_can_message_feature_direction_indicator_t di_msg;
                di_msg.value_on_off          = (left || right) ? 1U : 0U;
                di_msg.value_left_right_both = hazard ? 2U : (right ? 1U : 0U);
                di_msg.value_front_rear_both = 2U; // both front and rear
                di_msg.value_dashboard_only  = 0U; // normal operation
                uint8_t di_payload[CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH];
                if (cmc_can_message_feature_direction_indicator_pack(di_payload, &di_msg, sizeof(di_payload)) < 0) { break; }
                cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_FRAME_ID, di_payload, CMC_CAN_MESSAGE_FEATURE_DIRECTION_INDICATOR_LENGTH);
            }
            break;

        case CMC_CONFIG_IN_DEVICE_BRAKE_LEVER:
            // TODO
            break;

        default:
            break;
    }
}
