/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

ButtonStatusHistory buttonStatusHistory[20]; // Array storing last time a button was pressed for all buttons, used to ignore dirty signal from buttons causing double-press

class Setup {
    // Set Arduino pins according to congig
    private:
        void setRelayOutputPin(int pin, bool defaultOn) {
            if (pin > -1)
            {
                pinMode(pin, OUTPUT);
                if (defaultOn)
                    digitalWrite(pin, LOW);
                else
                    digitalWrite(pin, HIGH);
            }
        }
        void setInputPin(Input input) {
            if (input.pin > -1)
            {
                if (input.pinType == digitalPin)
                    pinMode(input.pin, INPUT_PULLUP);
                else
                    pinMode(input.pin, INPUT);
            }
        }

    public:
        void setPinMode() {
            // Output pins for relay setup
            setRelayOutputPin(MAIN_IGNITION_POSITIVE_OUTPUT_PIN, false);
            setRelayOutputPin(MAIN_IGNITION_GROUD_OUTPUT_PIN, false);
            setRelayOutputPin(START_MOTOR_OUTPUT_PIN, false);
            setRelayOutputPin(SIGNAL_HORN_OUTPUT_PIN, false);
            setRelayOutputPin(LIGHTS_PARK_OUTPUT_PIN, false);
            setRelayOutputPin(LIGHTS_LOW_BEAM_OUTPUT_PIN, false);
            setRelayOutputPin(LIGHTS_HIGH_BEAM_OUTPUT_PIN, false);
            setRelayOutputPin(LIGHTS_BRAKE_OUTPUT_PIN, false);
            setRelayOutputPin(INDICATOR_LEFT_OUTPUT_PIN, false);
            setRelayOutputPin(INDICATOR_RIGHT_OUTPUT_PIN, false);
            // Onboard led
            pinMode(ONBOARD_LED_PIN, OUTPUT);
            // Display

            // Input pins
            setInputPin(MAIN_IGNITION_SWITCH_INPUT);
            setInputPin(SIGNAL_HORN_SWITCH_INPUT);
            setInputPin(LIGHTS_LOW_HIGHT_SWITCH_INPUT);
            setInputPin(INDICATOR_LEFT_SWITCH_INPUT);
            setInputPin(INDICATOR_RIGHT_SWITCH_INPUT);
            setInputPin(LIGHTS_MAIN_SWITCH_INPUT);
            setInputPin(START_MOTOR_SWITCH_INPUT);
            setInputPin(DISPLAY_MENU_ITEM_NEXT_INPUT);
            setInputPin(DISPLAY_MENU_ITEM_SELECT_INPUT);
            setInputPin(CLUTCH_SWITCH_INPUT);
            setInputPin(BRAKE_SWITCH_INPUT);
            setInputPin(OIL_SENSOR_INPUT);
            setInputPin(NEUTRAL_SWITCH_INPUT);
            setInputPin(ENGINE_RUNNING_SENSOR_INPUT);

            //Done
            Serial.println("Pin Setup Done");
        }

        void initButtonStatusHisory() {
            for (size_t i = 0; i < 20; i++)
            {
                buttonStatusHistory[i].lastPressTimestamp = (millis() - 1000);
            }
            
        };
};

