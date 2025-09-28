/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class TestButtons {

    private:

        Config::TestButtons configTestButtons;
        Button btnTestInitiate;
        uint8_t lastButtonHold = 0;
        uint8_t lastButtonClicked = 0;
        int clickCount = 0;

        void checkButton(Button& btn, String txt) {
            bool updateDisplay = false;
            // Check if clicked
            bool isClicked = btn.isClicked();
            if (isClicked) {
                // Show button name
                displayHelper.rowTextShow(txt, 0, false);
                // Show new click event
                clickCount++;
                String clickInfo = String();
                clickInfo = "CLICK ";
                clickInfo += clickCount;
                clickInfo += " - PIN:";
                clickInfo += btn.pin;
                displayHelper.rowTextShow(clickInfo, 1, false);
                lastButtonClicked = btn.pin;
                updateDisplay = true;
                // Display timeout
                displayHelper.displayTimeoutInitiate();
            }
            // Check if button is hold
            if (btn.isHold()) {
                if (btn.pin != lastButtonHold) {
                    // Show hold event
                    displayHelper.rowTextShow("BUTTON HOLD", 2, false);
                    updateDisplay = true;
                    lastButtonHold = btn.pin;
                }
                displayHelper.displayTimeoutCancel();
            }
            else if(btn.pin == lastButtonHold) {
                // Remove hold event
                displayHelper.rowTextShow("", 2, false);
                updateDisplay = true;
                lastButtonHold = 0;
                // Display timeout
                displayHelper.displayTimeoutInitiate();
            }
            // Update disp
            if (updateDisplay)
                displayHelper.refresh();
        }

    public:

        TestButtons() {
            configTestButtons = Config::TestButtons();
            ButtonHelper btnHelper = ButtonHelper();
            btnTestInitiate = btnHelper.getButton(configTestButtons.inititateButton.pin);
        }

        void loopAction() {
            // Check for activating button test, only when bike status is off
            if (configTestButtons.enabled) {
                // Feature enable, check bike status
                if (bikeStatus.ignition == BikeStatusIgnition::ignOff) {
                    // Check for button test activation
                    bool buttonHold = btnTestInitiate.isHold();
                    if (buttonHold && btnTestInitiate.holdDuration() > configTestButtons.longPressDuration) {
                        bikeStatus.ignition = BikeStatusIgnition::ignTestButtonsMode;
                        displayHelper.displayTimeoutCancel();
                        displayHelper.clearDisplay();
                        displayHelper.statusTextShow("*** Test Mode ***", true);
                        clickCount = 0;
                    }
                }
                else if (bikeStatus.ignition == BikeStatusIgnition::ignTestButtonsMode) {
                    // Check each button
                    checkButton(btnBrakeFront, "FRONT BRAKE");
                    checkButton(btnClutch, "CLUTCH");
                    checkButton(btnIndicatorLeft, "INDICATOR LEFT");
                    checkButton(btnIndicatorRight, "INDICATOR RIGHT");
                    checkButton(btnLightsHiLo, "LIGHTS HIGH<->LOW");
                    checkButton(btnHorn, "HORN");
                    checkButton(btnMenuMain, "MENU MAIN");
                    checkButton(btnMenuStartStop, "MENU START/STOP");
                }
            }
        }


};