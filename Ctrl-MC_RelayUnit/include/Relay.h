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
      if (pin == ruOutput.brake.pin) return ruOutput.brake;
      else if (pin == ruOutput.coilGround.pin) return ruOutput.coilGround;
      else if (pin == ruOutput.horn.pin) return ruOutput.horn;
      else if (pin == ruOutput.lightsHigh.pin) return ruOutput.lightsHigh;
      else if (pin == ruOutput.lightsLow.pin) return ruOutput.lightsLow;
      else if (pin == ruOutput.lightsPark.pin) return ruOutput.lightsPark;
      else if (pin == ruOutput.mainPower.pin) return ruOutput.mainPower;
      else if (pin == ruOutput.starterMotor.pin) return ruOutput.starterMotor;
      else if (pin == ruOutput.turnSignalLeft.pin) return ruOutput.turnSignalLeft;
      else if (pin == ruOutput.turnSignalRight.pin) return ruOutput.turnSignalRight;
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
      setRelayPin(ruOutput.brake);
      setRelayPin(ruOutput.coilGround);
      setRelayPin(ruOutput.horn);
      setRelayPin(ruOutput.lightsHigh);
      setRelayPin(ruOutput.lightsLow);
      setRelayPin(ruOutput.lightsPark);
      setRelayPin(ruOutput.mainPower);
      setRelayPin(ruOutput.starterMotor);
      setRelayPin(ruOutput.turnSignalLeft);
      setRelayPin(ruOutput.turnSignalRight);
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

