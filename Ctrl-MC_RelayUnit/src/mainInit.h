/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

class MainInit {
    // Set Arduino pins according to config
    private:
        void setRelayOutputPin(uint8_t pin, bool defaultOn) {
            if (pin > -1)
            {
                pinMode(pin, OUTPUT);
                if (defaultOn)
                    digitalWrite(pin, LOW);
                else
                    digitalWrite(pin, HIGH);
            }
        }

    public:
        void setPinMode() {
            // Output pins for relay setup
            setRelayOutputPin(OUTPUT_PIN_MAIN_IGNITION, false);
            setRelayOutputPin(OUTPUT_PIN_START_MOTOR, false);
            setRelayOutputPin(OUTPUT_PIN_SIGNAL_HORN, false);
            setRelayOutputPin(OUTPUT_PIN_LIGHTS_PARK, false);
            setRelayOutputPin(OUTPUT_PIN_LIGHTS_LOW_BEAM, false);
            setRelayOutputPin(OUTPUT_PIN_LIGHTS_HIGH_BEAM, false);
            setRelayOutputPin(OUTPUT_PIN_LIGHTS_BRAKE, false);
            setRelayOutputPin(OUTPUT_PIN_INDICATOR_LEFT, false);
            setRelayOutputPin(OUTPUT_PIN_INDICATOR_RIGHT, false);
            setRelayOutputPin(OUTPUT_PIN_AUX, false);
            // Onboard led
            pinMode(ONBOARD_LED_PIN, OUTPUT);
        }

};