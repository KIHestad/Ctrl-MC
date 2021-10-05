/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Relay {

  public:

    enum RelayStatus { relayOn, relayOff, relayInactive };

    void init() {
      // Set Output pins for relays
      for (uint8_t relayNumber = 0; relayNumber < OUTPUT_PIN_RELAY_COUNT; relayNumber++)
      {
          pinMode(OUTPUT_PIN_RELAY[relayNumber], OUTPUT);
          off(relayNumber);
      }
    }

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

