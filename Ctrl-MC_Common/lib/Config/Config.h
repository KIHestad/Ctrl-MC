/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#ifndef configDef
    #define configDef
    #if (ARDUINO >= 100)
        #include "Arduino.h"
    #endif
    #include "../OnBoardLed/OnBoardLed.h"

    class Config {
        public:

            // *************************************************
            //   Common config settings, do not change
            // *************************************************
            struct Feature {
                bool enabled; // Used to set feature enabled or disabled
                uint8_t pin; // Pin on Arduino for the feature
            };
            const unsigned long serialCommSpeed = 9600;

            // *************************************************
            //   Relay Unit Configuration
            // *************************************************
            
            // Outputs - relays / onboard led
            class RelayUnitOutput {
                public:
                    // Enable/disable relay unit features, set arduino pin connected to each relay
                    const Feature mainPower =       { true, 2 };
                    const Feature coilGround =      { true, 3 };
                    const Feature starterMotor =    { true, 4 };
                    const Feature horn =            { true, 5 };
                    const Feature turnSignalLeft =  { true, 6 };
                    const Feature turnSignalRight = { true, 7 };
                    const Feature lightPark =       { true, 8 };
                    const Feature lightLow =        { true, 9 };
                    const Feature lightHigh =       { true, 10 };
                    const Feature lightBrake =      { true, 11 };
                    // Onboard led settings: enabled/disabled, pinNumber, value to turn led on, value to turn led off
                    // If not to be used, set enabled to false, the remaining vars are ignored in this case, ex: { false, 0, 0, 0 }
                    const OnBoardLed::Settings onBoardLed = { true, 13, HIGH, LOW };
            };
        
            // Inputs - swithes and sensors located neard relay unit
            class RelayUnitInput {
                public:
                    const Feature tempSensor =          { false, 0 };
                    const Feature oilSensor =           { false, 0 };
                    const Feature neutralSwitch =       { false, 0 };
                    const Feature brakeRearSwitch =     { false, 0 };
                    const Feature engineRunningSensor = { false, 0 }; // experimental
            };
           
            // *************************************************
            //   Display Unit Configuration
            // *************************************************

            // Outputs - onboard led
            class DisplayUnitOutput {
                public:
                    // Onboard led settings: enabled/disabled, pinNumber, value to turn led on, value to turn led off
                    // If not to be used, set enabled to false, the remaining vars are ignored in this case, ex: { false, 0, 0, 0 }
                    const OnBoardLed::Settings onBoardLed = { true, 2, HIGH, LOW };
            };

            // Inputs - buttons on handlebar
            class DisplayUnitInput {
                public:
                    // Enable/disable handlebar buttons, set arduino pin connected to each button
                    const Feature clutch =          { true, 13 };
                    const Feature indicatorLeft =   { true, 12 };
                    const Feature indicatorRight =  { true, 14 };
                    const Feature lightsHiLo =      { true, 27 };
                    const Feature startStop =       { true, 26 };
                    const Feature menuSelect =      { true, 25 };
                    const Feature menuNext =        { true, 33 };
                    const Feature brakeFront =      { true, 32 };
            };

            // Test Buttons - feature that enables to activate display to show what buttons is pressed, activate using long press for spesific button
            class TestButtons {
                public:
                    bool enabled = true;                                // Set enabled to activate feature
                    unsigned long longPressDuration = 3000;             // Set number of millliseconds to hold down button to activate feature
                    Feature inititateButton = Feature();

                    // constructur
                    TestButtons() {
                        DisplayUnitInput duInput = DisplayUnitInput();
                        this->inititateButton = duInput.menuSelect;     // Set what button to be used for enabling feature, cannot be the same as for ignition button password feature
                    }
            };

            // Ignition Password
            class IgnitionButtonPassword {
                public:
                    bool enabled = true;                                // Set enabled to activate ignition button password
                    int pwLength = 4;                                   // Length of password
                    Feature pwButtons[4];                               // Password button array, set same length as above
                    Feature inititateButton;

                    // constructur
                    IgnitionButtonPassword() {
                        DisplayUnitInput duInput = DisplayUnitInput();
                        this->inititateButton = duInput.menuNext;       // Set what button to be used for enabling feature, cannot be the same as for test button feature
                        this->pwButtons[0] = duInput.indicatorLeft;     // Set button used as password keypress 1
                        this->pwButtons[1] = duInput.indicatorRight;    // Set button used as password keypress 2
                        this->pwButtons[2] = duInput.menuSelect;        // Set button used as password keypress 3
                        this->pwButtons[3] = duInput.menuNext;          // Set button used as password keypress 4
                    }
            };

    };

#endif