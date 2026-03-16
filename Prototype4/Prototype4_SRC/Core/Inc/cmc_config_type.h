#ifndef CMC_CONFIG_TYPE_H_
#define CMC_CONFIG_TYPE_H_

#include <stdint.h>
#include <stdbool.h>

/* ==================================================================================
 * SYSTEM SETTINGS & LIMITS
 * ================================================================================== */
#define CMC_CONFIG_SIGNATURE        0x4354524C  // Identifies if valid config exists
#define CMC_MAX_SUPPORTED_IO_UNITS  4           // Max number of Ctrl MC I/O-units in the system (eg: Front, Rear, Entertainment, etc)
#define CMC_MAX_SUPPORTED_RULES     64          // Max number of rules for controlling the outputs (eg: turn on light when ignition is on and light switch is on)
#define CMC_MAX_INPUTS_D            10          // Max physical digital buttons/sensors
#define CMC_MAX_INPUTS_A            2           // Max physical analog sensors
#define CMC_MAX_OUTPUTS             6           // Max Infineon PROFET/SPOC channels

/* ==================================================================================
 * SUPPORTED EQUIPMENT = TO BE CONNECTED TO OUTPUT +12V CHANNELS
 * NOTE: Might want to stick to max 255 for storing the value into a uint8_t 
 * ================================================================================== */
typedef enum {
    CMC_EQP_NONE = 0,
    CMC_EQP_COIL = 1,
    CMC_EQP_STARTER = 2,
    CMC_EQP_LIGHT_PARK = 10,
    CMC_EQP_LIGHT_LOW_BEAM = 11,
    CMC_EQP_LIGHT_HIGH_BEAM = 12,
    CMC_EQP_LIGHT_TAIL = 13,
    CMC_EQP_LIGHT_BRAKE = 14,
    CMC_EQP_LIGHT_AUX = 15,
    CMC_EQP_TURN_LEFT = 20,
    CMC_EQP_TURN_RIGHT = 21,
    CMC_EQP_HORN = 22,
    CMC_EQP_INSTR_BG = 30,
    CMC_EQP_INSTR_LO = 31,
    CMC_EQP_INSTR_HI = 32,
    CMC_EQP_INSTR_OIL = 33,
    CMC_EQP_INSTR_NEUTRAL = 34,
    CMC_EQP_INSTR_TURN_COMMON = 35,
    CMC_EQP_INSTR_TURN_LEFT = 36,
    CMC_EQP_INSTR_TURN_RIGHT = 37,
    CMC_EQP_INSTR_HIGH_TEMP = 38,
    CMC_EQP_HEATED_GRIPS = 90
} cmc_equipment_t;

// The final configuration for each output channel, linking the physical channel to the equipment it's controlling
typedef struct {
    uint8_t channel; // Which output channel on Infineon PROFET/SPOC switch is this equipment connected to? (1 to CMC_MAX_OUTPUTS)
    uint8_t equipment_id; // Maps to cmc_equipment_t, what pin is connected to (eg: coil, starter, light, horn, etc)
    uint8_t reserved[2]; // Reserved to explicitly make it 4 bytes.
} cmc_output_config_t;

/* ==================================================================================
 * SUPPORTED BUTTONS AND SENSORS = TO BE CONNECTED TO INPUT PINS
 * ================================================================================== */
typedef enum {
    CMC_INP_NONE = 0,
    CMC_INP_IGNITION = 1,
    CMC_INP_STARTER = 2,
    CMC_INP_KILL = 3,
    CMC_INP_LIGHTS_MAIN = 10, // Master light switch
    CMC_INP_LIGHT_PARK = 11,
    CMC_INP_LIGHT_LOW_BEAM = 12,
    CMC_INP_LIGHT_HIGH_BEAM = 13,
    CMC_INP_TURN_LEFT = 20,
    CMC_INP_TURN_RIGHT = 21,
    CMC_INP_HORN = 22,
    CMC_INP_CLUTCH_LEVER = 23,
    CMC_INP_BRAKE_LEVER = 24,
    CMC_INP_BRAKE_PEDAL = 25,
    CMC_INP_NEUTRAL_SENSOR = 30,
    CMC_INP_OIL_SENSOR = 31,
    CMC_INP_WATER_TEMP_SENSOR = 32,
    CMC_INP_MENU_LEFT = 40,
    CMC_INP_MENU_RIGHT = 41,
    CMC_INP_MENU_UP = 42,
    CMC_INP_MENU_DOWN = 43,
    CMC_INP_MENU_SELECT = 44,
    CMC_INP_MENU_BACK = 45,
} cmc_input_t;

// butoon types: How should the system interpret the button presses? (eg: classic, toggle, ignore)
typedef enum {
    CMC_BTN_IGNORE      = 0, // Disable button, ignore all presses and features
    CMC_BTN_CLASSIC     = 1, // ON only while button is set to permanent ON-position (eg: light switch ser to ON) or held if momentary button (eg: horn button pressed and held)
    CMC_BTN_TOGGLE      = 2, // Click to turn ON, click to turn OFF, to use a modern momentary-type button to act like a permanent button (eg: momentary button click used to select menu items)
} cmc_button_t;

// The final configuration for each input pin, linking the physical pin to the button/sensor it's connected to and how it should be interpreted
typedef struct {
    uint8_t pin; // Which physical input pin is this button/sensor connected to? (1 to CMC_MAX_INPUTS_D for digital, 1 to CMC_MAX_INPUTS_A for analog)
    uint8_t input_id; // Maps to cmc_input_t, what button/sensor is connected to (eg: ignition, clutch lever, light switch, etc)
    uint8_t button_type; // Maps to cmc_button_t, how should the system interpret the button presses? (eg: classic, toggle, ignore)
    uint8_t reserved; // Reserved to explicitly make it 4 bytes.
} cmc_input_config_t;

/* ====================================================================
 * RULE LOGIC
 * ==================================================================== */
 typedef enum {
    CMC_OP_DIRECT = 0, // Direct link: If Cond1 is true, do the action. (Ignores Cond2)
    CMC_OP_AND    = 1, // BOTH Cond1 and Cond2 must be true
    CMC_OP_OR     = 2, // EITHER Cond1 or Cond2 must be true
    CMC_OP_XOR    = 3  // EXCLUSIVE OR (One true, one false)
} cmc_rule_operator_t;

typedef enum {
    CMC_ACT_DO_NOTHING = 0,
    CMC_ACT_TURN_ON    = 1, // Power the equipment
    CMC_ACT_TURN_OFF   = 2, // Cut power to the equipment
    CMC_ACT_BLINK      = 3  // Start a blink timer for the equipment
} cmc_rule_action_t;

typedef struct {
    uint8_t cond1_input_id;     // First condition (eg: ignition ON)
    uint8_t rule_operator_id;   // How to evaluate the conditions (direct, AND, OR, XOR)
    uint8_t cond2_input_id;     // Second condition (eg: light switch ON) - ignored if operator is DIRECT
    uint8_t rule_action_id;     // What to do if the conditions are met (eg: turn on light)
    uint16_t blink_interval_ms; // If action is BLINK, how fast should it blink? (eg: 500 for 500ms ON, 500ms OFF)
    uint16_t blink_duration_ms; // If action is BLINK, how long should it keep blinking? (eg: 5000 for 5 seconds total)
    uint8_t target_unit_id;     // Which unit owns the output? 
    uint8_t target_output_id;   // Maps to cmc_output_config_t, which output channel/equipment does this rule control?
    uint8_t reserved[2];        // Padding to make the total struct 12 bytes (divisible by 4)
} cmc_rule_t;

/* ==================================================================================
 * UNIT CONFIGURATION = TO DESCRIBE THE DIFFERENT CTRL MC UNITS IN THE SYSTEM
 * JUST FOR INFORMATION PURPOSES, NOT USED IN THE LOGIC (YET)
 * ================================================================================== */
typedef struct {
    uint8_t unit_id; // The number of the I/O units configures, (1 to CMC_MAX_SUPPORTED_IO_UNITS)
    char name[20]; // Friendly name for the unit (eg: "Front", "Rear", "Entertainment", etc)
    uint8_t output_channels_used; // How many output channels are used? (1 to CMC_MAX_OUTPUTS)
    uint8_t input_digital_pins_used; // How many digital input pins are used? (1 to CMC_MAX_INPUTS_D)
    uint8_t input_analog_pins_used; // How many analog input pins are used? (1 to CMC_MAX_INPUTS_A)
    cmc_output_config_t output_equipment[CMC_MAX_OUTPUTS]; // What equipment is connected to each output channel?
    cmc_input_config_t input_digital[CMC_MAX_INPUTS_D]; // What button/sensor is connected to each digital input pin?
    cmc_input_config_t input_analog[CMC_MAX_INPUTS_A]; // What button/sensor is connected to each analog input pin?
} cmc_io_unit_config_t;

/* ====================================================================
 * THE MASTER CONFIGURATION STRUCTURE 
 * ==================================================================== */
typedef struct {
    uint32_t signature;          // To check if config is valid for the unit. It should be set to CMC_CONFIG_SIGNATURE if valid, if reset/newly flashed, it will be 0xFFFFFFFF or 0x00000000)
    uint32_t global_config_hash; // Hash of the systems global configuration, to be compared between units at startup by doing a canbus handshake to verify same global config across all units
    uint8_t  active_unit_count;  // Number of active I/O units in the system, to tell the loops when to stop. Should be less than or equal to CMC_MAX_SUPPORTED_IO_UNITS
    uint8_t  active_rule_count;  // Number of active rules in the system, to tell the loops when to stop. Should be less than or equal to CMC_MAX_SUPPORTED_RULES
    uint8_t  reserved[2];        // Pad to 4 bytes
    cmc_io_unit_config_t io_unit[CMC_MAX_SUPPORTED_IO_UNITS]; // Info about each Ctrl MC unit in the system (eg: Front, Rear, Entertainment, etc)
    cmc_rule_t rule[CMC_MAX_SUPPORTED_RULES]; // What are the rules for controlling each output channel?
} cmc_global_config_t;

/* ====================================================================
 * GLOBAL EXTERNAL DECLARATION
 * ==================================================================== */
extern cmc_global_config_t cmc_global_config;

#endif /* CMC_CONFIG_TYPE_H_ */