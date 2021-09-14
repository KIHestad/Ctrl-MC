/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class OnBoardLed {
    
    private:
        
        Config config = Config();
    
    public:
        
        void blink(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(config.onBoardLed, HIGH);
                delay(100);
                digitalWrite(config.onBoardLed, LOW);
                delay(100);
            }
        }

        void on() {
            digitalWrite(config.onBoardLed, HIGH);
        }

        void off() {
            digitalWrite(config.onBoardLed, LOW);
        }
};

class ButtonActon {

    public:

        ButtonStatusRead readDigital(int pin) {
            int digitalReadValue = digitalRead(pin);
            ButtonStatusRead newButtonStatus = ButtonStatusRead();
            newButtonStatus.pressed = (digitalReadValue == 0) ? true : false;
            newButtonStatus.timeStamp = millis();
            return newButtonStatus;
        };

        ButtonStatusRead readAnalog(int pin, int valueInterval[]) {
            int analogReadValue = analogRead(pin);
            Serial.print("ANALOG READ: ");
            Serial.println(analogReadValue);
            ButtonStatusRead newButtonStatus = ButtonStatusRead();
            newButtonStatus.pressed = (analogReadValue >= valueInterval[0] && analogReadValue <= valueInterval[1]) ? true : false;
            newButtonStatus.timeStamp = millis();
            return newButtonStatus;
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
