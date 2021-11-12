/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Button {

    private:

        bool pressed = false;
        bool clicked = false;
        unsigned long pressedTimestamp = 0;

        // Read button state if enabled, skip reading if just read to avoid dirty signal
        void read() {
            if (enabled && millis() > pressedTimestamp + 200) {
                pressed = digitalRead(pin) == LOW;
                if (pressed && pressedTimestamp == 0)
                    pressedTimestamp = millis();
                else if (!pressed)
                    pressedTimestamp = 0;
            }
        }

    public:

        bool enabled;
        uint8_t pin;

        void init(Config::Feature feature) {
            this->enabled = feature.enabled;
            this->pin = feature.pin;
        }

        // Check if button is hold
        bool isHold() {
            read();
            return pressed;
        }

        // Return pressed duration
        unsigned long holdDuration() {
            if (pressedTimestamp == 0)
                return 0;
            else
                return millis() - pressedTimestamp;
        }

        // Check if button is clicked
        bool isClicked() {
            read();
            if (pressed && !clicked) {
                // button pressed but not set as clicked, return as clicked now
                clicked = true;
                return true;
            }
            else if (pressed && clicked) {
                // button is pressed but already returned as clicked, skip returning a pressed button as repeated clicks
                return false;
            }
            else {
                // button is no longer pressed, set as not clicked to enable new click
                clicked = false;
                return false;
            }
        }
};