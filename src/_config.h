/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

// *************************************************
// Inputs, outputs and features
// *************************************************
// The controller has differen features that can be enabled or disabled
// A feature is a code part controlling "somthing" on the motorcycle, ex: controlling the signal horn
// Most features has one or several inputs and the same for outputs


// *************************************************
//   Arduino Input Pins Configuration
// *************************************************
// Map the controllers inputs to relecant input pin for reading buttons/switches signals, levers/pedals or sensors
// It is possible to map several features to same pin, ex: handlebar buttons connected in series using a resistors between each button delivers different values per button back to the analog input pin
// Some analog pins can on most Arduinos also be used as a digital pin, A0 (fist analog pin) can normally be referred to as pin 14 when used as digital pin
// For each feature set input pin configuration like this: { pin_number, short_name, pin_read_type, analog_pin_expected_read_value (20 - 1023) }
// Examples
// - Value for disabled inputs:  { false }; // Other values can be added, will be ignored by the system
// - Value for digial read:      { true, 12, digitalPin, 0, "IGN-SW", "Ignition Switch" };
// - Value for analog read:      { true, A0, analogPin, 1023, "CLUTCH", "Clutch Lever" };
int ANALOG_PIN_VALUE_VARIATION = 25; // This value will be subtracted and added to the analog_value to get min- and max reading acceptance range
// Normally only the pin number and analog_pin_expected_read_value should be edited and set according to the Arduino pin actually used and input signal according to what values returned
// When using several buttons on one analog pin connected in series, the reccomended resistor is: 150ohm (but it can vary)
Input MAIN_IGNITION_SWITCH_INPUT        = { false, 12, digitalPin, 0, "IGN-SW", "Ignition Switch" };
// Lever left
Input CLUTCH_SWITCH_INPUT               = { true, A0, analogPin, 1023, "CLUTCH", "Clutch Lever" };
// Normally on left hand side handle button controls
Input SIGNAL_HORN_SWITCH_INPUT          = { true, A0, analogPin, 145, "HORN", "Horn Button" }; // When triggered using long press it can use same pin as for ligths hi/lo
Input LIGHTS_LOW_HIGHT_SWITCH_INPUT     = { true, A0, analogPin, 145, "HI/LO", "Lights High/Low Beam Button" }; // Triggered with short press, can be same as signal horn
Input INDICATOR_LEFT_SWITCH_INPUT       = { true, A0, analogPin, 437, "T-LEFT", "Turn Signal Left Button" };
Input INDICATOR_RIGHT_SWITCH_INPUT      = { true, A0, analogPin, 254, "T-RIGHT", "Turn Signal Left Button" };
// Normally on right hand side handle button controls
Input LIGHTS_MAIN_SWITCH_INPUT          = { false }; // Can be ignored if not having enough buttons, lights can be selected from display menu
Input START_MOTOR_SWITCH_INPUT          = { true, A1, analogPin, 145, "STA/STP", "Start/Stop Button" }; // Can be safer to use separate digital pin in case series buttons has dirty signal
Input DISPLAY_MENU_ITEM_SELECT_INPUT    = { true, A1, analogPin, 437, "D-SEL", "Display Select Item" };
Input DISPLAY_MENU_ITEM_NEXT_INPUT      = { true, A1, analogPin, 254, "D-NEXT", "Display Goto Next" };
// Lever right
Input BRAKE_SWITCH_INPUT                = { true, A1, analogPin, 1023, "BRAKE", "Brake Lever" };
// Sensors
Input OIL_SENSOR_INPUT                  = { false };
Input NEUTRAL_SWITCH_INPUT              = { false };
Input ENGINE_RUNNING_SENSOR_INPUT       = { false };

// Several buttons can be connected to the same pin when using analog input
// In this section list the inputs that are connected to the same pin, it makes reading the buttons faster for the methods, as it is not needed to perform actual analogRead per input
bool HANDLEBAR_SWITCHES_LEFT_ENABLED = true;
Input HANDLEBAR_SWITCHES_LEFT[5] = {                 
    CLUTCH_SWITCH_INPUT,
    SIGNAL_HORN_SWITCH_INPUT,
    LIGHTS_LOW_HIGHT_SWITCH_INPUT,
    INDICATOR_LEFT_SWITCH_INPUT,
    INDICATOR_RIGHT_SWITCH_INPUT 
};
bool HANDLEBAR_SWITCHES_RIGHT_ENABLED = true;
Input HANDLEBAR_SWITCHES_RIGHT[4] = {                 
    START_MOTOR_SWITCH_INPUT,
    START_MOTOR_SWITCH_INPUT,
    DISPLAY_MENU_ITEM_SELECT_INPUT,
    BRAKE_SWITCH_INPUT
};

// *************************************************
//   Arduino Output Pins Configuration
// *************************************************
// Map the controllers outputs to digital output pins that needs to be connected to relelays
// It will require a total of 10 relays (2 channel + 8 channel relay module) to gett full functionality
// It is possible to map several outputs to the same pin, ex: park lights and low_beam lights can use same pin
// Set pin to -1 if the output is not to be used
// Digital pin 0 and 1 are not safe to use with relay modules, these are used when booting the Arduino causes relay to be triggered
// Some analog pins can on most Arduinos also be used as a digital pin, A0 (fist analog pin) can normally be referred to as pin 14 when used as digital pin

int MAIN_IGNITION_POSITIVE_OUTPUT_PIN   = 2;
int MAIN_IGNITION_GROUD_OUTPUT_PIN      = 3;
int START_MOTOR_OUTPUT_PIN              = 4;
int SIGNAL_HORN_OUTPUT_PIN              = 5;
int LIGHTS_PARK_OUTPUT_PIN              = 6;
int LIGHTS_LOW_BEAM_OUTPUT_PIN          = 7;
int LIGHTS_HIGH_BEAM_OUTPUT_PIN         = 8;
int LIGHTS_BRAKE_OUTPUT_PIN             = 9;
int INDICATOR_LEFT_OUTPUT_PIN           = 10;
int INDICATOR_RIGHT_OUTPUT_PIN          = 11;

// Pin to arduino onboard led
int ONBOARD_LED_PIN                     = 13;

// Pins to OLED Display using I2C interface, SCL and SDA pins
int DISPLAY_SDA_OUTPUT_PIN              = A4;
int DISPLAY_SCL_OUTPUT_PIN              = A5;


// *************************************************
//   Feature: Testing
// *************************************************

bool TEST_READ_ENABLED_INPUTS = false;    // Display in terminal inpus set as enabled


// *************************************************
//   Feature: Main Ignition
// *************************************************

bool IGNITION_FEATURE_ENABLED = true;
// Ignition password
bool IGN_PASSWORD_ENABLED = true;                           // Enables to power on the motorcycle by a spesified button press combination
Input IGN_PASSWORD_START_INPUT = CLUTCH_SWITCH_INPUT;       // Button or lever to start/restart entering password, cannot be used as part of the password
const int IGN_PASSWORD_LENGTH = 5;                          // Length of password
Input IGN_PASSWORD[IGN_PASSWORD_LENGTH] = {                 // The actual password as an array of inputs
    INDICATOR_LEFT_SWITCH_INPUT,
    INDICATOR_RIGHT_SWITCH_INPUT,
    INDICATOR_LEFT_SWITCH_INPUT,
    INDICATOR_RIGHT_SWITCH_INPUT,
    SIGNAL_HORN_SWITCH_INPUT 
};


// *************************************************
//   Feature: Start/stop engine
// *************************************************


// *************************************************
//   Feature: Lights settings
// *************************************************

bool LIGHTS_FEATURE_ENABLED = true;
bool LIGHTS_LOW_HIGH_COMBINE = true;                    // Keep on low beam when high beam is triggered, set false to turn off low beam and only send power to high beam light bulb
int LIGHTS_HIGH_PASSING_FLASH_COUNT = 3;                // Set to -1 to disable, else if main lights are in low beam mode, double cklick on High/Low swith will trigger flasing


// *************************************************
//  feature: Brake Lights
// *************************************************


// *************************************************
//   feature: Signal Horn
// *************************************************

bool HORN_FEATURE_ENABLED = true;
int HORN_INPUT__DELAY = 1000;                           // Delay in milliseconds (1 sec = 1000) from button press to activation, useful if mapped to a multifuntional button, set to 0 to immediate activate horn on button press


// *************************************************
//   feature: Indicators (Turn Signals)
// *************************************************

bool INDICATIORS_FEATURE_ENABLED = true;
int INDICATORS_BLINK_INTERVAL_SPEED = 750;              // Number of milliseconds (1000 = 1 second) for the blinking speed on turn signals. 500 = fast, 750 = normal, 1000 = slow.
int INDICATORS_AUTO_SHUT_OFF = 30;                      // Number of seconds before turn signals automatically are turned off. Set to -1 to disable it.
int INDICATORS_HAZARD_LONG_PRESS_ENABLE = 1500;         // Number of milliseconds (1000 = 1 second) for activating hazard pressing either L or R turn signal button, set -1 to disable the feature


// *************************************************
// Display Module
// *************************************************






