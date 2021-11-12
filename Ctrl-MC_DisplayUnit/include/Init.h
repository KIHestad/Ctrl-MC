/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Init {
    private:
        // Set Arduino pins according to congig
        void setInputPin(Input input) {
            if (input.enabled) {
                pinMode(input.pin, INPUT_PULLUP);
            }
        }

        void setInputPins() {
            // Input pins
            setInputPin(INPUT_CLUTCH);
            setInputPin(INPUT_HILO);
            setInputPin(INPUT_IND_LEFT);
            setInputPin(INPUT_IND_RIGHT);
            setInputPin(INPUT_MENU_SELECT);
            setInputPin(INPUT_MENU_NEXT);
            setInputPin(INPUT_START_STOP);
            setInputPin(INPUT_BRAKE_FRONT);
        }

    public:
        
        void run() {
            // Set input pins
            setInputPins();
            // Set initial bike status
            bikeStatus = BikeStatus();
            // Set buttons
            Config::DisplayUnitInput duInput = Config::DisplayUnitInput();
            btnClutch.init(duInput.clutch);
            btnIndicatorLeft.init(duInput.indicatorLeft);
            btnIndicatorRight.init(duInput.indicatorRight);
            btnLightsHiLo.init(duInput.lightsHiLo);
            btnStartStop.init(duInput.startStop);
            btnMenuSelect.init(duInput.menuSelect);
            btnMenuNext.init(duInput.menuNext);
            btnBrakeFront.init(duInput.brakeFront);
            // Set display properties
            controlDisplay = ControlDisplay();
            controlDisplay.init();
            // Initiate features
            testButtons = TestButtons();
            ignitionButtonPassword = IgnitionButtonPassword();
            action = Action();
        }

};