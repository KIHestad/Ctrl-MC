/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Init {

    public:
        
        void run() {
            // Init onboard led
            Config::DisplayUnitOutput duOutput = Config::DisplayUnitOutput();
            onBoardLed = OnBoardLed();
            onBoardLed.init(duOutput.onBoardLed);
            // OLED display speed
            Wire.setClock(400000);
            // Serial comm
            Serial.begin(Config::serialCommSpeed);
            serialCommunication = SerialCommunication();
            // Set initial bike status
            bikeStatus = BikeStatus();
            // Set buttons
            Config::DisplayUnitInput duInput = Config::DisplayUnitInput();
            btnClutch = Button();
            btnClutch.init(duInput.clutch);
            
            btnIndicatorLeft = Button();
            btnIndicatorLeft.init(duInput.indicatorLeft);
            
            btnIndicatorRight = Button();
            btnIndicatorRight.init(duInput.indicatorRight);

            btnLightsHiLo = Button();
            btnLightsHiLo.init(duInput.lightsHiLo);

            btnHorn = Button();
            btnHorn.init(duInput.horn);

            btnMenuMain = Button();
            btnMenuMain.init(duInput.menuMain);
            
            btnMenuStartStop = Button();
            btnMenuStartStop.init(duInput.menuStartStop);

            btnBrakeFront = Button();
            btnBrakeFront.init(duInput.brakeFront);
            
            // Set display properties
            displayHelper = DisplayHelper();
            displayHelper.init();

            // Initiate features
            testButtons = TestButtons();
            ignitionButtonPassword = IgnitionButtonPassword();
            action = Action();
            buttonEvent = ButtonEvent();

            // Clear searial comm buffer
            serialCommunication.clearBuffer();
            
            // TODO: Read bike status from relay unit
        }

};