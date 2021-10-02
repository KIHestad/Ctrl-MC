/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class ControlIgnition {

    private:
        int passwordPressCount = 0;
        bool passwordMismatch = false;
        unsigned long passwordTimeoutTimestamp = 0;
        bool passwordTimeoutProgressStarted = false;
        int8_t btnPwHoldPin = -1; // Remember pin of last pressed button, when set > 0 that pin is set as hold until release is

        void CheckPW(Input btn) {
            if (btn.enabled)
            {
                // Check if btn is pressed
                bool btnPressed = readInput(btn);
                // Check for continously press
                if (btn.pin == btnPwHoldPin && !btnPressed) {
                    // Relese
                    btnPwHoldPin = -1;
                }
                else if (btnPressed && btn.pin != btnPwHoldPin) {
                    // Check if progress for goto status page is in progress, cancel now
                    if (bikeStatus.displayGotoStatusPageTimestamp > 0 || passwordTimeoutProgressStarted) {
                        controlDisplay.gotoStatusPageCancel(); // Cancel running display off
                        passwordTimeoutProgressStarted = false;
                    }
                    // Button press detected, show on display
                    Image image = Image();
                    image.ignOff();
                    // Remember it to check for continously press later
                    btnPwHoldPin = btn.pin;
                    // Check if incorrect password keypress
                    if (passwordPressCount < IGN_PW_LENGTH && btn.pin != IGN_PW[passwordPressCount].pin) 
                        passwordMismatch = true;
                    // Check if password complete
                    passwordPressCount++;
                    if (passwordPressCount >= IGN_PW_LENGTH && !passwordMismatch) {
                        // Success, update bike status and show on display
                        bikeStatus.ignition = ignOn;
                        bikeStatus.ignitionOnTimestamp = millis();
                        bikeStatus.communicationOK = true;
                        bikeStatus.communicationLastPing = millis() - (SYSTEM_HANDSHAKE_CHECK_INTERVAL * 1000);
                        image.ignOffToOn1();
                        delay(50);
                        image.ignOffToOn2();
                        delay(50);
                        image.ignOn();
                        delay(900);
                        controlDisplay.refreshStatusPage();
                    }
                    else {
                        // Still not correct password entered, display dummy pw character
                        controlDisplay.statusTextRemove();
                        uint8_t pwLength = passwordPressCount > 40 ? 40 : passwordPressCount;
                        uint8_t pwCharWidthInclSeparator = DISPLAY_SCREEN_WIDTH / pwLength;
                        pwCharWidthInclSeparator = pwCharWidthInclSeparator > 16 ? 16 : pwCharWidthInclSeparator;
                        uint8_t pwTotalWidht = pwCharWidthInclSeparator * pwLength;
                        uint8_t x = (DISPLAY_SCREEN_WIDTH / 2) - (pwTotalWidht / 2) + 1;
                        for (uint8_t i = 0; i < pwLength; i++)
                        {
                            display.fillRect(x, DISPLAY_SCREEN_HEIGHT - DISPLAY_TEXT_CHAR_HEIGHT, pwCharWidthInclSeparator-2, DISPLAY_TEXT_CHAR_HEIGHT, SSD1306_WHITE);
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
        
        void checkForPassword() {
            if (IGN_PW_ENABLED && IGN_PW_START_BUTTON.enabled)
            {
                if (bikeStatus.ignition == ignOff) {
                    bool btnStartPwPressed = readInput(IGN_PW_START_BUTTON);
                    if (btnStartPwPressed)
                    {
                        // Activated password feature
                        bikeStatus.ignition = ignPasswordMode;
                        // Cancel running display off
                        controlDisplay.gotoStatusPageCancel();
                        Image image = Image();
                        image.ignOff();
                        // Reset values
                        passwordPressCount = 0;
                        passwordMismatch = false;
                        passwordTimeoutProgressStarted = false;
                        passwordTimeoutTimestamp = millis();
                        btnPwHoldPin = IGN_PW_START_BUTTON.pin;
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
                            controlDisplay.gotoStatusPageInitiate();
                            passwordTimeoutProgressStarted = true;
                        }
                        // Check for password, read buttons
                        CheckPW(INPUT_IND_LEFT);
                        CheckPW(INPUT_IND_RIGHT);
                        CheckPW(INPUT_HORN);
                        CheckPW(INPUT_HILO);
                        CheckPW(INPUT_MENU_NEXT);
                        CheckPW(INPUT_MENU_SELECT);
                        CheckPW(INPUT_START_STOP);
                        CheckPW(INPUT_CLUTCH);
                        CheckPW(INPUT_BRAKE_FRONT);
                    }
                }
            }
        };
        
};