/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

class PinSetup {
    // Define what arduino pins are used
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
        void setInputPin(int pin, int type) {
            if (pin > -1)
            {
                pinMode(pin, type);
            }
        }

    public:
        void setPinMode() {
            Config config = Config();
            // Output pins for relay setup
            setRelayPin(config.outMainIgnintionPositive, false);
            setRelayPin(config.outMainIgningtonNegative, false);
            setRelayPin(config.outStartMotor, false);
            setRelayPin(config.outHorn, false);
            setRelayPin(config.outIndicatorLeft, false);
            setRelayPin(config.outIndicatorRight, false);
            setRelayPin(config.outLightsPark, false);
            setRelayPin(config.outLightsLow, false);
            setRelayPin(config.outLightsHigh, false);
            setRelayPin(config.outLightsBrake, false);
            // Onboard led
            pinMode(config.onBoardLed, OUTPUT);
            // Input pins for switches setup
            setInputPin(config.inHandlebarButtonArray, INPUT_PULLUP);
            setInputPin(config.inClutch, INPUT_PULLUP);
            setInputPin(config.inBreakLeverAndPedal, INPUT_PULLUP);
            setInputPin(config.inOilSensor, INPUT_PULLUP);
            setInputPin(config.inNeutralSensor, INPUT_PULLUP);
            // Output pin for onboard led
        }
};