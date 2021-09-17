/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlHorn {

    private:

        Button button = Button();
        Relay relay = Relay();
        OnBoardLed onBoardLed = OnBoardLed(); // for tessting
        long longPressTimestamp = 0;

    public:

        BikeStatus action(BikeStatus bikeStatus) {
        if (HORN_FEATURE_ENABLED && SIGNAL_HORN_SWITCH_INPUT.enabled) {
            // Read signal horn button
            ButtonStatus buttonHorn = button.read(SIGNAL_HORN_SWITCH_INPUT);
            // Start horn if initiating and switch still pressed
            if (bikeStatus.horn == hornInitiating && buttonHorn.pressed) {
                long newTimestamp = millis();
                if (newTimestamp - longPressTimestamp > HORN_INPUT__DELAY) {
                    bikeStatus.horn = hornOn;
                    relay.on(SIGNAL_HORN_OUTPUT_PIN);
                    onBoardLed.on(); // testing
                    Serial.println("HORN ON");
                }
            }
            
            // Identify if any of indicator buttons are pressed by comparing to previous value
            if (buttonHorn.pressed && bikeStatus.horn == hornOff) {
                longPressTimestamp = millis();
                bikeStatus.horn = hornInitiating;
                Serial.println("HORN INITIATING, wait one sec");
            }
            if (!buttonHorn.pressed && bikeStatus.horn != hornOff) {
                if (bikeStatus.horn == hornInitiating)
                    Serial.println("HORN CANCELLING");
                else {
                    relay.off(SIGNAL_HORN_OUTPUT_PIN);
                    onBoardLed.off();
                    Serial.println("HORN OFF");
                }
                bikeStatus.horn = hornOff;
            }
        }
        return bikeStatus;
    };
};