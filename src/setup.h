/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class PinSetup {
    // Set Arduino pins according to congig
    private:
        void setRelayPin(int pin, bool defaultOn) {
            if (pin > -1)
            {
                pinMode(pin, OUTPUT);
                if (defaultOn)
                    digitalWrite(pin, LOW);
                else
                    digitalWrite(pin, HIGH);
            }
        }
        void setInputPin(int pin[], int type) {
            if (pin[0] > -1)
            {
                pinMode(pin[0], type);
            }
        }

    public:
        void setPinMode() {
            // Output pins for relay setup
            setRelayPin(MAIN_IGNITION_POSITIVE_OUTPUT_PIN, false);
            setRelayPin(MAIN_IGNITION_GROUD_OUTPUT_PIN, false);
            setRelayPin(START_MOTOR_OUTPUT_PIN, false);
            setRelayPin(LIGHTS_PARK_OUTPUT_PIN, false);
            setRelayPin(LIGHTS_LOW_BEAM_OUTPUT_PIN, false);
            setRelayPin(LIGHTS_HIGH_BEAM_OUTPUT_PIN, false);
            setRelayPin(LIGHTS_BRAKE_OUTPUT_PIN, false);
            setRelayPin(SIGNAL_HORN_OUTPUT_PIN, false);
            setRelayPin(INDICATOR_LEFT_OUTPUT_PIN, false);
            setRelayPin(INDICATOR_RIGHT_OUTPUT_PIN, false);
            setRelayPin(AUX_OUTPUT_PIN, false);
            // Onboard led
            pinMode(ONBOARD_LED_PIN, OUTPUT);
            // Input pins for switches setup
            setInputPin(MAIN_IGNITION_SWITCH_INPUT_PIN, INPUT_PULLUP);
            setInputPin(START_MOTOR_SWITCH_INPUT_PIN, INPUT_PULLUP);
            setInputPin(LIGHTS_MAIN_SWITCH_INPUT_PIN, INPUT_PULLUP);
            setInputPin(LIGHTS_LOW_HIGHT_SWITCH_INPUT_PIN, INPUT_PULLUP);
            setInputPin(LIGHTS_BRAKE_SWITCH_INPUT_PIN, INPUT_PULLUP);
            // Output pin for onboard led
        }
};

