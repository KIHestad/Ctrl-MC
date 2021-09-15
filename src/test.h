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
            String output = String();
            for (size_t i = 0; i < 12; i++) {
                //Read all button names and values if enabled
                ButtonStatus btn = buttonStatus[i];
                if (btn.enabled)
                {
                    output += btn.input.name;
                    if (btn.pressed) {
                        if (btn.input.pinType == analogPin)
                        {
                            output += " EXP:";
                            output += btn.input.expectedValue;
                            output += " ";
                        }
                        output += "=>";
                    }
                    else
                        output += "  ";
                    output += btn.value;
                    output += "\t";
                }
            }
            Serial.println(output);
        }

};