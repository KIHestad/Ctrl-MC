/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#ifndef onBoardLedDef
    #define onBoardLedDef
    #if (ARDUINO >= 100)
        #include "Arduino.h"
    #endif

    class OnBoardLed {

        public:

            // Properties
            struct Settings {

                public:
                    bool enabled; // Set enabled or disabled
                    uint8_t pin; // Pin on Arduino for the feature
                    uint8_t onValue; // When used: set HIGH or LOW to determin what sets the onboard led on or off
                    uint8_t offValue; // Ex: for Arduino Uno/Nano led in on using HIGH, but for NodeMCU led is on using LOW
            };

            // Constructor
            OnBoardLed();

            // Methods
            void init(Settings settings);
            void blink(size_t blinkCount, unsigned long delayInMilliseconds);
            void set(int value);
            void on();
            void off();

        private:

            Settings settings;

    };

#endif