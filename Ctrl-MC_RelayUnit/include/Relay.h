/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Relay {

  private:

    void setRelayPin(Config::PinConfig output) {
      if (output.enabeld) {
        pinMode(output.pin, OUTPUT);
        off(output);
      }
    }

    Config::PinConfig getRelayOutputFromPin(uint8_t pin) {
      Config::RelayUnitOutput output = Config::RelayUnitOutput();
      if (pin == output.Brake.pin) return output.Brake;
      else if (pin == output.CoilGround.pin) return output.CoilGround;
      else if (pin == output.Horn.pin) return output.Horn;
      else if (pin == output.LightsHigh.pin) return output.LightsHigh;
      else if (pin == output.LightsLow.pin) return output.LightsLow;
      else if (pin == output.LightsPark.pin) return output.LightsPark;
      else if (pin == output.MainPower.pin) return output.MainPower;
      else if (pin == output.Starter.pin) return output.Starter;
      else if (pin == output.TurnSignalLeft.pin) return output.TurnSignalLeft;
      else if (pin == output.TurnSignalRight.pin) return output.TurnSignalRight;
      else {
        Config::PinConfig invalid = { 0, false };
        return invalid;  
      };
    }
  
  public:

    enum RelayStatus { relayOn, relayOff, relayInactive };

    void init() {
      // Set Output pins for relays
      Config::RelayUnitOutput output = Config::RelayUnitOutput();
      setRelayPin(output.Brake);
      setRelayPin(output.CoilGround);
      setRelayPin(output.Horn);
      setRelayPin(output.LightsHigh);
      setRelayPin(output.LightsLow);
      setRelayPin(output.LightsPark);
      setRelayPin(output.MainPower);
      setRelayPin(output.Starter);
      setRelayPin(output.TurnSignalLeft);
      setRelayPin(output.TurnSignalRight);
    }

    void on(Config::PinConfig output) {
        if (output.enabeld)
          digitalWrite(output.pin, LOW);
    }
    
    void off(Config::PinConfig output) {
        if (output.enabeld)
          digitalWrite(output.pin, HIGH);
    }

    void set(uint8_t pin, RelayStatus relayStatus) {
        Config::PinConfig output = getRelayOutputFromPin(pin);
        if (output.enabeld) {
          if (relayStatus == relayOn)
            on(output);
          else if (relayStatus == relayOff)
            off(output);
        }
    }

    RelayStatus get(Config::PinConfig output) {
      if (output.enabeld) {
        if (digitalRead(output.pin == LOW))
          return RelayStatus::relayOn;
        else
          return RelayStatus::relayOff;
      }
      else {
        return RelayStatus::relayInactive;
      }
    }

};

