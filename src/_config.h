/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

// *************************************
//   Arduino Output Pins Configuration
// *************************************
// Map the controllers features to digital output pins that needs to be connected to relelays
// It will require a total of 10 relays (2 channel + 8 channel relay module) to gett full functionality
// It is possible to map several features to same pin, ex: park and low_beam lights can use same pin
// Set pin to -1 if feature is not to be used
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

// *************************************
//   Arduino Input Pins Configuration
// *************************************
// Map the controllers features to input pins that needs to be connected to buttons/switches, levers/pedals or sensors
// It is possible to map several features to same pin, ex: handlebar buttons connected in series using a resistors between each button delivers different values per button back to the analog input pin
// Some analog pins can on most Arduinos also be used as a digital pin, A0 (fist analog pin) can normally be referred to as pin 14 when used as digital pin
// For each feature set input pin configuration like this: { pin_number, short_name, pin_read_type, analog_pin_expected_read_value (20 - 1023) }
// Examples
// - Value for disabled feature: { "NAME", -1 };
// - Value for digial read:      { "NAME, 12, digitalPin };
// - Value for analog read:      { "NAME", analogPin, 190 };
int ANALOG_PIN_VALUE_VARIATION = 25; // This value will be subtracted and added to the analog_value to get min- and max reading acceptance range
// Normally only the pin number and analog_pin_expected_read_value should be edited and set according to the Arduino pin actually used and input signal according to what values returned
// When using several buttons on one analog pin connected in series, the reccomended resistor is: 150ohm (but it can vary)
Input MAIN_IGNITION_SWITCH_INPUT        = { 12, "IGN-SW", digitalPin };
// Lever left
Input CLUTCH_SWITCH_INPUT               = { A0, "CLUTCH", analogPin, 9999 };
// Normally on left hand side handle button controls
Input SIGNAL_HORN_SWITCH_INPUT          = { A0, "HORN", analogPin, 9999 }; // Triggered with long press - Can be same as ligths hi/lo
Input LIGHTS_LOW_HIGHT_SWITCH_INPUT     = { A0, "HI/LO", analogPin, 9999 }; // Triggered with short press - can be same as signal horn
Input INDICATOR_LEFT_SWITCH_INPUT       = { A0, "T-LEFT", analogPin, 112 };
Input INDICATOR_RIGHT_SWITCH_INPUT      = { A0, "T-RIGHT", analogPin, 184 };
// Normally on right hand side handle button controls
Input LIGHTS_MAIN_SWITCH_INPUT          = { -1, "LIGHTS" };                      // Can be ignored if not having enough buttons, lights can be selected from display menu
Input START_MOTOR_SWITCH_INPUT          = { A0, "STA/STP", analogPin, 1014 }; // Can be safer to use separate digital pin in case series buttons has dirty signal
Input DISPLAY_MENU_ITEM_NEXT_INPUT      = { A0, "D-NEXT", analogPin, 278 };
Input DISPLAY_MENU_ITEM_SELECT_INPUT    = { A0, "D-SEL", analogPin, 452 };
// Lever right
Input BRAKE_SWITCH_INPUT                = { A0, "BRAKE", analogPin, 9999 };
// Sensors
Input OIL_SENSOR_INPUT                  = { -1, "OIL" };
Input NEUTRAL_SWITCH_INPUT              = { -1, "NEUTR" };
Input ENGINE_RUNNING_SENSOR_INPUT       = { -1 ,"E-RUN"};

// *************************************
//   Testing
// *************************************
bool TEST_READ_ENABLED_INPUTS = true;  // Display in terminal inpus set as enabled

// *************************************
//   Main Ignition
// *************************************

bool IGN_PASSWORD_ENABLED = true;                           // Enables to power on the motorcycle by a spesified button press combination
Input IGN_PASSWORD_START_INPUT = START_MOTOR_SWITCH_INPUT;  // Button or lever to start/restart entering password, cannot be used as part of the password
const int IGN_PASSWORD_LENGTH = 5;                          // Length of password
Input IGN_PASSWORD[IGN_PASSWORD_LENGTH] = {                 // The actual password as an array of inputs
    INDICATOR_LEFT_SWITCH_INPUT,
    INDICATOR_RIGHT_SWITCH_INPUT,
    DISPLAY_MENU_ITEM_NEXT_INPUT,
    DISPLAY_MENU_ITEM_SELECT_INPUT,
    DISPLAY_MENU_ITEM_SELECT_INPUT
};

// *************************************
//   Start/stop engine
// *************************************


// *************************************
//   Lights settings
// *************************************

int LIGHTS_LOW_HIGH_COMBINE = true;        // Keep on low beam when high beam is triggered, set false to turn off low beam and only send power to high beam light bulb
int LIGHTS_HIGH_PASSING_FLASH_COUNT = 3;   // Set to -1 to disable, else if main lights are in low beam mode, double cklick on High/Low swith will trigger flasing


// *************************************
// Brake Lights
// *************************************


// *************************************
//   Signal Horn
// *************************************

int HORN_INPUT_LONG_PRESS_DELAY = 1000;                 // Delay in milliseconds (1 sec = 1000) from button press to activation, useful if mapped to a multifuntional button


// *************************************
//   Indicators (Turn Signals)
// *************************************

int INDICATORS_BLINK_INTERVAL_SPEED = 750;              // Number of milliseconds (1000 = 1 second) for the blinking speed on turn signals. 500 = fast, 750 = normal, 1000 = slow.
int INDICATORS_AUTO_SHUT_OFF = 30;                      // Number of seconds before turn signals automatically are turned off. Set to -1 to disable it.
int INDICATORS_HAZARD_LONG_PRESS_ENABLE = 1500;         // Number of milliseconds (1000 = 1 second) for activating hazard pressing either L or R turn signal button, set -1 to disable the feature


// *************************************
// Display Module
// *************************************






