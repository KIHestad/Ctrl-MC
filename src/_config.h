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
// Some analog pins can on most Arduinos also be used as a digital pin, A1 (fist analog pin) can normally be referred to as pin 14 when used as digital pin

int MAIN_IGNITION_POSITIVE_OUTPUT_PIN   = 2;
int MAIN_IGNITION_GROUD_OUTPUT_PIN      = 3;
int START_MOTOR_OUTPUT_PIN              = 4;
int LIGHTS_PARK_OUTPUT_PIN              = 5;
int LIGHTS_LOW_BEAM_OUTPUT_PIN          = 6;
int LIGHTS_HIGH_BEAM_OUTPUT_PIN         = 7;
int LIGHTS_BRAKE_OUTPUT_PIN             = 8;
int SIGNAL_HORN_OUTPUT_PIN              = 9;
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
// Some analog pins can on most Arduinos also be used as a digital pin, A1 (fist analog pin) can normally be referred to as pin 14 when used as digital pin
// For each feature set input pin configuration like this: { pin_number, pin_read_type, analog_value_minimum, analog_value_maximum }
// Examples
// - Value for disabled feature: { -1 };
// - Value for digial read:      { 14, digitalPin };
// - Value for analog read:      { A1, analogPin, 190, 210 };

int MAIN_IGNITION_SWITCH_INPUT_PIN[4]        = { 12, digitalPin };
int START_MOTOR_SWITCH_INPUT_PIN[4]          = { 14, digitalPin }; 
int LIGHTS_MAIN_SWITCH_INPUT_PIN[4]          = { -1 };
int LIGHTS_LOW_HIGHT_SWITCH_INPUT_PIN[4]     = { A1, analogPin, 190, 210 };
int LIGHTS_HIGH_BEAM_INPUT_PIN[4]            = { A1, analogPin, 190, 210 };
int LIGHTS_BRAKE_SWITCH_INPUT_PIN[4]         = { A1, analogPin, 190, 210 };
int SIGNAL_HORN_SWITCH_INPUT_PIN[4]          = { A1, analogPin, 190, 210 };
int INDICATOR_LEFT_SWITCH_INPUT_PIN[4]       = { A1, analogPin, 190, 210 };
int INDICATOR_RIGHT_SWITCH_INPUT_PIN[4]      = { A1, analogPin, 190, 210 };
int CLUTCH_SWITCH_INPUT_PIN[4]               = { A1, analogPin, 190, 210 };
int BRAKE_SWITCH_INPUT_PIN[4]                = { A1, analogPin, 190, 210 };
int OIL_SENSOR_INPUT_PIN[4]                  = { -1 };
int NEUTRAL_SWITCH_INPUT_PIN[4]              = { -1 };
int ENGINE_RUNNING_SENSOR[4]                 = { -1 };

// *************************************
//   Main Ignition
// *************************************


// *************************************
//   Start/stop engine
// *************************************


// *************************************
//   Lights settings
// *************************************

int LIGHTS_LOW_HIGH_COMBINE = true;                       // Keep on low beam when high beam is triggered, set false to turn off low beam and only send power to high beam light bulb
int LIGHTS_HIGH_PASSING_FLASH_COUNT = 3;                  // Set to -1 to disable, else if main lights are in low beam mode, double cklick on High/Low swith will trigger flasing


// *************************************
// Brake Lights
// *************************************


// *************************************
//   Signal Horn
// *************************************

int HORN_INPUT_LONG_PRESS_DELAY = 1000;                   // Delay in milliseconds (1 sec = 1000) from button press to activation, useful if mapped to a multifuntional button


// *************************************
//   Indicators (Turn Signals)
// *************************************

int INDICATORS_BLINK_INTERVAL_SPEED = 750;                // Number of milliseconds (1000 = 1 second) for the blinking speed on turn signals. 500 = fast, 750 = normal, 1000 = slow.
int INDICATORS_AUTO_SHUT_OFF = 30;                        // Number of seconds before turn signals automatically are turned off. Set to -1 to disable it.
int INDICATORS_HAZARD_LONG_PRESS_ENABLE = 1500;           // Number of milliseconds (1000 = 1 second) for activating hazard pressing either L or R turn signal button, set -1 to disable the feature


// *************************************
// Display Module
// *************************************






