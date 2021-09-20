class Setup {
    private:
        // Set Arduino pins according to congig
        void setInputPin(Input input) {
            if (input.enabled)
                pinMode(input.pin, INPUT_PULLUP);
        }

    public:
        
        void init() {
            setPinMode();
            bikeStatus.init();
            controlDisplay.init();
        }
        
        void setPinMode() {
            // Input pins
            setInputPin(INPUT_CLUTCH);
            setInputPin(INPUT_HORN);
            setInputPin(INPUT_HILO);
            setInputPin(INPUT_IND_LEFT);
            setInputPin(INPUT_IND_RIGHT);
            setInputPin(INPUT_DISP_SELECT);
            setInputPin(INPUT_DISP_NEXT);
            setInputPin(INPUT_START_STOP);
            setInputPin(INPUT_BRAKE_FRONT);
            // Onboard LED pin
            pinMode(ONBOARD_LED_PIN, OUTPUT);
            digitalWrite(ONBOARD_LED_PIN, LOW);
        }

};