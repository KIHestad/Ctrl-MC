
/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/
bool readInput(Input input) {
    if (!input.enabled)
        return false;
    if (input.pinType == pinDigital)
        return (digitalRead(input.pin) == 0);
    else {
        int val = analogRead(input.pin);
        return (val >= input.analogValueExpected - INPUT_ANALOG_DEVIATION_ACCEPTED && val <= input.analogValueExpected + INPUT_ANALOG_DEVIATION_ACCEPTED);
    }
}

uint8_t readInputValue(Input input) {
    if (!input.enabled)
        return LOW;
    if (input.pinType == pinDigital)
        return digitalRead(input.pin);
    else {
        return analogRead(input.pin);
    }
}

class OnBoardLed {
    
    public:
        
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