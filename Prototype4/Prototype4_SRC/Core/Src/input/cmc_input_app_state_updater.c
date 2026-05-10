/**
  *********************************************************************************************
  * @file      cmc_input_app_state_updater.c
  * @brief     Updates the cmc_app_state based on the input states read and processed by 
               cmc_input_scanner, called from the main app logic after scanning inputs
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type.h"
#include "config/cmc_config_type_unit.h"
#include "app/cmc_app_state.h"
#include "input/cmc_input.h"
#include "can/cmc_can_manager.h"
#include "can/cmc_can_message.h"

// This function should be called after cmc_input_scanner executes to update the cmc_app_state based on the latest input states.
void cmc_input_app_state_update(const cmc_config_in_t* config_in, cmc_input_state_t* in_state) {

        // After button state is recorded, check if cmc_app_state needs updating depending on the button type
        switch (config_in->device_id) {

            case CMC_IN_HORN:
                if (cmc_app_state.input.horn_button_pressed != in_state->pressed) {
                    // Horn button state has changed, update app state accordingly
                    cmc_app_state.input.horn_button_pressed = in_state->pressed; 
                    // Send over canbus
                    struct cmc_can_message_feature_horn_t horn_msg;
                    horn_msg.value_on_off = cmc_app_state.input.horn_button_pressed;  // 1=on, 0=off
                    uint8_t payload[CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH];
                    int pack_result = cmc_can_message_feature_horn_pack(payload, &horn_msg, sizeof(payload));
                    if (pack_result < 0) { break; } // Packing failed, skip sending
                    cmc_can_status_t status = cmc_can_manager_send(CMC_CAN_MESSAGE_FEATURE_HORN_FRAME_ID, payload, CMC_CAN_MESSAGE_FEATURE_HORN_LENGTH);
                    if (status != CMC_CAN_OK) { break; } // Sending failed, skip further processing
                }
                break;
            
                case CMC_IN_BRAKE_LEVER:
                // todo
                break;
        }

}
