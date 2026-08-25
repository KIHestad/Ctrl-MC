/**
  *********************************************************************************************
  * @file      cmc_config_type_unit.h
  * @brief     Configuration types for the unit properties and settings
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_TYPE_UNIT_H_
#define CMC_CONFIG_TYPE_UNIT_H_

// Default system configuration
#define CMC_CONFIG_SIGNATURE  0x4354524C    // Signature to identify if valid config exists in flash
#define CMC_CONFIG_VERSION    1              // Version number for the config structure, can be used for migration logic if the structure changes in future firmware versions
#define CMC_CONFIG_MAX_SUPPORTED_IO_UNITS 10 // Max number of I/O units supported by the system

// Unit names
typedef enum {
    CMC_CONFIG_UNIT_NAME_MAIN       = 0, // Main Unit
    CMC_CONFIG_UNIT_NAME_REAR       = 1, // Rear Unit
    CMC_CONFIG_UNIT_NAME_FRONT      = 2, // Front Unit
    CMC_CONFIG_UNIT_NAME_INSTRUMENT = 3, // Instrument Unit
    CMC_CONFIG_UNIT_NAME_AUXILIARY  = 4, // Auxiliary Unit
} cmc_config_unit_name_t;

// Supported input devices, buttons and sensors
typedef enum {
    CMC_CONFIG_IN_DEVICE_NONE = 0,
    CMC_CONFIG_IN_DEVICE_IGNITION = 1,
    CMC_CONFIG_IN_DEVICE_STARTER = 2,
    CMC_CONFIG_IN_DEVICE_KILL_SW = 3,
    CMC_CONFIG_IN_DEVICE_LIGHTS_MAIN = 10, // Master light switch to be used as on off for enable low and high beam
    CMC_CONFIG_IN_DEVICE_LIGHT_PARK = 11, // Master light switch to be used as on off for toggle on park only
    CMC_CONFIG_IN_DEVICE_LIGHT_MULTIFUNCTION = 12, // If the light switch is a single input that toggles through off → park → main (enables low and high beam) with each press
    CMC_CONFIG_IN_DEVICE_LIGHT_LOW_BEAM = 13,
    CMC_CONFIG_IN_DEVICE_LIGHT_HIGH_BEAM = 14,
    CMC_CONFIG_IN_DEVICE_LIGHT_HI_LOW_BEAM_TOGGLE = 15, // Toggle switch for low/high beam
    CMC_CONFIG_IN_DEVICE_TURN_LEFT = 20,
    CMC_CONFIG_IN_DEVICE_TURN_RIGHT = 21,
    CMC_CONFIG_IN_DEVICE_HORN = 22,
    CMC_CONFIG_IN_DEVICE_CLUTCH_LEVER = 23,
    CMC_CONFIG_IN_DEVICE_BRAKE_LEVER = 24,
    CMC_CONFIG_IN_DEVICE_BRAKE_PEDAL = 25,
    CMC_CONFIG_IN_DEVICE_NEUTRAL_SENSOR = 30,
    CMC_CONFIG_IN_DEVICE_OIL_SENSOR = 31,
    CMC_CONFIG_IN_DEVICE_WATER_TEMP_SENSOR = 32,
    CMC_CONFIG_IN_DEVICE_MENU_LEFT = 40,
    CMC_CONFIG_IN_DEVICE_MENU_RIGHT = 41,
    CMC_CONFIG_IN_DEVICE_MENU_UP = 42,
    CMC_CONFIG_IN_DEVICE_MENU_DOWN = 43,
    CMC_CONFIG_IN_DEVICE_MENU_SELECT = 44,
    CMC_CONFIG_IN_DEVICE_MENU_BACK = 45,
    
} cmc_config_in_device_t;

// button and sensor types, for digital inputs set how to interpret the button presses: direct or toggle
typedef enum {
    CMC_CONFIG_IN_USAGE_IGNORE         = 0, // Disable, ignore any input
    CMC_CONFIG_IN_USAGE_DIGITAL_DIRECT = 1, // Mechanical latching button stays permanently on (light on/off button) or if held when momentary button (horn hold button)
    CMC_CONFIG_IN_USAGE_DIGITAL_TOGGLE = 2, // Click to turn ON, click to turn OFF, to use a modern momentary-type button to act like a permanent button (select menu items)
    CMC_CONFIG_IN_USAGE_ANALOG         = 3, // Analog input device (fuel level sensor)
} cmc_config_in_usage_t;

// Supported output devices
typedef enum {
    CMC_CONFIG_OUT_DEVICE_NONE = 0,
    CMC_CONFIG_OUT_DEVICE_MAIN_PWR = 1, // Typically controlled by the ignition and powers main system units as the engine ecu, coil, fuel pump or other devices having continuous power when the ignition is on
    CMC_CONFIG_OUT_DEVICE_STARTER = 2, // Power output for the starter relay, typically only on when the starter button is pressed and the starter logic conditions are met
    CMC_CONFIG_OUT_DEVICE_LIGHT_PARK = 10,
    CMC_CONFIG_OUT_DEVICE_LIGHT_LOW_BEAM = 11,
    CMC_CONFIG_OUT_DEVICE_LIGHT_HIGH_BEAM = 12,
    CMC_CONFIG_OUT_DEVICE_LIGHT_TAIL = 13,
    CMC_CONFIG_OUT_DEVICE_LIGHT_BRAKE = 14,
    CMC_CONFIG_OUT_DEVICE_LIGHT_AUX = 15,
    CMC_CONFIG_OUT_DEVICE_TURN_LEFT_ALL = 20, // If both front and rear turn signals are connected to the same output channel
    CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_ALL = 21, // If both front and rear turn signals are connected to the same output channel
    CMC_CONFIG_OUT_DEVICE_TURN_LEFT_FRONT = 22, // If front and rear turn signals are connected to separate channels, use this for the front
    CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_FRONT = 23, // If front and rear turn signals are connected to separate channels, use this for the front
    CMC_CONFIG_OUT_DEVICE_TURN_LEFT_REAR = 24, // If front and rear turn signals are connected to separate channels, use this for the rear
    CMC_CONFIG_OUT_DEVICE_TURN_RIGHT_REAR = 25, // If front and rear turn signals are connected to separate channels, use this for the rear
    CMC_CONFIG_OUT_DEVICE_HORN = 30,
    CMC_CONFIG_OUT_DEVICE_INSTR_BG = 40, // Instrument cluster background light
    CMC_CONFIG_OUT_DEVICE_INSTR_LO = 41, 
    CMC_CONFIG_OUT_DEVICE_INSTR_HI = 42,
    CMC_CONFIG_OUT_DEVICE_INSTR_OIL = 43, // Oil pressure warning light
    CMC_CONFIG_OUT_DEVICE_INSTR_NEUTRAL = 44,
    CMC_CONFIG_OUT_DEVICE_INSTR_TURN_COMMON = 45, // If the turn signal indicator is a single light that blinks for both left and right turns
    CMC_CONFIG_OUT_DEVICE_INSTR_TURN_LEFT = 46,
    CMC_CONFIG_OUT_DEVICE_INSTR_TURN_RIGHT = 47,
    CMC_CONFIG_OUT_DEVICE_INSTR_HIGH_TEMP = 48,
    CMC_CONFIG_OUT_DEVICE_HEATED_GRIPS = 90
} cmc_config_out_device_t;

#endif /* CMC_CONFIG_TYPE_UNIT_H_ */