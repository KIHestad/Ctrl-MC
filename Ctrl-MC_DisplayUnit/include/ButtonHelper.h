/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class ButtonHelper {

    public:

        Button getButton(uint8_t pin) {
            Config::DisplayUnitInput duInput = Config::DisplayUnitInput();
            if (pin == duInput.brakeFront.pin)
                return btnBrakeFront;
            else if (pin == duInput.clutch.pin)
                return btnClutch;
            else if (pin == duInput.indicatorLeft.pin)
                return btnIndicatorLeft;
            else if (pin == duInput.indicatorRight.pin)
                return btnIndicatorRight;
            else if (pin == duInput.lightsHiLo.pin)
                return btnLightsHiLo;
            else if (pin == duInput.menuStartStop.pin)
                return btnMenuStartStop;
            else if (pin == duInput.menuMain.pin)
                return btnMenuMain;
            else if (pin == duInput.brakeFront.pin)
                return btnBrakeFront;
            else
                return Button();                
        }

};
