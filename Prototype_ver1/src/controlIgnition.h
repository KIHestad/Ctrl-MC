/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlIgnition {

    /*
    *    Provide possibility to turn on or off the ignition to enable other controls
    */

    private:
        Button button = Button();
        OnBoardLed onBoardLed = OnBoardLed();
        BikeStatus bikeStatus_;
        ButtonStatus waitForReleaseInputButtonStatustatus = ButtonStatus();
        ButtonStatus buttonPasswordStart = ButtonStatus();
        bool waitForRelease = false;
        Input waitForReleaseInput;
        long passwordTimout = 0;
        int passwordPressCount = 0;
        bool passwordMismatch = false;

        void resetPasswordStart() {
            waitForRelease = true;
            waitForReleaseInput = IGN_PASSWORD_START_INPUT;
            bikeStatus_.ignitionStatus = ignitionPasswordStart;
            passwordPressCount = 0;
            passwordMismatch = false;
            passwordTimout = millis();
            Serial.println("WAITING FOR PASSWORD");
            onBoardLed.blink(2);
        }

    public:
        BikeStatus action(BikeStatus bikeStatus) {
            if (IGNITION_FEATURE_ENABLED)
            {
                bikeStatus_ = bikeStatus;
                // If button is pressed, wait unitil it is released unitil next read
                if (waitForRelease) {
                    waitForReleaseInputButtonStatustatus = button.read(waitForReleaseInput);
                    if (!waitForReleaseInputButtonStatustatus.pressed) {
                        waitForRelease = false;
                    }
                }
                if (!waitForRelease)
                {            
                    // Depending on bike status enable features
                    if (bikeStatus_.ignitionStatus == ignitionOff) {
                        // Ignition is off, only enable to turn on the bike to standby mode
                        if (IGN_PASSWORD_ENABLED) {
                            // Enable to turn on engine using password, check for password start
                            buttonPasswordStart = button.read(IGN_PASSWORD_START_INPUT);
                            if (buttonPasswordStart.pressed) {
                                resetPasswordStart();
                            }
                        }
                    }   
                    else if (bikeStatus_.ignitionStatus == ignitionPasswordStart) {
                        // Waiting for password, check for timeout
                        if (millis() - passwordTimout > 10000) {
                            bikeStatus_.ignitionStatus = ignitionOff;
                            Serial.println("PASSWORD TIMEOUT");
                            onBoardLed.blinkSlow(2);
                        }
                        else {
                            // Check for password reset
                            buttonPasswordStart = button.read(IGN_PASSWORD_START_INPUT);
                            if (buttonPasswordStart.pressed) 
                                resetPasswordStart();
                            else {
                                // Check all inputs to see if correct one is pressed according to IGN_PASSWORD
                                ButtonStatus buttonStatus[10];
                                buttonStatus[0] = button.read(SIGNAL_HORN_SWITCH_INPUT);
                                buttonStatus[1] = button.read(LIGHTS_LOW_HIGHT_SWITCH_INPUT);
                                buttonStatus[2] = button.read(INDICATOR_LEFT_SWITCH_INPUT);
                                buttonStatus[3] = button.read(INDICATOR_RIGHT_SWITCH_INPUT);
                                buttonStatus[4] = button.read(LIGHTS_MAIN_SWITCH_INPUT);
                                buttonStatus[5] = button.read(START_MOTOR_SWITCH_INPUT);
                                buttonStatus[6] = button.read(DISPLAY_MENU_ITEM_NEXT_INPUT);
                                buttonStatus[7] = button.read(DISPLAY_MENU_ITEM_SELECT_INPUT);
                                buttonStatus[8] = button.read(CLUTCH_SWITCH_INPUT);
                                buttonStatus[9] = button.read(BRAKE_SWITCH_INPUT);
                                for (size_t i = 0; i < 10; i++) {
                                    // Check all buttonStatus if any pressed
                                    if (buttonStatus[i].pressed) {
                                        // Detected button press
                                        Serial.print("PW CHAR: ");
                                        Serial.print(passwordPressCount);
                                        Serial.print(" - BUTTON PRESSED: ");
                                        Serial.print(buttonStatus[i].input.displayName);
                                        // Check if press count has passed pw length
                                        if (passwordPressCount >= IGN_PASSWORD_LENGTH) 
                                            Serial.print(" -> IGNORED - TO MANY BUTTONS PRESSED ");
                                        else {
                                            if (buttonStatus[i].input.shortName == IGN_PASSWORD[passwordPressCount].shortName) {
                                                Serial.print(" -> CORRECT ");
                                            }
                                            else {
                                                passwordMismatch = true;
                                                Serial.print(" -> WRONG :-( ");
                                            }
                                        }
                                        waitForRelease = true;
                                        waitForReleaseInput = buttonStatus[i].input;
                                        passwordPressCount++;
                                        // Check if password complete
                                        if (passwordPressCount >= IGN_PASSWORD_LENGTH && !passwordMismatch) {
                                            bikeStatus_.ignitionStatus = ignitionStandby;

                                            // TODO TURN ON IGNITION RELAY
                                            onBoardLed.blink(10);
                                            Serial.println(" -> SUCCESS - TURNING ON IGNITION ");
                                        }
                                        else {
                                            Serial.println(" -> WAITING FOR NEXT BUTTON PRESS ");
                                        }
                                        passwordTimout = millis();
                                    }
                                }
                            }
                        }

                    }
                    else if (bikeStatus_.ignitionStatus == ignitionStandby) {
                        // Ignition is on, bike in stand by mode = engine is not running, enable to start engine
                    }    
                    else if (bikeStatus_.ignitionStatus == engineStarting) {
                        // Start motor is running, trying to start engine
                    }
                    else if (bikeStatus_.ignitionStatus == engineRunning) {
                        // Engine is running, enable to stop engine
                    }
                    else if (bikeStatus_.ignitionStatus == engineStopping) {
                        // Engine is to be stopped, verify that engine has stopped
                    }
                }
            }
            return bikeStatus_;
        };
};