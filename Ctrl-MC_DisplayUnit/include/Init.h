/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Init {

    public:
        
        void run() {
            // OLED display speed
            Wire.setClock(400000);
            // Serial comm
            HardwareSerial SerialPort(2); // use UART2
            SerialPort.begin(Config::serialCommSpeed, SERIAL_8N1, Config::serialPort_U2_RX, Config::serialPort_U2_TX);
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