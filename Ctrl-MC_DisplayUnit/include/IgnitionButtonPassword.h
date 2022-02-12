/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class IgnitionButtonPassword {

    private:
        int passwordPressCount = 0;
        bool passwordMismatch = false;
        Button btnPwInitiate;
        Config::IgnitionButtonPassword configIgnBtnPw;

        void checkPW(Button& btn) {
            if (btn.enabled)
            {
                // Check if btn is clicked
                bool btnClicked = btn.isClicked();
                if (btnClicked) {
                    // Restart timeout progress
                    displayHelper.displayTimeoutInitiate(5000); 
                    // Button press detected, show on display
                    DisplayImage displayImage = DisplayImage();
                    displayImage.ignOff();
                    // Check if incorrect password keypress
                    if (passwordPressCount < configIgnBtnPw.pwLength && btn.pin != configIgnBtnPw.pwButtons[passwordPressCount].pin) 
                        passwordMismatch = true;
                    // Check if password complete
                    passwordPressCount++;
                    if ((passwordPressCount >= configIgnBtnPw.pwLength && !passwordMismatch) || Config::debugMode) {
                        // Success, update bike status and show on display
                        bikeStatus.ignition = ignOn;
                        bikeStatus.ignitionOnTimestamp = millis();
                        // Trigger handshake immediately
                        bikeStatus.handshakeOK = true;
                        bikeStatus.handshakeNextTimestamp = millis(); 
                        action.performHandshake();
                        // Turn on relay
                        SerialCommunication serialCommunication = SerialCommunication();
                        Config::RelayUnitOutput output = Config::RelayUnitOutput();
                        serialCommunication.send(output.mainPower.pin, 1);
                        // Show animation
                        displayImage.ignOffToOn1();
                        delay(50);
                        displayImage.ignOffToOn2();
                        delay(50);
                        displayImage.ignOn();
                        displayHelper.refresh();
                        delay(900);
                        displayHelper.refreshStatusPage();
                    }
                    else {
                        // Still not correct password entered, display dummy pw character
                        displayHelper.statusTextRemove();
                        uint8_t pwLength = passwordPressCount > 40 ? 40 : passwordPressCount;
                        uint8_t pwCharWidthInclSeparator = Config::DisplaySettings::screenWidth / pwLength;
                        pwCharWidthInclSeparator = pwCharWidthInclSeparator > 16 ? 16 : pwCharWidthInclSeparator;
                        uint8_t pwTotalWidht = pwCharWidthInclSeparator * pwLength;
                        uint8_t x = (Config::DisplaySettings::screenWidth / 2) - (pwTotalWidht / 2) + 1;
                        for (uint8_t i = 0; i < pwLength; i++)
                        {
                            displayHelper.fillRect(x, Config::DisplaySettings::screenHeight - Config::DisplaySettings::textCharHeight, pwCharWidthInclSeparator-2, Config::DisplaySettings::textCharHeight, 1);
                            x += pwCharWidthInclSeparator;
                        }
                        displayHelper.refresh();
                        delay(200);
                    }
                }
            }
        };

    public:
        
        IgnitionButtonPassword() {
            configIgnBtnPw = Config::IgnitionButtonPassword();
            ButtonHelper btnHelper = ButtonHelper();
            btnPwInitiate = btnHelper.getButton(configIgnBtnPw.inititateButton.pin);
        }

        void loopAction() {
            // Check for activating ingnition button password
            Config::IgnitionButtonPassword configIgnBtnPw = Config::IgnitionButtonPassword();
            if (configIgnBtnPw.enabled && configIgnBtnPw.inititateButton.enabled)
            {
                if (bikeStatus.ignition == BikeStatusIgnition::ignOff) {
                    if (btnPwInitiate.isClicked())
                    {
                        // Activated password feature
                        bikeStatus.ignition = ignPasswordMode;
                        // Show icon on display
                        DisplayImage displayImage = DisplayImage();
                        displayImage.ignOff();
                        // Reset values
                        passwordPressCount = 0;
                        passwordMismatch = false;
                        // wait until button is released
                        while (btnPwInitiate.isHold()) {
                            delay(100);
                        }
                        // Start display timeout
                        displayHelper.displayTimeoutInitiate(5000);
                    }
                }
                else if (bikeStatus.ignition == ignPasswordMode)
                {
                    // Check for password, read buttons
                    checkPW(btnClutch);
                    checkPW(btnIndicatorLeft);
                    checkPW(btnIndicatorRight);
                    checkPW(btnLightsHiLo);
                    checkPW(btnHorn);
                    checkPW(btnMenuMain);
                    checkPW(btnMenuStartStop);
                    checkPW(btnBrakeFront);
                }
            }
        };
        
};