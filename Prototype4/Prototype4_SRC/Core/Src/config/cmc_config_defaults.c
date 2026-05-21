/**
  *********************************************************************************************
  * @file      cmc_config_defaults.c
  * @brief     Configuration defaults  for demo only, to be removed when a real config editor is implemented
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_defaults.h"
#include "config/cmc_config_type.h"
#include "config/cmc_config_type_unit.h"

// Set to true to load the default config on boot if missing in flash
// Set false to ignore this, config must then be loaded over CAN
const bool cmc_config_default_for_demo_use = true;

// Default configuration values for the system
const cmc_config_t cmc_config_default_for_demo = {
    .signature       = CMC_CONFIG_SIGNATURE, // Default config signature, must match CMC_CONFIG_SIGNATURE to be considered valid
    .version         = CMC_CONFIG_VERSION,   // Default config version, can be used for migration logic if the config structure changes in future firmware versions
    .units_required  = 2, // The expected number of IO units the system needs to operate, this is also the number of units that should be present in the configuration

    // Unit number 1: Front I/O Unit
    .io_unit[0] = {
        .unit_id         = 1,
        .unit_name_id    = CMC_CONFIG_UNIT_NAME_FRONT, 
        .in_used         = 8, // Number of input connectors used on this unit
        .out_used        = 6, // Number of output channels used on this unit
        
        // Input buttons and sensors
        .in[0] = {       // Input button 1
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_TURN_LEFT,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[1] = {       // Input button 2
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_TURN_RIGHT,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[2] = {       // Input button 3
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_LIGHT_HIGH_BEAM,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[3] = {       // Input button 4
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_HORN,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT
        },
        .in[4] = {       // Input button 5
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_CLUTCH_LEVER,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT
        },
        .in[5] = {       // Input button 6
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_BRAKE_LEVER,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT
        },
        .in[6] = {       // Input button 7
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_STARTER,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT
        },
        .in[7] = {       // Input button 8
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_LIGHTS_MAIN,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[8] = {       // Input button 9
            .enabled     = 0,
            .device_id   = CMC_CONFIG_IN_DEVICE_MENU_LEFT,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[9] = {       // Input button 10
            .enabled     = 0,
            .device_id   = CMC_CONFIG_IN_DEVICE_MENU_RIGHT,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },

        // Output Channel Mapping
        .out[0] = {      // Output channel 1
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_HORN
        },
        .out[1] = {      // Output channel 2
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT
        },
        .out[2] = {      // Output channel 3
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_PARK
        },
        .out[3] = {      // Output channel 4
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT
        },
        .out[4] = {      // Output channel 5
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM
        },
        .out[5] = {      // Output channel 6
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM
        },
    },

    // Unit number 2: Rear I/O Unit
    .io_unit[1] = {
        .unit_id         = 2,
        .unit_name_id    = CMC_CONFIG_UNIT_NAME_REAR,
        .in_used         = 2, // Number of input connectors used on this unit
        .out_used        = 6, // Number of output channels used on this unit

        // Input buttons and sensors
        .in[0] = {       // Input button 1
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_NEUTRAL_SENSOR,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[1] = {       // Input button 2
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_BRAKE_PEDAL,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT
        },

        // Output Channel Mapping
        .out[0] = {      // Output channel 1
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_BRAKE
        },
        .out[1] = {       // Output channel 2
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_LIGHT_TAIL
        },
        .out[2] = {       // Output channel 3
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR
        },
        .out[3] = {       // Output channel 4
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR
        },
        .out[4] = {       // Output channel 5
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_STARTER
        },
        .out[5] = {       // Output channel 6
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_INSTR_NEUTRAL
        }
    },
    .feature_ignition = {
        .enabled = 0, // 0 = disabled: ignition always on (no sensor required, safe default for bench testing)
    },
    .feature_starter = {
        .enabled = 0, // 0 = disabled: starter output never activates; set to 1 to enable input-driven starter control
    },
    .feature_horn = {
        .enabled = 1, // Set to 1 to enable the horn feature, set to 0 to disable it and the system will ignore any horn-related logic
        .auto_shut_off_sec = 3, // Automatically turn off the horn after this many seconds if the button is held continuously, set to 0 to disable auto shut-off
    },
    .feature_direction_indicator = {
        .enabled = 1,              // Set to 1 to enable the direction indicator feature
        .blink_interval_x10ms = 50, // Blink on/off interval (100 = 1 second, 50 = half a second - number in 1/100 of a second)
        .auto_shut_off_sec = 30,    // Duration in seconds after which the direction indicator should automatically shut off, not applicable if hazard mode
    }
        
};
