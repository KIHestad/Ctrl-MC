/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class IgnitionButtonPassword {

    private:
        int passwordPressCount = 0;
        bool passwordMismatch = false;
        unsigned long passwordTimeoutTimestamp = 0;
        bool passwordTimeoutProgressStarted = false;
        Button btnPwInitiate;
        Config::IgnitionButtonPassword configIgnBtnPw;

        void checkPW(Button& btn) {
            if (btn.enabled)
            {
                // Check if btn is clicked
                bool btnClicked = btn.isClicked();
                if (btnClicked) {
                    // Check if progress for goto status page is in progress, cancel now
                    if (bikeStatus.displayGotoStatusPageTimestamp > 0 || passwordTimeoutProgressStarted) {
                        displayHelper.gotoStatusPageCancel(); // Cancel running display off
                        passwordTimeoutProgressStarted = false;
                    }
                    // Button press detected, show on display
                    DisplayImage displayImage = DisplayImage();
                    displayImage.ignOff();
                    // Check if incorrect password keypress
                    if (passwordPressCount < configIgnBtnPw.pwLength && btn.pin != configIgnBtnPw.pwButtons[passwordPressCount].pin) 
                        passwordMismatch = true;
                    // Check if password complete
                    passwordPressCount++;
                    if (passwordPressCount >= configIgnBtnPw.pwLength && !passwordMismatch) {
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
                        delay(900);
                        displayHelper.refreshStatusPage();
                    }
                    else {
                        // Still not correct password entered, display dummy pw character
                        displayHelper.statusTextRemove();
                        uint8_t pwLength = passwordPressCount > 40 ? 40 : passwordPressCount;
                        uint8_t pwCharWidthInclSeparator = Config::DisplaySettings::ScreenWidth / pwLength;
                        pwCharWidthInclSeparator = pwCharWidthInclSeparator > 16 ? 16 : pwCharWidthInclSeparator;
                        uint8_t pwTotalWidht = pwCharWidthInclSeparator * pwLength;
                        uint8_t x = (Config::DisplaySettings::ScreenWidth / 2) - (pwTotalWidht / 2) + 1;
                        for (uint8_t i = 0; i < pwLength; i++)
                        {
                            display.fillRect(x, Config::DisplaySettings::ScreenHeight - Config::DisplaySettings::TextCharHeight, pwCharWidthInclSeparator-2, Config::DisplaySettings::TextCharHeight, SSD1306_WHITE);
                            x += pwCharWidthInclSeparator;
                        }
                        display.display();
                        delay(200);
                    }
                    passwordTimeoutTimestamp = millis();
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
                        // Cancel running display off
                        displayHelper.gotoStatusPageCancel();
                        DisplayImage displayImage = DisplayImage();
                        displayImage.ignOff();
                        // Reset values
                        passwordPressCount = 0;
                        passwordMismatch = false;
                        passwordTimeoutProgressStarted = false;
                        passwordTimeoutTimestamp = millis();
                        delay(200);
                    }
                }
                else if (bikeStatus.ignition == ignPasswordMode)
                {
                    // Waiting for password, check for timeout
                    if (passwordTimeoutProgressStarted && !bikeStatus.displayGotoStatusPageProgress) {
                        // Timeout
                        bikeStatus.ignition = ignOff;                        
                    }
                    else {
                        // Check for initiate timeout
                        if (!passwordTimeoutProgressStarted && millis() - passwordTimeoutTimestamp > 6000) {
                            displayHelper.gotoStatusPageInitiate();
                            passwordTimeoutProgressStarted = true;
                        }
                        // Check for password, read buttons
                        checkPW(btnBrakeFront);
                        checkPW(btnClutch);
                        checkPW(btnIndicatorLeft);
                        checkPW(btnIndicatorRight);
                        checkPW(btnLightsHiLo);
                        checkPW(btnMenuNext);
                        checkPW(btnMenuSelect);
                        checkPW(btnStartStop);
                    }
                }
            }
        };
        
};