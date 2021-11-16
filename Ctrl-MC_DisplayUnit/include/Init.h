/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Init {

    public:
        
        void run() {
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

            btnStartStop = Button();
            btnStartStop.init(duInput.startStop);

            btnMenuSelect = Button();
            btnMenuSelect.init(duInput.menuSelect);

            btnMenuNext = Button();
            btnMenuNext.init(duInput.menuNext);
            
            btnBrakeFront = Button();
            btnBrakeFront.init(duInput.brakeFront);
            
            // Set display properties
            displayHelper = DisplayHelper();
            displayHelper.init();
            // Initiate features
            testButtons = TestButtons();
            ignitionButtonPassword = IgnitionButtonPassword();
            action = Action();
        }

};