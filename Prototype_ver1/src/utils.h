/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class OnBoardLed {
    
    public:
        
        void blink(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, HIGH);
                delay(100);
                digitalWrite(ONBOARD_LED_PIN, LOW);
                delay(100);
            }
        }

        void blinkSlow(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, HIGH);
                delay(600);
                digitalWrite(ONBOARD_LED_PIN, LOW);
                delay(600);
            }
        }
        void on() {
            digitalWrite(ONBOARD_LED_PIN, HIGH);
        }

        void off() {
            digitalWrite(ONBOARD_LED_PIN, LOW);
        }
};

class Button {

    public:

        ButtonStatus read(Input input) {
            // Prepare return model
            ButtonStatus buttonStatus = ButtonStatus();
            buttonStatus.input = input;
            if (!input.enabled)
                return buttonStatus;
            // Check timeout for any button, with this code any input are read each 250ms and returned same value within this time period
            long timeStampNow = millis();
            if (timeStampNow - buttonStatusHistory[input.pin].lastPressTimestamp < 250)
            {
                buttonStatus.pressed = buttonStatusHistory[input.pin].pressed;
                buttonStatus.value = buttonStatusHistory[input.pin].value;
                return buttonStatus;
            }
            //Timeout not triggered
            buttonStatusHistory[input.pin].lastPressTimestamp = timeStampNow;
            // Check if analog or digiral read
            if (input.pinType == digitalPin) {
                buttonStatus.value = digitalRead(input.pin);
                buttonStatus.pressed = (buttonStatus.value == 0) ? true : false;
            }
            else if (input.pinType == analogPin) {
                buttonStatus.value = analogRead(input.pin);
                int minValue = input.expectedValue - ANALOG_PIN_VALUE_VARIATION;
                int maxValue = input.expectedValue + ANALOG_PIN_VALUE_VARIATION;
                buttonStatus.pressed = (buttonStatus.value >= minValue && buttonStatus.value <= maxValue) ? true : false;
            }
            // Add to history
            buttonStatusHistory[input.pin].value = buttonStatus.value;
            buttonStatusHistory[input.pin].pressed = buttonStatus.pressed;

            // TODO: debugging, show pressed button
            // if (buttonStatus.pressed)
            //     Serial.println(input.displayName);
            return buttonStatus;
        };

};

class Relay {

  public:

    void on(int pin) {
        if (pin > -1)
            digitalWrite(pin, LOW);
    }
    
    void off(int pin) {
        if (pin > -1)
            digitalWrite(pin, HIGH);
    }

};
