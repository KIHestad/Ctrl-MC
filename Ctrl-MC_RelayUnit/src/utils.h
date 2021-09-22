/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

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

    void set(int pin, RelayStatus relayStatus) {
        if (relayStatus == relayOn)
          on(pin);
        else if (relayStatus == relayOff)
          off(pin);
    }

    RelayStatus getStatus(int pin) {
      if (pin == -1)
        return relayInactive;
      else if (digitalRead(pin) == LOW)
        return relayOn;
      else
        return relayOff;
    }

};


class OnBoardLed {
    
    public:
        
        void blink(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, HIGH);
                delay(10);
                digitalWrite(ONBOARD_LED_PIN, LOW);
                delay(10);
            }
        }

        void blinkSlow(size_t count) {
            for (size_t i = 0; i < count; i++)
            {
                digitalWrite(ONBOARD_LED_PIN, HIGH);
                delay(250);
                digitalWrite(ONBOARD_LED_PIN, LOW);
                delay(250);
            }
        }
        void on() {
            digitalWrite(ONBOARD_LED_PIN, HIGH);
        }

        void off() {
            digitalWrite(ONBOARD_LED_PIN, LOW);
        }
};