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
                    // If display off has been initiated, cancel now
                    if (bikeStatus.displayOffTimestamp > 0 || passwordTimeoutProgressStarted) {
                        controlDisplay.displayOffRemove(); // Cancel running display off
                        passwordTimeoutProgressStarted = false;
                    }
                    // Button press detected, show on display
                    Image image = Image();
                    image.ignitionLockFrameButtonPress();
                    display.display();
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
                        display.clearDisplay();
                        image.ignitionLockFrame();
                        image.ignitionLockKeyHoleUnlocked();
                        display.display();
                        delay(1000);
                        display.clearDisplay();
                        display.display();
                    }
                    else {
                        // Still not correct password entered, prepare for resetting display
                        delay(200); 
                        display.clearDisplay();
                        image.ignitionLockFrame();
                        image.ignitionLockKeyHoleLocked();
                        display.display();
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
                        controlDisplay.displayOffRemove();
                        Image image = Image();
                        display.clearDisplay();
                        image.ignitionLockFrame();
                        image.ignitionLockKeyHoleLocked();
                        display.display();
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
                    if (passwordTimeoutProgressStarted && !bikeStatus.displayOffProgressRunning) {
                        // Timeout
                        bikeStatus.ignition = ignOff;                        
                    }
                    else {
                        // Check for initiate timeout
                        if (!passwordTimeoutProgressStarted && millis() - passwordTimeoutTimestamp > 6000) {
                            controlDisplay.displayOffInititate();
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

        void checkForStartStopEngine() {
            OnBoardLed onBoardLed = OnBoardLed();
            if (INPUT_START_STOP.enabled)
            {
                if (bikeStatus.engine == engStopped || bikeStatus.engine == engStartMotorEngaged) {
                    bool btnStartStopPressed = readInput(INPUT_START_STOP);
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
        };

        
};