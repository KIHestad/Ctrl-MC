/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Relay {

  public:

    void on(int realyNumber) {
        digitalWrite(OUTPUT_PIN_RELAY[realyNumber], LOW);
    }
    
    void off(int realyNumber) {
        digitalWrite(OUTPUT_PIN_RELAY[realyNumber], HIGH);
    }

    void set(int realyNumber, RelayStatus relayStatus) {
        if (relayStatus == relayOn)
          on(realyNumber);
        else if (relayStatus == relayOff)
          off(realyNumber);
    }

    RelayStatus getStatus(int realyNumber) {
      if (digitalRead(OUTPUT_PIN_RELAY[realyNumber]) == LOW)
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