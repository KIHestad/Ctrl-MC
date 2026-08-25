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
    .units_required  = 1, // The expected number of IO units the system needs to operate, this is also the number of units that should be present in the configuration

    // Unit number 1: Front I/O Unit
    .io_unit[0] = {
        .unit_id         = 1,
        .unit_name_id    = CMC_CONFIG_UNIT_NAME_FRONT, 
        .in_used         = 8, // Number of input connectors used on this unit
        .out_used        = 7, // Number of output channels used on this unit
        
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
            .device_id   = CMC_CONFIG_IN_DEVICE_LIGHT_HI_LOW_BEAM_TOGGLE,
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
            .device_id   = CMC_CONFIG_IN_DEVICE_NEUTRAL_SENSOR,
            .usage_id     = CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE
        },
        .in[7] = {       // Input button 8
            .enabled     = 1,
            .device_id   = CMC_CONFIG_IN_DEVICE_LIGHT_MULTIFUNCTION,
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
            .device_id   = CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL
        },
        .out[2] = {      // Output channel 3
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_PARK
        },
        .out[3] = {      // Output channel 4
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL
        },
        .out[4] = {      // Output channel 5
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM
        },
        .out[5] = {      // Output channel 6
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM
        },
        .out[6] = {      // Output channel 7
            .enabled     = 1,
            .device_id   = CMC_CONFIG_OUT_DEVICE_INSTR_NEUTRAL
        },
        .out[7] = {      // Output channel 8
            .enabled     = 0,
            .device_id   = CMC_CONFIG_OUT_DEVICE_NONE
        }
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
            .device_id   = CMC_CONFIG_OUT_DEVICE_LIGHT_PARK
        },
        .out[1] = {       // Output channel 2
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM
        },
        .out[2] = {       // Output channel 3
            .enabled      = 1,
            .device_id    = CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM
        }
    },
    .feature_test_channels = {
        .enabled = 0, // Set to 1 to enable the test channel feature, set to 0 to disable it and the system will ignore any test channel-related logic
    },
    .feature_ignition = {
        .enabled = 0, // 0 = disabled: ignition always on (no sensor required, safe default for bench testing)
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running 
    },
    .feature_starter = {
        .enabled = 1, // 0 = disabled: starter output never activates; set to 1 to enable input-driven starter control
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
    },
    .feature_horn = {
        .enabled = 1, // Set to 1 to enable the horn feature, set to 0 to disable it and the system will ignore any horn-related logic
        .auto_shut_off_sec = 3, // Automatically turn off the horn after this many seconds if the button is held continuously, set to 0 to disable auto shut-off
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running

    },
    .feature_direction_indicator = {
        .enabled = 1,              // Set to 1 to enable the direction indicator feature
        .blink_interval_x10ms = 50, // Blink on/off interval (100 = 1 second, 50 = half a second - number in 1/100 of a second)
        .auto_shut_off_sec = 30,    // Duration in seconds after which the direction indicator should automatically shut off, not applicable if hazard mode
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
    },
    .feature_light = {
        .enabled                  = 1,  // Set to 1 to enable the lighting feature
        .park_light_enabled       = 1,  // 1 = motorcycle has a park/side light; 0 = no park light
        .high_beam_keeps_low_beam = 1,  // 0 = low beam off when high beam on; 1 = both beams on simultaneously
        .main_light_input_mode    = CMC_FEATURE_LIGHT_MAIN_MODE_MULTIFUNCTION_TOGGLE, // Use a single multifunction toggle button
        .hi_lo_beam_input_mode    = CMC_FEATURE_LIGHT_HIBEAM_MODE_TOGGLE,             // Use a single hi/lo toggle switch
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
    },
    .feature_brake_light = {
        .enabled = 1,  // Set to 1 to enable the brake light feature
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running

    },
    .feature_neutral = {
        .enabled = 1,  // Set to 1 to enable the neutral indicator feature
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
    },
    .feature_oil_pressure = {
        .enabled = 0,  // Set to 1 to enable the oil pressure warning feature
        .enabled_on_test = 0 // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running

    },
    .feature_channel_info = {
        // Per-channel power, supply voltage, and fault reporting over CAN, needed for display units to show channel status and power consumption
        .enabled                = 1,
        .enabled_on_test        = 1, // Set to 1 to enable when test feature are enabled, set to 0 to disable it while test feature are running
        .temp_unit              = CMC_TEMP_UNIT_CELSIUS,
        .compensation_enabled   = 0, // set 0 to report raw current-sense values, eg. when calibrating a new switch
        
        // The following overview_enabled flags control the periodic broadcast of channel overview messages over CAN
        // These messages are not read by the Ctrl MC system, only for reporting when using a CAN bus analyzer like Savvycan
        .overview_enabled       = 0,  // requires CAN FD capable adapter; set 1 only when hardware supports it
        .overview_enabled_01_03 = 1, // classic CAN, ch1-3; matches this board's 3 physical output channels
        .overview_enabled_04_06 = 1, // classic CAN, ch4-6; enable only if the unit has these channels
        .overview_enabled_07_09 = 1, // classic CAN, ch7-9; enable only if the unit has these channels
        .overview_enabled_10_12 = 0, // classic CAN, ch10-12; enable only if the unit has these channels
    }
        
};
