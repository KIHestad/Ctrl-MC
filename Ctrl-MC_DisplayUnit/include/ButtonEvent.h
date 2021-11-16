class ButtonEvent {

    public:
        
        void loopAction() {
            
            // Start / Stop engine
            if (btnStartStop.enabled)
            {
                if (bikeStatus.engine == engStopped || bikeStatus.engine == engStartMotorEngaged) {
                    bool btnStartStopIsHold = btnStartStop.isHold();
                    if (btnStartStopIsHold && bikeStatus.engine == engStopped) {
                        // Initiate start motor
                        bikeStatus.engine = engStartMotorEngaged;
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.starterMotor.pin,1);
                    }
                    if (!btnStartStopIsHold && bikeStatus.engine == engStartMotorEngaged) {
                        // Disengage start motor
                        bikeStatus.engine = engStopped; // engUnknownStatus; // check relay module for bike running status
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.starterMotor.pin,0);
                    }
                }
                else if (bikeStatus.engine == engRunning)
                {
                    
                }
            }

            // Horn
            if (btnMenuSelect.enabled && bikeStatus.displayMenyPageSelected == 0)
            {
                bool btnHornIsHold = btnMenuSelect.isHold();
                if (btnHornIsHold && !bikeStatus.hornActive) {
                    SerialCommunication serialCommunication = SerialCommunication();
                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                    serialCommunication.send(output.horn.pin,1);
                }
                else if (!btnHornIsHold && bikeStatus.hornActive) {
                    SerialCommunication serialCommunication = SerialCommunication();
                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                    serialCommunication.send(output.horn.pin,0);
                }
            }

            // Brake light
            if (btnBrakeFront.enabled)
            {
                bool btnBrakeFrontIsHold = btnBrakeFront.isHold();
                if (btnBrakeFrontIsHold && !bikeStatus.lightBrakeActive) {
                    bikeStatus.lightBrakeActive = true;
                    SerialCommunication serialCommunication = SerialCommunication();
                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                    serialCommunication.send(output.lightBrake.pin,1);
                }
                else if (!btnBrakeFrontIsHold && bikeStatus.lightBrakeActive) {
                    bikeStatus.lightBrakeActive = false;
                    SerialCommunication serialCommunication = SerialCommunication();
                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                    serialCommunication.send(output.lightBrake.pin,0);
                }
            }

            // High / Low Beam
            if (btnLightsHiLo.enabled)
            {
                if (bikeStatus.lights == BikeStatusLights::lightsMain)
                {
                    if (btnLightsHiLo.isClicked())
                    {
                        // Toggle Hi/lo
                        int low = 0;
                        int high = 0;
                        if (bikeStatus.lightHilo == lightsLow) {
                            bikeStatus.lightHilo = lightsHigh;
                            high = 1;
                        }
                        else if (bikeStatus.lightHilo == lightsHigh) {
                            bikeStatus.lightHilo = lightsLow;
                            low = 1;
                        }
                        // Update relay
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.lightHigh.pin,high);
                        serialCommunication.send(output.lightLow.pin,low);
                        // Update icon
                        if (bikeStatus.displayMenyPageSelected == 0)
                            displayHelper.refreshStatusPage();
                        else if (bikeStatus.displayMenyPageSelected > 0) {
                            // if light menu is selected
                            Config::DisplayMenuItemShow dmis = Config::DisplayMenuItemShow();
                            Config::DisplayMenuItemInfo dmiSelected = dmis.item[bikeStatus.displayMenyPageSelected - 1];
                            if (dmiSelected.id == 5) {
                                if (bikeStatus.displayGotoStatusPageProgress) {
                                    // Stay on same menu, cancel goto status page progress
                                    displayHelper.gotoStatusPageCancel();
                                }
                                Config::DisplayMenuSettings dmSettings = Config::DisplayMenuSettings();
                                bikeStatus.displayMenuTimeoutTimestamp = millis() + (dmSettings.ShutdownWait);
                                display.clearDisplay();
                                displayMenu.showSelectedLights();
                            }
                        }
                    }
                }
                else {
                    bool btnLightsHiLoIsHold = btnLightsHiLo.isHold();
                    if (btnLightsHiLoIsHold && !bikeStatus.lightHighBeamFlash) {
                        bikeStatus.lightHighBeamFlash = true;
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.lightHigh.pin,1);
                        displayHelper.refreshStatusPage();
                    }
                    else if (!btnLightsHiLoIsHold && bikeStatus.lightHighBeamFlash) {
                        bikeStatus.lightHighBeamFlash = false;
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.lightHigh.pin,0);
                        displayHelper.refreshStatusPage();
                    }
                }
            }

            // Indicators
            if (btnIndicatorLeft.enabled && btnIndicatorRight.enabled)
            {
                // Check for hazard first
                if (btnIndicatorLeft.isHold() && btnIndicatorRight.isHold() && bikeStatus.indicator != BikeStatusIndicator::indHazard) {
                    // Check for hold duration before activating
                    if (btnIndicatorLeft.holdDuration() > 3000 &&  btnIndicatorRight.holdDuration() > 3000)
                    {
                        // Activate Hazard
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        bikeStatus.indicator = indHazard;
                        serialCommunication.send(output.turnSignalLeft.pin,1);
                        serialCommunication.send(output.turnSignalRight.pin,1);
                        bikeStatus.indicatorNextBlinkTimestamp = millis() + Config::Indicator::blinkSpeed;
                        bikeStatus.indicatorBlinkOn = true;
                        // Goto display status page and refresh
                        displayHelper.refreshStatusPage();
                    }
                }
                else {
                    // Check normal indicator actions
                    bool btnIndLeftIsClicked = btnIndicatorLeft.isClicked();
                    bool btnIndRightIsClicked = btnIndicatorRight.isClicked();
                    // Check if one is clicked to start indicator actions
                    if (btnIndLeftIsClicked || btnIndRightIsClicked)
                    {
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        if (btnIndLeftIsClicked && bikeStatus.indicator == indOff) {
                            // Activate Left Turn Signal
                            bikeStatus.indicator = indLeft;
                            serialCommunication.send(output.turnSignalLeft.pin,1);
                            bikeStatus.indicatorNextBlinkTimestamp = millis() + Config::Indicator::blinkSpeed;
                            bikeStatus.indicatorBlinkOn = true;
                        }
                        else if (btnIndRightIsClicked && bikeStatus.indicator == indOff) {
                            // Activate Right Turn Signal
                            bikeStatus.indicator = indRight;
                            serialCommunication.send(output.turnSignalRight.pin,1);
                            bikeStatus.indicatorNextBlinkTimestamp = millis() + Config::Indicator::blinkSpeed;
                            bikeStatus.indicatorBlinkOn = true;
                        }
                        else if ((btnIndLeftIsClicked || btnIndRightIsClicked) && bikeStatus.indicator != indOff ) {
                            // Turn off
                            bikeStatus.indicator = indOff;
                            bikeStatus.indicatorBlinkOn = false;
                            serialCommunication.send(output.turnSignalLeft.pin,0);
                            serialCommunication.send(output.turnSignalRight.pin,0);
                        }
                        // Goto display status page and refresh
                        displayHelper.refreshStatusPage();
                    }
                }
            }
        }
};