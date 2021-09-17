/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class Test {

    private:

        Button button = Button();

    public:

        void displayInputs() {
            // Check all inputs to see if correct one is pressed according to IGN_PASSWORD
            ButtonStatus buttonStatus[12];
            buttonStatus[0] = button.read(MAIN_IGNITION_SWITCH_INPUT);
            buttonStatus[1] = button.read(SIGNAL_HORN_SWITCH_INPUT);
            buttonStatus[2] = button.read(LIGHTS_LOW_HIGHT_SWITCH_INPUT);
            buttonStatus[3] = button.read(INDICATOR_LEFT_SWITCH_INPUT);
            buttonStatus[4] = button.read(INDICATOR_RIGHT_SWITCH_INPUT);
            buttonStatus[5] = button.read(LIGHTS_MAIN_SWITCH_INPUT);
            buttonStatus[6] = button.read(START_MOTOR_SWITCH_INPUT);
            buttonStatus[7] = button.read(DISPLAY_MENU_ITEM_NEXT_INPUT);
            buttonStatus[8] = button.read(DISPLAY_MENU_ITEM_SELECT_INPUT);
            buttonStatus[9] = button.read(CLUTCH_SWITCH_INPUT);
            buttonStatus[10] = button.read(BRAKE_SWITCH_INPUT);
            buttonStatus[11] = button.read(NEUTRAL_SWITCH_INPUT);
            Serial.print("#");
            Serial.print(millis());
            Serial.print(" > ");
            for (size_t i = 0; i < 12; i++) {
                //Read all button names and values if enabled
                ButtonStatus btn = buttonStatus[i];
                if (btn.input.enabled)
                {
                    Serial.print(btn.input.shortName);
                    if (btn.pressed) {
                        if (btn.input.pinType == analogPin)
                        {
                            Serial.print(" EXP:");
                            Serial.print(btn.input.expectedValue);
                            Serial.print(" ");
                        }
                        Serial.print("=>");
                    }
                    else
                        Serial.print("  ");
                    Serial.print(btn.value);
                    Serial.print("\t");
                }
            }
            Serial.println("");
            delay(1000);
        }

        void i2c_scanner() {

            // --------------------------------------
            // i2c_scanner
            //
            // Version 1
            //    This program (or code that looks like it)
            //    can be found in many places.
            //    For example on the Arduino.cc forum.
            //    The original author is not know.
            // Version 2, Juni 2012, Using Arduino 1.0.1
            //     Adapted to be as simple as possible by Arduino.cc user Krodal
            // Version 3, Feb 26  2013
            //    V3 by louarnold
            // Version 4, March 3, 2013, Using Arduino 1.0.3
            //    by Arduino.cc user Krodal.
            //    Changes by louarnold removed.
            //    Scanning addresses changed from 0...127 to 1...119,
            //    according to the i2c scanner by Nick Gammon
            //    https://www.gammon.com.au/forum/?id=10896
            // Version 5, March 28, 2013
            //    As version 4, but address scans now to 127.
            //    A sensor seems to use address 120.
            // Version 6, November 27, 2015.
            //    Added waiting for the Leonardo serial communication.
            //
            //
            // This sketch tests the standard 7-bit addresses
            // Devices with higher bit address might not be seen properly.
            //
            byte error, address;
            int nDevices;
            Serial.println("Scanning...");
            nDevices = 0;
            for(address = 1; address < 127; address++ )
            {
                Serial.print(".");
                // The i2c_scanner uses the return value of
                // the Write.endTransmisstion to see if
                // a device did acknowledge to the address.
                Wire.beginTransmission(address);
                error = Wire.endTransmission();
            
                if (error == 0)
                {
                    Serial.print("I2C device found at address 0x");
                    if (address<16)
                        Serial.print("0");
                    Serial.print(address,HEX);
                    Serial.println("  !");
                    nDevices++;
                }
                else if (error==4)
                {
                    Serial.print("Unknown error at address 0x");
                    if (address<16)
                        Serial.print("0");
                    Serial.println(address,HEX);
                }    
            }
            if (nDevices == 0)
                Serial.println("No I2C devices found\n");
            else
                Serial.println("done\n");
            
            delay(5000);           // wait 5 seconds for next scan
        }
};