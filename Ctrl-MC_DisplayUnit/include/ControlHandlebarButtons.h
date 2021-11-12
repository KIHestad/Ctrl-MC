class ControlHandlebarButtons {

    private: 

        bool btnHiLoHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        bool btnIndLeftHold = false; 
        bool btnIndRightHold = false; 

    public:
        
        void checkForButtonAction() {
            
            // Start / Stop engine
            if (INPUT_START_STOP.enabled)
            {
                if (bikeStatus.engine == engStopped || bikeStatus.engine == engStartMotorEngaged) {
                    bool btnStartStopPressed = readInput(INPUT_START_STOP);
                    OnBoardLed onBoardLed = OnBoardLed();
                    if (btnStartStopPressed && bikeStatus.engine == engStopped) {
                        // Initiate start motor
                        bikeStatus.engine = engStartMotorEngaged;
                        onBoardLed.on();
                    }
                    if (!btnStartStopPressed && bikeStatus.engine == engStartMotorEngaged) {
                        // Disengage start motor
                        bikeStatus.engine = engStopped; // engUnknownStatus; // check relay module for bike running status
                        onBoardLed.off();
                    }
                }
                else if (bikeStatus.engine == engRunning)
                {
                    
                }
            }

            // High / Low Beam
            if (INPUT_HILO.enabled)
            {
                bool btnHiLoPressed = readInput(INPUT_HILO);
                if (btnHiLoHold && !btnHiLoPressed)
                {
                    // Check for turning off high beam flash
                    if (bikeStatus.lightHighBeamFlash) {
                        bikeStatus.lightHighBeamFlash = false;
                        controlDisplay.refreshStatusPage();
                    }
                    // Release
                    btnHiLoHold = false;
                }
                else if (bikeStatus.lights != lightsMain && btnHiLoPressed && !btnHiLoHold)
                {
                    // Button pressed, act as passing switch = flash with hight beam because main lights are not turned on
                    btnHiLoHold = true;
                    bikeStatus.lightHighBeamFlash = true;
                    controlDisplay.refreshStatusPage();
                }
                else if (btnHiLoPressed && !btnHiLoHold)
                {
                    // Button pressed, set as hold until detected release
                    btnHiLoHold = true;
                    // Toggle Hi/lo
                    if (bikeStatus.lightHilo == lightsLow)
                        bikeStatus.lightHilo = lightsHigh;
                    else if (bikeStatus.lightHilo == lightsHigh)
                        bikeStatus.lightHilo = lightsLow;
                    // Update icon
                    if (bikeStatus.displayMenyPageSelected == 0)
                        controlDisplay.refreshStatusPage();
                    else if (bikeStatus.displayMenyPageSelected > 0) {
                        // if light menu is selected
                        MenuItem menuSelected = MENUS_AVAILABLE[bikeStatus.displayMenyPageSelected - 1];
                        if (menuSelected.id == 5) {
                            if (bikeStatus.displayGotoStatusPageProgress) {
                                // Stay on same menu, cancel goto status page progress
                                controlDisplay.gotoStatusPageCancel();
                            }
                            bikeStatus.displayMenuTimeoutTimestamp = millis() + (MENU_SHUTDOWN_WAIT * 1000);
                            display.clearDisplay();
                            controlDisplayMenu.showSelectedLights();
                        }
                    }

                    delay(250);
                }
            }

            // Indicators
            if (INPUT_IND_LEFT.enabled && INPUT_IND_RIGHT.enabled)
            {
                // Check for ind buttons
                bool btnIndLeftPressed = readInput(INPUT_IND_LEFT);
                bool btnIndRightPressed = readInput(INPUT_IND_RIGHT);
                // Check if btn released
                if (!btnIndLeftPressed && btnIndLeftHold)
                    btnIndLeftHold = false;
                if (!btnIndRightPressed && btnIndRightHold)
                    btnIndRightHold = false;
                // Check if any pressed to start indicator actions
                if (btnIndLeftPressed || btnIndRightPressed)
                {
                    SerialCommunication serialCommunication = SerialCommunication();
                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                    // Check for hold state to avoid continuosly pressed button actions
                    if (btnIndLeftPressed && btnIndRightPressed && bikeStatus.indicator != indHazard) {
                        // Activate Hazard
                        bikeStatus.indicator = indHazard;
                        btnIndLeftHold = true;
                        btnIndRightHold = true;
                        serialCommunication.send(output.turnSignalLeft.pin,1);
                        serialCommunication.send(output.turnSignalRight.pin,1);
                        bikeStatus.indicatorNextBlinkTimestamp = millis() + IND_BLINK_SPEED;
                        bikeStatus.indicatorBlinkOn = true;
                        //controlDisplay.statusTextShow("HAZARD");
                    }
                    if (btnIndLeftPressed && !btnIndLeftHold && bikeStatus.indicator == indOff) {
                        // Activate Left Turn Signal
                        btnIndLeftHold = true;
                        bikeStatus.indicator = indLeft;
                        serialCommunication.send(output.turnSignalLeft.pin,1);
                        bikeStatus.indicatorNextBlinkTimestamp = millis() + IND_BLINK_SPEED;
                        bikeStatus.indicatorBlinkOn = true;
                        //controlDisplay.statusTextShow("IND LEFT");
                    }
                    else if (btnIndRightPressed && !btnIndRightHold && bikeStatus.indicator == indOff) {
                        // Activate Right Turn Signal
                        btnIndRightHold = true;
                        bikeStatus.indicator = indRight;
                        serialCommunication.send(output.turnSignalRight.pin,1);
                        bikeStatus.indicatorNextBlinkTimestamp = millis() + IND_BLINK_SPEED;
                        bikeStatus.indicatorBlinkOn = true;
                        //controlDisplay.statusTextShow("IND RIGHT");
                    }
                    else if (((btnIndLeftPressed && !btnIndLeftHold) || (btnIndRightPressed && !btnIndRightHold)) && bikeStatus.indicator != indOff ) {
                        // Turn off
                        bikeStatus.indicator = indOff;
                        bikeStatus.indicatorBlinkOn = false;
                        btnIndLeftHold = btnIndLeftPressed;
                        btnIndRightHold = btnIndRightPressed;
                        serialCommunication.send(output.turnSignalLeft.pin,0);
                        serialCommunication.send(output.turnSignalRight.pin,0);
                        //controlDisplay.statusTextShow("IND OFF");
                    }
                    // Goto display status page and refresh
                    controlDisplay.refreshStatusPage();
                    delay(50);
                 }
            }
        }
};