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
            buttonStatus.timeStamp = millis();
            buttonStatus.input = input;
            buttonStatus.enabled = (input.pin > -1);
            // Check if enabled
            if (!buttonStatus.enabled)
                return buttonStatus;
            // Check if analog or digiral read
            if (input.pinType == digitalPin) {
                buttonStatus.value = digitalRead(input.pin);
                buttonStatus.pressed = (buttonStatus.value == 0) ? true : false;
                //Serial.print("DIGITAL READ: ");
                //Serial.print(digitalReadValue);
            }
            else if (input.pinType == analogPin) {
                buttonStatus.value = analogRead(input.pin);
                //Serial.print("ANALOG READ: ");
                //Serial.print(analogReadValue);
                int minValue = input.expectedValue - ANALOG_PIN_VALUE_VARIATION;
                int maxValue = input.expectedValue + ANALOG_PIN_VALUE_VARIATION;
                buttonStatus.pressed = (buttonStatus.value >= minValue && buttonStatus.value <= maxValue) ? true : false;
            }
            //if (buttonStatus.pressed)
                //Serial.print(" -> DETECTED BUTTON PRESSED");
            //else
                //Serial.print(" -> DETECTED BUTTON RELEASED");
            return buttonStatus;
        };

};

class Relay {

  public:

    void on(int pin) {
        digitalWrite(pin, LOW);
    }
    
    void off(int pin) {
        digitalWrite(pin, HIGH);
    }

};
