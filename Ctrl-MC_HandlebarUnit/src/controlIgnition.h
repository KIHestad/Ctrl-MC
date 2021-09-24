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
                    // Btn pressed, remember it to check for continously press
                    btnPwHoldPin = btn.pin;
                    // Detected button press, check if incorrect password keypress
                    if (passwordPressCount < IGN_PW_LENGTH && btn.pin != IGN_PW[passwordPressCount].pin) 
                        passwordMismatch = true;
                    // Check if password complete
                    passwordPressCount++;
                    Image image = Image();
                    if (passwordPressCount >= IGN_PW_LENGTH && !passwordMismatch) {
                        // Success, show on display
                        bikeStatus.ignition = ignOn;
                        display.clearDisplay();
                        image.unlocked();
                        bikeStatus.displayOffTimestamp = millis();
                    }
                    else {
                        // Show button press icon
                        int x = passwordPressCount;
                        while (x > 3)
                            x = x-3;
                        int y = passwordPressCount;
                        while (y > 9)
                            y = y-9;
                        y = (y-1) / 3;
                        display.fillRect(60 + (x*14), 8 + (y*16), 12, 14, SSD1306_INVERSE);
                        if (bikeStatus.displayOffTimestamp > 0 || passwordTimeoutProgressStarted) {
                            controlDisplay.displayOffRemove(); // Cancel running display off
                            passwordTimeoutProgressStarted = false;
                        }
                        display.display();
                    }
                    delay(250); // avoid dirty signal
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
                        controlDisplay.displayOffRemove();
                        Image image = Image();
                        display.clearDisplay();
                        image.locked();
                        // Reset values
                        passwordPressCount = 0;
                        passwordMismatch = false;
                        passwordTimeoutProgressStarted = false;
                        passwordTimeoutTimestamp = millis();
                        btnPwHoldPin = IGN_PW_START_BUTTON.pin;
                    }
                }
                else if (bikeStatus.ignition == ignPasswordMode)
                {
                    // Waiting for password, check for timeout
                    long timeNow = millis();
                    if (passwordTimeoutProgressStarted && !bikeStatus.displayOffProgressRunning) {
                        // Timeout
                        bikeStatus.ignition = ignOff;                        
                    }
                    else {
                        // Check for initiate timeout
                        if (!passwordTimeoutProgressStarted && timeNow - passwordTimeoutTimestamp > 6000) {
                            bikeStatus.displayOffTimestamp = timeNow;
                            passwordTimeoutProgressStarted = true;
                        }
                        // Check for password, read buttons
                        CheckPW(INPUT_IND_LEFT);
                        CheckPW(INPUT_IND_RIGHT);
                        CheckPW(INPUT_HORN);
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