
/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/
bool readInput(Input input) {
    if (input.enabled)
        return (digitalRead(input.pin) == INPUT_PRESSED_READ_VALUE);
    else
        return false;
}

class OnBoardLed {
    
    public:
        
        void blink(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
                delay(100);
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
                delay(100);
            }
        }

        void blinkSlow(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
                delay(500);
                digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
                delay(500);
            }
        }
        void on() {
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_ON);
        }

        void off() {
            digitalWrite(ONBOARD_LED_PIN, ONBOARD_LED_OFF);
        }
};