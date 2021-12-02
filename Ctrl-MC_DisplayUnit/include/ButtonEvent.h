class ButtonEvent {

    public:

        void loopAction() {

            Config::RelayUnitOutput output = Config::RelayUnitOutput();

            // Start / Stop engine
            if (btnStartStop.enabled)
            {
                if (bikeStatus.engine == engStopped || bikeStatus.engine == engStartMotorEngaged) {
                    bool btnStartStopIsHold = btnStartStop.isHold();
                    if (btnStartStopIsHold && bikeStatus.engine == engStopped) {
                        // Initiate start motor
                        bikeStatus.engine = engStartMotorEngaged;
                        serialCommunication.send(output.starterMotor.pin,1);
                    }
                    if (!btnStartStopIsHold && bikeStatus.engine == engStartMotorEngaged) {
                        // Disengage start motor
                        bikeStatus.engine = engStopped; // engUnknownStatus; // check relay module for bike running status
                        serialCommunication.send(output.starterMotor.pin,0);
                    }
                }
                else if (bikeStatus.engine == engRunning)
                {
                    
                }
            }

            // Horn
            if (btnMenuSelect.enabled && bikeStatus.displayMenuPageSelected == 0)
            {
                bool btnHornIsHold = btnMenuSelect.isHold();
                if (btnHornIsHold && !bikeStatus.hornActive) {
                    bikeStatus.hornActive = true;
                    serialCommunication.send(output.horn.pin,1);
                }
                else if (!btnHornIsHold && bikeStatus.hornActive) {
                    bikeStatus.hornActive = false;
                    serialCommunication.send(output.horn.pin,0);
                }
            }

            // Brake light
            if (btnBrakeFront.enabled)
            {
                bool btnBrakeFrontIsHold = btnBrakeFront.isHold();
                if (btnBrakeFrontIsHold && !bikeStatus.lightBrakeActive) {
                    bikeStatus.lightBrakeActive = true;
                    serialCommunication.send(output.lightBrake.pin,1);
                }
                else if (!btnBrakeFrontIsHold && bikeStatus.lightBrakeActive) {
                    bikeStatus.lightBrakeActive = false;
                    serialCommunication.send(output.lightBrake.pin,0);
                }
            }

            // High / Low Beam
            if (btnLightsHiLo.enabled)
            {
                if (bikeStatus.lights == BikeStatusLights::lightsMain)
                {
                    Config::Headlight headlightConfig = Config::Headlight();
                    if (btnLightsHiLo.isClicked())
                    {
                        // Toggle Hi/lo
                        int lightLowValue = 0;
                        int lightHighValue = 0;
                        if (bikeStatus.lightHilo == lightsLow) {
                            // Toggle to Hi
                            bikeStatus.lightHilo = lightsHigh;
                            lightHighValue = 1;
                            if (headlightConfig.hiWithLow)
                                lightLowValue = 1;
                        }
                        else if (bikeStatus.lightHilo == lightsHigh) {
                            // Toggle to Lo
                            bikeStatus.lightHilo = lightsLow;
                            lightLowValue = 1;
                        }
                        // Update relay
                        serialCommunication.send(output.lightHigh.pin, lightHighValue);
                        serialCommunication.send(output.lightLow.pin, lightLowValue);
                        // Update icon
                        if (bikeStatus.displayMenuPageSelected == 0)
                            displayHelper.refreshStatusPage();
                        else if (bikeStatus.displayMenuPageSelected > 0) {
                            // if light menu is selected
                            Config::DisplayMenuItemShow dmis = Config::DisplayMenuItemShow();
                            Config::DisplayMenuItemInfo dmiSelected = dmis.item[bikeStatus.displayMenuPageSelected - 1];
                            if (dmiSelected.id == 5) {
                                if (bikeStatus.displayGotoStatusPageProgress) {
                                    // Stay on same menu, cancel goto status page progress
                                    displayHelper.gotoStatusPageCancel();
                                }
                                Config::DisplayMenuSettings dmSettings = Config::DisplayMenuSettings();
                                bikeStatus.displayMenuTimeoutTimestamp = millis() + (dmSettings.shutdownWait);
                                display.clearDisplay();
                                displayMenu.showSelectedLights();
                            }
                        }
                    }
                }
                else {
                    bool btnLightsHiLoIsHold = btnLightsHiLo.isHold();
                    if (btnLightsHiLoIsHold && !bikeStatus.lightHighBeamFlash) {
                        Config::Headlight headlightConfig = Config::Headlight();
                        bikeStatus.lightHighBeamFlash = true;
                        serialCommunication.send(output.lightHigh.pin,1);
                        if (headlightConfig.hiWithLow)
                            serialCommunication.send(output.lightLow.pin,1);
                        displayHelper.refreshStatusPage();
                    }
                    else if (!btnLightsHiLoIsHold && bikeStatus.lightHighBeamFlash) {
                        Config::Headlight headlightConfig = Config::Headlight();
                        bikeStatus.lightHighBeamFlash = false;
                        serialCommunication.send(output.lightHigh.pin,0);
                        if (headlightConfig.hiWithLow)
                            serialCommunication.send(output.lightLow.pin,0);
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
                    if (btnIndicatorLeft.holdDuration() > 2000 &&  btnIndicatorRight.holdDuration() > 2000)
                    {
                        // Activate Hazard
                        bikeStatus.indicator = indHazard;
                        serialCommunication.send(output.turnSignalLeft.pin,1);
                        serialCommunication.send(output.turnSignalRight.pin,1);
                        bikeStatus.indicatorNextBlinkTimestamp = millis() + Config::Indicator::blinkSpeed;
                        bikeStatus.indicatorBlinkOn = true;
                        // Goto display status page and refresh
                        displayHelper.refreshStatusPage();
                        delay(1000); // add delay after hazard is activated
                    }
                }
                else {
                    // Check normal indicator actions
                    bool btnIndLeftIsClicked = btnIndicatorLeft.isClicked();
                    bool btnIndRightIsClicked = btnIndicatorRight.isClicked();
                    // Check if one is clicked to start indicator actions
                    if (btnIndLeftIsClicked || btnIndRightIsClicked)
                    {
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