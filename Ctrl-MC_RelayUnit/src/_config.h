/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// *************************************************
//   Arduino Output Pins Configuration
// *************************************************
// Map the controllers outputs to digital output pins that needs to be connected to relays
// It will require a total of 10 relays (2 channel + 8 channel relay module) to get full functionality
// It is possible to map several outputs to the same pin, ex: park lights and low_beam lights can use same pin
// Set pin to -1 if the output is not to be used
// Digital pin 0 and 1 cannot be used, these are for serial commmunication to handlebar unit
// Some analog pins can on most Arduinos also be used as a digital pin

const uint8_t OUTPUT_PIN_MAIN_IGNITION            = 2;
const uint8_t OUTPUT_PIN_START_MOTOR              = 3;
const uint8_t OUTPUT_PIN_SIGNAL_HORN              = 4;
const uint8_t OUTPUT_PIN_LIGHTS_PARK              = 5;
const uint8_t OUTPUT_PIN_LIGHTS_LOW_BEAM          = 6;
const uint8_t OUTPUT_PIN_LIGHTS_HIGH_BEAM         = 7;
const uint8_t OUTPUT_PIN_LIGHTS_BRAKE             = 8;
const uint8_t OUTPUT_PIN_INDICATOR_LEFT           = 9;
const uint8_t OUTPUT_PIN_INDICATOR_RIGHT          = 10;
const uint8_t OUTPUT_PIN_AUX                      = 11;

// Pin to arduino onboard led
const uint8_t ONBOARD_LED_PIN                     = 13;