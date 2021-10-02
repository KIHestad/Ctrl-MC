/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// *************************************************
//   Arduino Output Pins Configuration
// *************************************************
// Set the controllers outputs to digital output pins that needs to be connected to relays
// Remember, digital pin 0 and 1 are normally used for serial commmunication to handlebar unit
// Some analog pins can on most Arduinos also be used as a digital pin
// Output pins for relays are listed below, first relay should visually be marked with numbered 1 for reference to _config file for the handlebar unit

const uint8_t OUTPUT_PIN_RELAY_COUNT = 10; // number of relays, the code managing serial connecteion are made for supporting maximum 16 relays
const uint8_t OUTPUT_PIN_RELAY[OUTPUT_PIN_RELAY_COUNT] {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // pin used for relays

// Pin to arduino onboard led
const uint8_t ONBOARD_LED_PIN = 13;     // Pin for onboard led, onboard led is primarely for debugging
const uint8_t ONBOARD_LED_ON = HIGH;    // Set HIGH or LOW to determin what sets the onboard led on or off
const uint8_t ONBOARD_LED_OFF = LOW;    // Ex: for Arduino Uno/Nano led in on using HIGH, but for NodeMCU led is on using LOW

// *************************************************
//   Arduino Input Pins Configuration
// *************************************************
// Set the controllers input pins to receive data as well, set to -1 if not to be used
// Remember, digital pin 0 and 1 are normally used for serial commmunication to handlebar unit
// Some analog pins can on most Arduinos also be used as a digital pin

const int8_t INPUT_PIN_TEMP = 12;
const int8_t INPUT_PIN_OIL = A0;
const int8_t INPUT_PIN_NEUTRAL = A1;
const int8_t INPUT_PIN_BRAKE = A2;
const int8_t INPUT_PIN_ENG_RUNNING = A3; // experimemtal