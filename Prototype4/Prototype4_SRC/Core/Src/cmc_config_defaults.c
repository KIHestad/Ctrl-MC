#include "cmc_config_defaults.h"
#include "cmc_config_type.h"

/* ====================================================================
 * FIRMWARE DEFAULT CONFIGURATION
 * ==================================================================== */
const cmc_global_config_t firmware_default_config = {
    .signature          = CMC_CONFIG_SIGNATURE,
    .global_config_hash = 0x00000000, // No hash yet, it's a raw default
    .active_unit_count  = 2,          // The total number of I/O units to be used for the system (e.g., front unit, rear unit, etc.)
    .active_rule_count  = 1,          // The total number of rules to be used for the system
    
    // --- UNIT 1: FRONT I/O UNIT ---
    .io_unit[0] = {
        .unit_id                 = 1,
        .name                    = "Front Unit",
        .output_channels_used    = 6,
        .input_digital_pins_used = 10,
        .input_analog_pins_used  = 0,
        
        // Output Channel Mapping
        .output_equipment[0] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_HORN
        },
        .output_equipment[1] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_TURN_LEFT
        },
        .output_equipment[2] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_LIGHT_PARK
        },
        .output_equipment[3] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_TURN_RIGHT
        },
        .output_equipment[4] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_LIGHT_LOW_BEAM
        },
        .output_equipment[5] = {
            .equipment_id = 1,
            .equipment_id = CMC_EQP_LIGHT_HIGH_BEAM
        },
        
        // Input Pin Mapping
        .input_digital[0] = {
            .enabled     = 1,
            .input_id    = CMC_INP_TURN_LEFT,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[1] = {
            .enabled     = 1,
            .input_id    = CMC_INP_TURN_RIGHT,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[2] = {
            .enabled     = 1,
            .input_id    = CMC_INP_LIGHT_HIGH_BEAM,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[3] = {
            .enabled     = 1,
            .input_id    = CMC_INP_HORN,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[4] = {
            .enabled     = 1,
            .input_id    = CMC_INP_CLUTCH_LEVER,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[5] = {
            .enabled     = 1,
            .input_id    = CMC_INP_BRAKE_LEVER,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[6] = {
            .enabled     = 1,
            .input_id    = CMC_INP_STARTER,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[7] = {
            .enabled     = 1,
            .input_id    = CMC_INP_LIGHTS_MAIN,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[8] = {
            .enabled     = 1,
            .input_id    = CMC_INP_MENU_LEFT,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[9] = {
            .enabled     = 1,
            .input_id    = CMC_INP_MENU_RIGHT,
            .button_type = CMC_BTN_TOGGLE
        },

    },
    // --- UNIT 2: REAR I/O UNIT ---
    .io_unit[1] = {
        .unit_id                 = 2,
        .name                    = "Rear Unit",
        .output_channels_used    = 6,
        .input_digital_pins_used = 4,
        .input_analog_pins_used  = 0,
        
        // Output Channel Mapping
        .output_equipment[0] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_LIGHT_BRAKE
        },
        .output_equipment[1] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_LIGHT_TAIL
        },
        .output_equipment[2] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_TURN_LEFT
        },
        .output_equipment[3] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_TURN_RIGHT
        },
        .output_equipment[4] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_STARTER
        },
        .output_equipment[5] = {
            .enabled      = 1,
            .equipment_id = CMC_EQP_INSTR_NEUTRAL
        },
        
        // Input Pin Mapping
        .input_digital[0] = {
            .enabled     = 1,
            .input_id    = CMC_INP_NEUTRAL_SENSOR,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[1] = {
            .enabled     = 1,
            .input_id    = CMC_INP_BRAKE_PEDAL,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[2] = {
            .enabled     = 1,
            .input_id    = CMC_INP_BRAKE_PEDAL,
            .button_type = CMC_BTN_CLASSIC
        },
        .input_digital[2] = {
            .enabled     = 1,
            .input_id    = CMC_INP_OIL_SENSOR,
            .button_type = CMC_BTN_TOGGLE
        },
        .input_digital[3] = {
            .enabled     = 1,
            .input_id    = CMC_INP_WATER_TEMP_SENSOR,
            .button_type = CMC_BTN_TOGGLE
        }
    },
    // --- THE RULES ENGINE (LOGIC) ---
    .rule[0] = {
        // "If Ignition is ON AND Horn Button is PRESSED..."
        .cond1_input_id    = CMC_INP_IGNITION,
        .rule_operator_id  = CMC_OP_AND,
        .cond2_input_id    = CMC_INP_HORN,
        
        // "...Turn ON the Horn on Unit 1, Channel 1"
        .rule_action_id    = CMC_ACT_TURN_ON,
        .target_unit_id    = 1,
        .target_output_id  = 1,
        
        .blink_interval_ms = 0,
        .blink_duration_ms = 0
    }
};

/* ====================================================================
 * PUBLIC INITIALIZATION FUNCTION
 * ==================================================================== */
void CMC_ConfigDefaults_Load(void) {
    // Copy firmware default from ROM into active RAM
    for (uint32_t i = 0; i < sizeof(cmc_global_config_t); i++) {
        ((uint8_t*)&cmc_global_config)[i] = ((uint8_t*)&firmware_default_config)[i];
    }
}