/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Relay {

  private:

    void setRelayPin(Config::Feature feature) {
      if (feature.enabled) {
        digitalWrite(feature.pin, HIGH); // Make sure it is set to OFF before pin is set to output mode
        pinMode(feature.pin, OUTPUT);
        off(feature);
      }
    }

    Config::Feature getRelayOutputFeatureFromPin(uint8_t pin) {
      Config::RelayUnitOutput ruOutput = Config::RelayUnitOutput();
      if (pin == ruOutput.mainPower.pin) return ruOutput.mainPower;
      else if (pin == ruOutput.coilGround.pin) return ruOutput.coilGround;
      else if (pin == ruOutput.starterMotor.pin) return ruOutput.starterMotor;
      else if (pin == ruOutput.horn.pin) return ruOutput.horn;
      else if (pin == ruOutput.turnSignalLeft.pin) return ruOutput.turnSignalLeft;
      else if (pin == ruOutput.turnSignalRight.pin) return ruOutput.turnSignalRight;
      else if (pin == ruOutput.lightHigh.pin) return ruOutput.lightHigh;
      else if (pin == ruOutput.lightLow.pin) return ruOutput.lightLow;
      else if (pin == ruOutput.lightPark.pin) return ruOutput.lightPark;
      else if (pin == ruOutput.lightBrake.pin) return ruOutput.lightBrake;
      else {
        Config::Feature invalid = { 0, false };
        return invalid;  
      };
    }
  
  public:

    enum RelayStatus { relayOn, relayOff, relayInactive };

    void init() {
      // Set ruOutput pins for relays
      Config::RelayUnitOutput ruOutput = Config::RelayUnitOutput();
      setRelayPin(ruOutput.mainPower);
      setRelayPin(ruOutput.coilGround);
      setRelayPin(ruOutput.starterMotor);
      setRelayPin(ruOutput.horn);
      setRelayPin(ruOutput.turnSignalLeft);
      setRelayPin(ruOutput.turnSignalRight);
      setRelayPin(ruOutput.lightPark);
      setRelayPin(ruOutput.lightLow);
      setRelayPin(ruOutput.lightHigh);
      setRelayPin(ruOutput.lightBrake);
    }

    void on(Config::Feature feature) {
        if (feature.enabled)
          digitalWrite(feature.pin, LOW);
    }
    
    void off(Config::Feature feature) {
        if (feature.enabled)
          digitalWrite(feature.pin, HIGH);
    }

    void set(uint8_t pin, RelayStatus relayStatus) {
        Config::Feature feature = getRelayOutputFeatureFromPin(pin);
        if (feature.enabled) {
          if (relayStatus == relayOn)
            on(feature);
          else if (relayStatus == relayOff)
            off(feature);
        }
    }

    RelayStatus get(Config::Feature feature) {
      if (feature.enabled) {
        if (digitalRead(feature.pin == LOW))
          return RelayStatus::relayOn;
        else
          return RelayStatus::relayOff;
      }
      else {
        return RelayStatus::relayInactive;
      }
    }

};

