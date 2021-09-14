/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlIndicators {
    
    private:
        Button button = Button();
        Relay relay = Relay();
        bool waitForRelease = false; // flag indicating that indicator switch has been pressed
        long buttonPressTimestamp = 0; // timestamp for when indicator button was pressed, either start or stop, used with blinkAutoShutDownSec and for ignore bad signal from switch
        long longPressTimestamp = 0; // hazard has a delay, timestamp for when it was initiated
        long blinkTimestamp = 0; // timestamp for previous blink
        bool blinkOn = false; // flag indicating if turn signal is currently on or off

    public:

        BikeStatus action(BikeStatus bikeStatus) {
            // Identify if any of indicator buttons are pressed or released by comparing to previous value
            ButtonStatusRead buttonLeft = button.read(INDICATOR_LEFT_SWITCH_INPUT_PIN);
            ButtonStatusRead buttonRight = button.read(INDICATOR_RIGHT_SWITCH_INPUT_PIN);
            if (waitForRelease) {
                if (!buttonRight.pressed && !buttonLeft.pressed) {
                    // Released
                    waitForRelease = false;
                }
                else {
                    // if hazard activated check for longpress
                    if (INDICATORS_HAZARD_LONG_PRESS_ENABLE > -1) {
                        long newTimestamp = millis();
                        if (newTimestamp - longPressTimestamp > INDICATORS_HAZARD_LONG_PRESS_ENABLE)
                        {
                            bikeStatus.indicators = hazard;
                            Serial.println("HAZARD ON");
                            blinkTimestamp = millis() - INDICATORS_BLINK_INTERVAL_SPEED;;
                            blinkOn = true;
                            waitForRelease = true;
                        }
                    }
                }
            }
            else {
                // If pressed any indicator button
                if (buttonLeft.pressed || buttonRight.pressed) {
                    // Ignore button press first 250ms in case of bad signal from button
                    if (millis() - buttonPressTimestamp > 250)
                    {
                        buttonPressTimestamp = millis();
                        // Check for turn off or on
                        if (bikeStatus.indicators != indicatorsOff) {
                            // Turn off
                            bikeStatus.indicators = indicatorsOff;
                            Serial.println("INDICATORS OFF");
                            relay.off(INDICATOR_LEFT_OUTPUT_PIN);
                            relay.off(INDICATOR_RIGHT_OUTPUT_PIN);
                            blinkOn = false;
                        }
                        else {
                            // Turn on
                            if (buttonRight.pressed) {
                                bikeStatus.indicators = turnRight;
                                Serial.println("TURN RIGHT");
                                //relay.On(pin.RelayIndicatorRight);
                            }
                            else if (buttonLeft.pressed) {
                                bikeStatus.indicators = turnLeft;
                                Serial.println("TURN LEFT");
                                //relay.On(pin.RelayIndicatorLeft);
                            }
                            longPressTimestamp = millis();
                            blinkTimestamp = millis() - INDICATORS_BLINK_INTERVAL_SPEED;
                            blinkOn = false;
                        }
                        waitForRelease = true;
                    }
                }
            }
            // Perform blink
            if (bikeStatus.indicators == turnLeft || bikeStatus.indicators == turnRight || bikeStatus.indicators == hazard) {
                long newTimestamp = millis();
                // Check for autoshutdown
                if (INDICATORS_AUTO_SHUT_OFF >= -1 && (newTimestamp - buttonPressTimestamp) > (INDICATORS_AUTO_SHUT_OFF * 1000)) {
                    // Autoshutdown now
                    bikeStatus.indicators = indicatorsOff;
                    Serial.println("INDICATORS AUTO OFF ");
                    relay.off(INDICATOR_LEFT_OUTPUT_PIN);
                    relay.off(INDICATOR_RIGHT_OUTPUT_PIN);
                    blinkOn = false;
                }
                else if (newTimestamp - blinkTimestamp > INDICATORS_BLINK_INTERVAL_SPEED) {
                    // Blink on/off
                    blinkOn = !blinkOn;
                    if (blinkOn) {
                        if (bikeStatus.indicators == hazard) {
                            relay.on(INDICATOR_LEFT_OUTPUT_PIN);
                            relay.on(INDICATOR_RIGHT_OUTPUT_PIN);
                        }
                        else if (bikeStatus.indicators == turnLeft) {
                            relay.on(INDICATOR_LEFT_OUTPUT_PIN);
                        }
                        else {
                            relay.on(INDICATOR_RIGHT_OUTPUT_PIN);
                        }
                    } 
                    else {
                        relay.off(INDICATOR_LEFT_OUTPUT_PIN);
                        relay.off(INDICATOR_RIGHT_OUTPUT_PIN);
                    }
                    blinkTimestamp = newTimestamp;
                }
            }
            
            return bikeStatus;
        };
};