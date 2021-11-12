/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class TestButtons {

    private:

        unsigned long terminateFeatureTimestamp = 0; // timestamp for when to initiating progressbar for turning off feature
        unsigned long buttonTextRemoveTimestamp = 0; // timestamp for when to remove last button press text
        Config::TestButtons configTestButtons;
        Button btnTestInitiate;

        void displayButton(String txt) {
            controlDisplay.gotoStatusPageCancel();
            controlDisplay.centeredTextShow(txt);
            buttonTextRemoveTimestamp = millis() + 3000;
            terminateFeatureTimestamp = buttonTextRemoveTimestamp + 5000;
        }

    public:

        TestButtons() {
            configTestButtons = Config::TestButtons();
            ButtonHelper btnHelper = ButtonHelper();
            btnTestInitiate = btnHelper.getButton(configTestButtons.inititateButton.pin);
        }

        void run() {
            // Check for activating button test, only when bike status is off
            if (configTestButtons.enabled) {
                // Feature enable, check bike status
                if (bikeStatus.ignition == BikeStatusIgnition::ignOff) {
                    // Check for button test activation
                    bool buttonHold = btnTestInitiate.isHold();
                    if (buttonHold && btnTestInitiate.holdDuration() > configTestButtons.longPressDuration) {
                        bikeStatus.ignition = BikeStatusIgnition::ignTestButtonsMode;
                        controlDisplay.gotoStatusPageCancel();
                        display.clearDisplay();
                        controlDisplay.statusTextShow("TEST BUTTONS", true);
                        terminateFeatureTimestamp = millis() + 8000;
                    }
                }
                else if (bikeStatus.ignition == BikeStatusIgnition::ignTestButtonsMode) {
                    
                    // Check each button
                    if (btnBrakeFront.isHold())
                        displayButton("FRONT BRAKE");
                    if (btnClutch.isHold())
                        displayButton("CLUTCH");
                    if (btnIndicatorLeft.isHold())
                        displayButton("INDICATOR LEFT");
                    if (btnIndicatorRight.isHold()) 
                        displayButton("INDICATOR RIGHT");
                    if (btnLightsHiLo.isHold()) 
                        displayButton("LIGHTS HIGH/LOW");
                    if (btnMenuNext.isHold()) 
                        displayButton("MENU NEXT");
                    if (btnMenuSelect.isHold()) 
                        displayButton("MENU SELECT");
                    if (btnStartStop.isHold()) 
                        displayButton("START / STOP");
                    // Check for remove button text
                    if (buttonTextRemoveTimestamp > 0 && millis() > buttonTextRemoveTimestamp) {
                        controlDisplay.centeredTextShow("");
                        buttonTextRemoveTimestamp = 0;
                    }
                    // Check for turn off test feature
                    if (terminateFeatureTimestamp > 0 && millis() > terminateFeatureTimestamp) {
                        controlDisplay.gotoStatusPageInitiate();
                        terminateFeatureTimestamp = 0;
                    }
                }
            }
        }


};