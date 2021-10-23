/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#ifndef testLibDef
    #define testLibDef
    #if (ARDUINO >= 100)
        #include "Arduino.h"
    #endif

    class Config {
        public:

            // *************************************************
            //   Common config settings, do not change
            // *************************************************
            struct PinConfig {
                uint8_t pin;
                bool enabeld;
            };

            // *************************************************
            //   Relay Unit Configuration
            // *************************************************
            // Set the controllers outputs to digital output pins that needs to be connected to relays
            // Digital pin 0 and 1 are normally used for serial commmunication to handlebar unit
            // Some analog pins can on most Arduinos also be used as a digital pin
            struct RelayUnitOutput {
                const PinConfig TurnSignalLeft = { 2, true };
                const PinConfig TurnSignalRight = { 3, true };
                const PinConfig MainPower = { 4, true };
                const PinConfig CoilGround = { 5, true };
                const PinConfig Starter = { 6, true };
                const PinConfig LightsPark = { 7, true };
                const PinConfig LightsLow = { 8, true };
                const PinConfig LightsHigh = { 9, true };
                const PinConfig Horn = { 10, true };
                const PinConfig Brake = { 11, true };
            };
        
            // Input pins config
            struct RelayUnitInput {
                const PinConfig TempSensor = { 0, false };
                const PinConfig OilSensor = { 0, false };
                const PinConfig NeutralSwitch = { 0, false };
                const PinConfig BrakeSwitch = { 0, false };
                const PinConfig EngineRunning = { 0, false }; // experimental
            };

            // Onboard led config
            struct RelayUnitOnBoardLed {
                const PinConfig config = { 13, true }; 
                const uint8_t on = HIGH; // Set HIGH or LOW to determin what sets the onboard led on or off
                const uint8_t off = LOW; // Ex: for Arduino Uno/Nano led in on using HIGH, but for NodeMCU led is on using LOW
            };

    };

#endif