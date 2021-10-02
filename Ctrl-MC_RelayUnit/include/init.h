/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Init {
    
    public:
        void run() {
    
            // Output pins for relays
            Relay relay = Relay();
            for (uint8_t relayNumber = 0; relayNumber < OUTPUT_PIN_RELAY_COUNT; relayNumber++)
            {
                pinMode(OUTPUT_PIN_RELAY[relayNumber], OUTPUT);
                relay.off(relayNumber);
            }
    
            // Onboard LED pin
            pinMode(ONBOARD_LED_PIN, OUTPUT);
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
            
            // Input pins
        }

};