/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

class ControlIndicators {
    
    private:
        Config config = Config();
        ButtonActon buttonAction = ButtonActon();
        Relay relay = Relay();
        bool waitForRelease = false; // flag indicating that indicator switch has been pressed
        long buttonPressTimestamp = 0; // timestamp for when indicator button was pressed, either start or stop, used with blinkAutoShutDownSec and for ignore bad signal from switch
        long longPressTimestamp = 0; // hazard has a delay, timestamp for when it was initiated
        long blinkTimestamp = 0; // timestamp for previous blink
        long blinkInterval = config.indicatorsBlinkIntervalSpeed; // speed on turn signal blinks in ms
        bool blinkOn = false; // flag indicating if turn signal is currently on or off
        int blinkAutoShutOffSec = config.indicatorsAutoShutOff; // atomaticly turn off indicators after number of seconds

    public:

        BikeStatus action(BikeStatus bikeStatus) {
            // Identify if any of indicator buttons are pressed or released by comparing to previous value
            ButtonStatusRead buttonLeft = buttonAction.readAnalog(config.inHandlebarButtonArray, config.handlebarButtonSignal_Indicator_Left);
            ButtonStatusRead buttonRight = buttonAction.readAnalog(config.inHandlebarButtonArray, config.handlebarButtonSignal_Indicator_Right);
            if (waitForRelease) {
                if (!buttonRight.pressed && !buttonLeft.pressed) {
                    // Released
                    waitForRelease = false;
                }
                else {
                    // if hazard activated check for longpress
                    if (config.hazardActivateLongPressDelay > -1) {
                        long newTimestamp = millis();
                        if (newTimestamp - longPressTimestamp > config.hazardActivateLongPressDelay)
                        {
                            bikeStatus.indicators = hazard;
                            Serial.println("HAZARD ON");
                            blinkTimestamp = millis() - blinkInterval;;
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
                            relay.off(config.outIndicatorLeft);
                            relay.off(config.outIndicatorRight);
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
                            blinkTimestamp = millis() - blinkInterval;
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
                if (blinkAutoShutOffSec > 0 && (newTimestamp - buttonPressTimestamp) > (blinkAutoShutOffSec * 1000)) {
                    // Autoshutdown now
                    bikeStatus.indicators = indicatorsOff;
                    Serial.println("INDICATORS AUTO OFF ");
                    relay.off(config.outIndicatorLeft);
                    relay.off(config.outIndicatorRight);
                    blinkOn = false;
                }
                else if (newTimestamp - blinkTimestamp > blinkInterval) {
                    // Blink on/off
                    blinkOn = !blinkOn;
                    if (blinkOn) {
                        if (bikeStatus.indicators == hazard) {
                            relay.on(config.outIndicatorLeft);
                            relay.on(config.outIndicatorRight);
                        }
                        else if (bikeStatus.indicators == turnLeft) {
                            relay.on(config.outIndicatorLeft);
                        }
                        else {
                            relay.on(config.outIndicatorRight);
                        }
                    } 
                    else {
                        relay.off(config.outIndicatorLeft);
                        relay.off(config.outIndicatorRight);
                    }
                    blinkTimestamp = newTimestamp;
                }
            }
            
            return bikeStatus;
        };
};