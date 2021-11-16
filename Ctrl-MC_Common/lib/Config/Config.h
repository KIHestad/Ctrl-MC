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
            //   Common settings, normally not to be changed
            // *************************************************
            struct Feature {
                bool enabled; // Used to set feature enabled or disabled
                uint8_t pin; // Pin on Arduino for the feature
            };
            const unsigned long serialCommSpeed = 9600; // Baud rate for serial comm for both units
            const unsigned long handshakeInterval = 15000; // Number of ms between each handshake triggered from display unit

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
                    const Feature menuSelect =      { true, 25 }; // 25 is buggy, because of DAC1 ??
                    const Feature menuNext =        { true, 33 };
                    const Feature brakeFront =      { true, 32 };
            };

            // Display Menu
            struct DisplayMenuItemInfo {
                uint8_t id; // Identifier used by code to know what to do
                String displayName; // Name of menu item to show on display
            };
            class DisplaySettings {
                public:
                    static const uint8_t ScreenAddress = 0x3C;             // See datasheet for Address; normally 0x3D for 128x64, 0x3C for 128x32        
                    static const int8_t  OLEDreset = -1;                    // Reset pin # (or -1 if sharing Arduino reset pin)
                    static const uint8_t ScreenWidth = 128;                // OLED display width, in pixels
                    static const uint8_t ScreenHeight = 64;                // OLED display height, in pixels
                    static const uint8_t TextSize = 1;                     // Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc these numbers include one extra pixel for space
                    static const uint8_t TextCharWidth = 6 * TextSize;     // Width of text INCLUDING ONE PIXEL FOR SEPARATION BETWEEN CHARS written to display, adjusted according to text size
                    static const uint8_t TextCharHeight = 7 * TextSize;    // Height of text EXCLUDING PIXEL FOR SEPARATION BETWEEB ROWS written to display, adjusted according to text size
            };
            class DisplayMenuSettings {
                public:
                    // Display settings
                    static const unsigned long ShutdownWait = 6000; // Number of milliseconds a menu item is shown before automatically shut down and go back to status screen
                    static const unsigned long StatusPageProgressbarDuration = 4000; // Delay time in ms for progressbar to be shown when initiated to switch over to show status page from another page
            };
            class DisplayMenuItem {
                public:
                    // List of available menu items, do not remove any or change ID, name can be modified / translated
                    const DisplayMenuItemInfo ignition =    { 1, "IGNITION" }; // Show ignition status, possible to turn off
                    const DisplayMenuItemInfo stopWatch =   { 2, "STOPWATCH" }; // Built in timer
                    const DisplayMenuItemInfo tempSystem =  { 4, "SYSTEM TEMP" }; // Read from relay unit
                    const DisplayMenuItemInfo lights =      { 5, "LIGHTS" }; // Control Ligths - OFF / PARK / ON
            };
            class DisplayMenuItemShow {
                public:
                    // Menu items to be shown on display
                    int count = 4;                                      // Set number of menu items to be shown on display
                    DisplayMenuItemInfo item[4];                        // Display items array, set same length as count set above
                    
                    DisplayMenuItemShow() {
                        DisplayMenuItem dmi = DisplayMenuItem();
                        this->item[0] = dmi.lights;                     // Set menu item to be shown
                        this->item[1] = dmi.ignition;                   // Set menu item to be shown
                        this->item[2] = dmi.stopWatch;                  // Set menu item to be shown
                        this->item[3] = dmi.tempSystem;                 // Set menu item to be shown
                    }
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

            // Indicators
            class Indicator {
                public: 
                    static const unsigned long blinkSpeed = 700;               // Milliseconds for each blink, should be from 500 (fast) to 1500 (slow)
            };

    };

#endif