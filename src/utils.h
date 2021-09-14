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

        void on() {
            digitalWrite(ONBOARD_LED_PIN, HIGH);
        }

        void off() {
            digitalWrite(ONBOARD_LED_PIN, LOW);
        }
};

class Button {

    public:

        ButtonStatusRead read(int inputPin[]) {
            // Prepare return model
            int pin = inputPin[0];
            ButtonStatusRead buttonStatus = ButtonStatusRead();
            buttonStatus.timeStamp = millis();
            // Check if enabled
            if (pin == -1)
                return buttonStatus;
            // Check if analog or digiral read
            if (inputPin[1] == digitalPin) {
                int digitalReadValue = digitalRead(pin);
                buttonStatus.pressed = (digitalReadValue == 0) ? true : false;
                Serial.print("DIGITAL READ: ");
                Serial.print(digitalReadValue);
            }
            else if (inputPin[1] == analogPin) {
                int analogReadValue = analogRead(pin);
                Serial.print("ANALOG READ: ");
                Serial.print(analogReadValue);
                buttonStatus.pressed = (analogReadValue >= inputPin[2] && analogReadValue <= inputPin[3]) ? true : false;
            }
            if (buttonStatus.pressed)
                Serial.print(" -> DETECTED BUTTON PRESSED");
            else
                Serial.print(" -> DETECTED BUTTON RELEASED");
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
