class OnBoardLed {
    
    public:
        
        void init() {
            // Onboard LED pin
            pinMode(ONBOARD_LED_PIN, OUTPUT);
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
        }
        
        void blink(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
                delay(10);
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
                delay(10);
            }
        }

        void blinkSlow(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
                delay(250);
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
                delay(250);
            }
        }
        void on() {
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
        }

        void off() {
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
        }
};