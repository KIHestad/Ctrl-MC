/**
  *********************************************************************************************
  * @file      cmc_config_type_def.h
  * @brief     Configuration types definitions 
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_TYPE_DEF_H_
#define CMC_CONFIG_TYPE_DEF_H_

// Default system configuration
#define CMC_CONFIG_SIGNATURE  0x4354524C // signature to identify if valid config exists in flash
#define CMC_CONFIG_MAX_SUPPORTED_IO_UNITS 4 // Max number of I/O units supported by the system
#define CMC_CONFIG_MAX_SUPPORTED_FEATURES 20 // Max number of features supported by the system

// Unit names
typedef enum {
    CMC_UNIT_MAIN       = 0, // Main Unit
    CMC_UNIT_REAR       = 1, // Rear Unit
    CMC_UNIT_FRONT      = 2, // Front Unit
    CMC_UNIT_INSTRUMENT = 3, // Instrument Unit
    CMC_UNIT_AUXILIARY  = 4, // Auxiliary Unit
} cmc_unit_name_t;

// Supported input devices, buttons and sensors
typedef enum {
    CMC_IN_NONE = 0,
    CMC_IN_IGNITION = 1,
    CMC_IN_STARTER = 2,
    CMC_IN_KILL_SW = 3,
    CMC_IN_LIGHTS_MAIN = 10, // Master light switch
    CMC_IN_LIGHT_PARK = 11,
    CMC_IN_LIGHT_LOW_BEAM = 12,
    CMC_IN_LIGHT_HIGH_BEAM = 13,
    CMC_IN_TURN_LEFT = 20,
    CMC_IN_TURN_RIGHT = 21,
    CMC_IN_HORN = 22,
    CMC_IN_CLUTCH_LEVER = 23,
    CMC_IN_BRAKE_LEVER = 24,
    CMC_IN_BRAKE_PEDAL = 25,
    CMC_IN_NEUTRAL_SENSOR = 30,
    CMC_IN_OIL_SENSOR = 31,
    CMC_IN_WATER_TEMP_SENSOR = 32,
    CMC_IN_MENU_LEFT = 40,
    CMC_IN_MENU_RIGHT = 41,
    CMC_IN_MENU_UP = 42,
    CMC_IN_MENU_DOWN = 43,
    CMC_IN_MENU_SELECT = 44,
    CMC_IN_MENU_BACK = 45,
} cmc_in_t;

// button types: How should the system interpret the button presses? (eg: classic, toggle, ignore)
typedef enum {
    CMC_IN_DEV_TYPE_IGNORE         = 0, // Disable, ignore any input
    CMC_IN_DEV_TYPE_DIGITAL_DIRECT = 1, // Mechanical latching button stays permanently on (light on/off button) or if held when momentary button (horn hold button)
    CMC_IN_DEV_TYPE_DIGITAL_TOGGLE = 2, // Click to turn ON, click to turn OFF, to use a modern momentary-type button to act like a permanent button (select menu items)
    CMC_IN_DEV_TYPE_ANALOG         = 3, // Analog input device (fuel level sensor)
} cmc_in_device_type_t;

// Supported output devices
typedef enum {
    CMC_OUT_NONE = 0,
    CMC_OUT_COIL = 1,
    CMC_OUT_STARTER = 2,
    CMC_OUT_LIGHT_PARK = 10,
    CMC_OUT_LIGHT_LOW_BEAM = 11,
    CMC_OUT_LIGHT_HIGH_BEAM = 12,
    CMC_OUT_LIGHT_TAIL = 13,
    CMC_OUT_LIGHT_BRAKE = 14,
    CMC_OUT_LIGHT_AUX = 15,
    CMC_OUT_TURN_LEFT_ALL = 20, // If both front and rear turn signals are connected to the same output channel
    CMC_OUT_TURN_RIGHT_ALL = 21, // If both front and rear turn signals are connected to the same output channel
    CMC_OUT_TURN_LEFT_FRONT = 22, // If front and rear turn signals are connected to separate channels, use this for the front
    CMC_OUT_TURN_RIGHT_FRONT = 23, // If front and rear turn signals are connected to separate channels, use this for the front
    CMC_OUT_TURN_LEFT_REAR = 24, // If front and rear turn signals are connected to separate channels, use this for the rear
    CMC_OUT_TURN_RIGHT_REAR = 25, // If front and rear turn signals are connected to separate channels, use this for the rear
    CMC_OUT_HORN = 30,
    CMC_OUT_INSTR_BG = 40, // Instrument cluster background light
    CMC_OUT_INSTR_LO = 41, 
    CMC_OUT_INSTR_HI = 42,
    CMC_OUT_INSTR_OIL = 43, // Oil pressure warning light
    CMC_OUT_INSTR_NEUTRAL = 44,
    CMC_OUT_INSTR_TURN_COMMON = 45, // If the turn signal indicator is a single light that blinks for both left and right turns
    CMC_OUT_INSTR_TURN_LEFT = 46,
    CMC_OUT_INSTR_TURN_RIGHT = 47,
    CMC_OUT_INSTR_HIGH_TEMP = 48,
    CMC_OUT_HEATED_GRIPS = 90
} cmc_out_t;

// Supported features
typedef enum {
    CMC_FEATURE_NONE = 0,
    CMC_FEATURE_HORN_SIGNALLING = 1, // Standard horn feature when horn button is pressed, turn on horn output    
} cmc_feature_type_t;

#endif /* CMC_CONFIG_TYPE_DEF_H_ */