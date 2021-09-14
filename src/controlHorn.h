/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlHorn {
    private:

        Button button = Button();
        OnBoardLed onBoardLed = OnBoardLed();
        long longPressTimestamp = 0;
    
    public:


        BikeStatus action(BikeStatus bikeStatus) {
            
            ButtonStatusRead buttonHorn = button.read(SIGNAL_HORN_SWITCH_INPUT_PIN);
            if (buttonHorn.enabled)
            {
                // Start horn if initiating and switch still pressed
                if (bikeStatus.horn == hornInitiating && buttonHorn.pressed) {
                    long newTimestamp = millis();
                    if (newTimestamp - longPressTimestamp > HORN_INPUT_LONG_PRESS_DELAY) {
                        bikeStatus.horn = hornOn;
                        onBoardLed.on();
                        Serial.println("HORN ON");
                    }
                }
                
                // Identify if any of indicator buttons are pressed by comparing to previous value
                if (buttonHorn.pressed && bikeStatus.horn == hornOff)
                {
                    longPressTimestamp = millis();
                    bikeStatus.horn = hornInitiating;
                    Serial.println("HORN INITIATING, wait one sec");
                }
                if (!buttonHorn.pressed && bikeStatus.horn != hornOff)
                {
                    if (bikeStatus.horn == hornInitiating)
                        Serial.println("HORN CANCELLING");
                    else {
                        onBoardLed.off();
                        Serial.println("HORN OFF");
                    }
                    bikeStatus.horn = hornOff;
                    
                }
            }
            return bikeStatus;
        };
};