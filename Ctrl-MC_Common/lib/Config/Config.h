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
            static const unsigned long serialCommSpeed = 9600; // Baud rate for serial comm for both units
            static const unsigned long handshakeInterval = 15000; // Number of ms between each handshake triggered from display unit
            static const bool debugMode = false; // Run system in debug mode, ignore handshare errors

            // *************************************************
            //   Relay Unit Configuration
            // *************************************************
            
            // Outputs - relays / onboard led
            class RelayUnitOutput {
                public:
                    // Enable/disable relay unit features, set arduino pin connected to each relay
                    const Feature turnSignalLeft =  { true, 5 };
                    const Feature turnSignalRight = { true, 18 };
                    const Feature mainPower =       { true, 13 };
                    const Feature coilGround =      { true, 12 };
                    const Feature starterMotor =    { true, 14 };
                    const Feature horn =            { true, 27 };
                    const Feature lightPark =       { true, 26 };
                    const Feature lightLow =        { true, 25 };
                    const Feature lightHigh =       { true, 33 };
                    const Feature lightBrake =      { true, 32 };
                    // Onboard led settings: enabled/disabled, pinNumber, value to turn led on, value to turn led off
                    // If not to be used, set enabled to false, the remaining vars are ignored in this case, ex: { false, 0, 0, 0 }
                    const OnBoardLed::Settings onBoardLed = { false, 2, HIGH, LOW };
            };
        
            // Inputs - swithes and sensors located near relay unit
            class RelayUnitInput {
                public:
                    static const int tempSensor =       15; // set to -1 to disable, pin A0 = 14 on Arduino Nano
                    static const int batteryVoltage =   35; // set to -1 to disable, pin used for measure battery voltage
                    static const int oilSensor =        -1; // set to -1 to disable, not implemented yet
                    static const int neutralSwitch =    -1; // set to -1 to disable, not implemented yet
                    static const int brakeRearSwitch =  -1; // set to -1 to disable, not implemented yet
                    static const int engineRpm =        -1; // set to -1 to disable, not implemented yet - experimental
            };
           
            // *************************************************
            //   Display Unit Configuration
            // *************************************************

            // Outputs - onboard led
            class DisplayUnitOutput {
                public:
                    // Onboard led settings: enabled/disabled, pinNumber, value to turn led on, value to turn led off
                    // If not to be used, set enabled to false, the remaining vars are ignored in this case, ex: { false, 0, 0, 0 }
                    const OnBoardLed::Settings onBoardLed = { false, 2, HIGH, LOW };
            };

            // Inputs - buttons on handlebar
            class DisplayUnitInput {
                public:
                    // Enable/disable handlebar buttons, set arduino pin connected to each button
                    const Feature clutch =          { true, 27 };
                    const Feature indicatorLeft =   { true, 14 };
                    const Feature indicatorRight =  { true, 26 };
                    const Feature lightsHiLo =      { true, 13 };
                    const Feature horn =            { true, 12 };
                    const Feature menuMain =        { true, 33 };
                    const Feature menuStartStop =   { true, 25 };
                    const Feature brakeFront =      { true, 32 };
            };

            // Display Menu
            struct DisplayMenuItemInfo {
                uint8_t id; // Identifier used by code to know what to do
                String displayName; // Name of menu item to show on display
            };
            class DisplaySettings {
                public:
                    static const int switchCapVCC = 0x02;
                    static const uint8_t sda = 21;
                    static const uint8_t scl = 22;
                    static const uint8_t screenAddress = 0x3C;                      // See datasheet for Address; normally 0x3D for 128x64, 0x3C for 128x32        
                    static const int8_t  oledReset = -1;                            // Reset pin # (or -1 if sharing Arduino reset pin)
                    static const uint8_t screenWidth = 128;                         // OLED display width, in pixels
                    static const uint8_t screenHeight = 64;                         // OLED display height, in pixels
                    static const uint8_t textSize = 1;                              // Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc these numbers include one extra pixel for space
                    static const uint8_t textCharWidth = 6 * textSize;              // Width of text INCLUDING ONE PIXEL FOR SEPARATION BETWEEN CHARS written to display, adjusted according to text size
                    static const uint8_t textCharHeight = 7 * textSize;             // Height of text EXCLUDING PIXEL FOR SEPARATION BETWEEB ROWS written to display, adjusted according to text size
                    static const uint8_t textLargeSize = 2;                         // Larger text
                    static const uint8_t textLargeCharWidth = 6 * textLargeSize;    // Width of text INCLUDING ONE PIXEL FOR SEPARATION BETWEEN CHARS written to display, adjusted according to text size
                    static const uint8_t textLargeCharHeight = 7 * textLargeSize;   // Height of text EXCLUDING PIXEL FOR SEPARATION BETWEEB ROWS written to display, adjusted according to text size
                    static const bool tempShowFarenheit = false;                    // Default is Celsius, set true to show as farenheit
                    static const unsigned long timeoutDelay = 11000;                // Default time for delay before starting progressbar to enable cancel current operation
                    static const unsigned long timeoutProgressbarDuration = 4000;   // Default time for progressbar to be running before cancelling current operation
            };

            class DisplayMenuItem {
                public:
                    // List of available main menu items, number must be sorted from 1 to n and represent sort order (can be changed), numbers above menuMainItemsCount will not be displayed
                    static const uint8_t menuMainItemsCount = 5;                                   // Set number of main menu items to be shown on display
                    const DisplayMenuItemInfo ignition =        { 1, "IGNITION ON" };       // Show ignition status, possible to turn off
                    const DisplayMenuItemInfo lights =          { 2, "LIGHTS" };            // Control Ligths - OFF / PARK / ON
                    const DisplayMenuItemInfo stopWatch =       { 3, "STOPWATCH" };         // Built in stopwatch, started when ignition is turned on
                    const DisplayMenuItemInfo tempSystem =      { 4, "SYSTEM TEMP" };       // Read system temp from relay unit
                    const DisplayMenuItemInfo batteryVoltage =  { 5, "BATTERY VOLTAGE" };   // Read battery voltage from relay unit
                    // List of start / stop engine menu items, number must not be changed
                    static const bool enableStartStop = true;
                    const DisplayMenuItemInfo engineStart =  { 100, "START ENGINE" }; 
                    const DisplayMenuItemInfo engineStop =  { 101, "STOP ENGINE" }; 
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
                        this->inititateButton = duInput.menuStartStop;     // Set what button to be used for enabling feature, cannot be the same as for ignition button password feature
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
                        this->inititateButton = duInput.menuMain;       // Set what button to be used for enabling feature, cannot be the same as for test button feature
                        this->pwButtons[0] = duInput.indicatorLeft;     // Set button used as password keypress 1
                        this->pwButtons[1] = duInput.indicatorRight;    // Set button used as password keypress 2
                        this->pwButtons[2] = duInput.lightsHiLo;     // Set button used as password keypress 3
                        this->pwButtons[3] = duInput.horn;          // Set button used as password keypress 4
                    }
            };

            // Indicators
            class Indicator {
                public: 
                    static const unsigned long blinkSpeed = 700;        // Milliseconds for each blink, should be from 500 (fast) to 1500 (slow)
            };

            // Headlight
            class Headlight {
                public:
                    static const bool hiWithLow = true;                 // Set true to keep Low Beam on togheter with High Beam, set false to turn off Low Beam when High Beam is selected
            };

            // Battery Voltage divider multipler parameters
            class BatteryVoltage {
                public:
                    static constexpr double resistor1 = 990; // Resistor in ohm between +12V and input pin
                    static constexpr double resistor2 = 241; // Resistor in ohm between GND and input pin 
                    static constexpr double adcFactor = 1.56/1775; // Actual voltage mcu reading / analog read output
            };

    };

#endif