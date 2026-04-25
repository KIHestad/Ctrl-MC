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
#include "config/cmc_config_type_def.h"

// Set to true to load the default config on boot if missing in flash
// Set false to ignore this, config must then be loaded over CAN
const bool cmc_config_default_for_demo_use = true;

// Default configuration values for the system
const cmc_config_t cmc_config_default_for_demo = {
    .signature       = CMC_CONFIG_SIGNATURE,
    .config_hash     = 0x00000000, // No hash yet, it's a raw default
    .units_required  = 2, // The minimum number of IO units the system needs to operate
    .features_used   = 1, // The number of features used in the system, should be less than or equal to CMC_CONFIG_MAX_SUPPORTED_FEATURES

    // Unit number 1: Front I/O Unit
    .io_unit[0] = {
        .unit_id                 = 1,
        .unit_name_id            = CMC_UNIT_FRONT, 
        .in_used                 = 8, // Number of input connectors used on this unit
        .out_used                = 6, // Number of output channels used on this unit
        
        // Input buttons and sensors
        .in[0] = {       // Input button 1
            .enabled     = 1,
            .device_id   = CMC_IN_TURN_LEFT,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[1] = {       // Input button 2
            .enabled     = 1,
            .device_id   = CMC_IN_TURN_RIGHT,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[2] = {       // Input button 3
            .enabled     = 1,
            .device_id   = CMC_IN_LIGHT_HIGH_BEAM,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[3] = {       // Input button 4
            .enabled     = 1,
            .device_id   = CMC_IN_HORN,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[4] = {       // Input button 5
            .enabled     = 1,
            .device_id   = CMC_IN_CLUTCH_LEVER,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[5] = {       // Input button 6
            .enabled     = 1,
            .device_id   = CMC_IN_BRAKE_LEVER,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[6] = {       // Input button 7
            .enabled     = 1,
            .device_id   = CMC_IN_STARTER,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[7] = {       // Input button 8
            .enabled     = 1,
            .device_id   = CMC_IN_LIGHTS_MAIN,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[8] = {       // Input button 9
            .enabled     = 0,
            .device_id   = CMC_IN_MENU_LEFT,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },
        .in[9] = {       // Input button 10
            .enabled     = 0,
            .device_id   = CMC_IN_MENU_RIGHT,
            .btn_type_id = CMC_IN_DEV_TYPE_DIGITAL_TOGGLE
        },

        // Output Channel Mapping
        .out[0] = {      // Output channel 1
            .enabled     = 1,
            .device_id   = CMC_OUT_HORN
        },
        .out[1] = {      // Output channel 2
            .enabled     = 1,
            .device_id   = CMC_OUT_TURN_LEFT_FRONT
        },
        .out[2] = {      // Output channel 3
            .enabled     = 1,
            .device_id   = CMC_OUT_LIGHT_PARK
        },
        .out[3] = {      // Output channel 4
            .enabled     = 1,
            .device_id   = CMC_OUT_TURN_RIGHT_FRONT
        },
        .out[4] = {      // Output channel 5
            .enabled     = 1,
            .device_id   = CMC_OUT_LIGHT_LOW_BEAM
        },
        .out[5] = {      // Output channel 6
            .enabled     = 1,
            .device_id   = CMC_OUT_LIGHT_HIGH_BEAM
        },
    },

    // Unit number 2: Rear I/O Unit
    .io_unit[1] = {
        .unit_id                 = 2,
        .unit_name_id            = CMC_UNIT_REAR,
        .in_used                 = 0, // Number of input connectors used on this unit
        .out_used                = 6, // Number of output channels used on this unit

        // Output Channel Mapping
        .out[0] = {       // Output channel 1
            .enabled      = 1,
            .device_id    = CMC_OUT_LIGHT_BRAKE
        },
        .out[1] = {       // Output channel 2
            .enabled      = 1,
            .device_id    = CMC_OUT_LIGHT_TAIL
        },
        .out[2] = {       // Output channel 3
            .enabled      = 1,
            .device_id    = CMC_OUT_TURN_LEFT_REAR
        },
        .out[3] = {       // Output channel 4
            .enabled      = 1,
            .device_id    = CMC_OUT_TURN_RIGHT_REAR
        },
        .out[4] = {       // Output channel 5
            .enabled      = 1,
            .device_id    = CMC_OUT_STARTER
        },
        .out[5] = {       // Output channel 6
            .enabled      = 1,
            .device_id    = CMC_OUT_INSTR_NEUTRAL
        },        
    },
    
    // Features
    .feature[0] = {
        .enabled = 1,
        .feature_id = CMC_FEATURE_HORN_SIGNALLING
    }
};
