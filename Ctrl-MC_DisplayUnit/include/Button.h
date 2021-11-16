/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class Button {

    private:

        bool pushed = false;
        bool clickReturned = false;
        unsigned long pushedTimestamp = 0;

        // Read button state if enabled, skip reading if just read to avoid dirty signal
        void read() {
            if (enabled && millis() > pushedTimestamp + 250) {
                pushed = digitalRead(pin) == LOW;
                if (pushed && pushedTimestamp == 0)
                    pushedTimestamp = millis();
                else if (!pushed)
                    pushedTimestamp = 0;
            }
        }

    public:
        bool enabled;
        uint8_t pin;

        void init(Config::Feature feature) {
            this->enabled = feature.enabled;
            this->pin = feature.pin;
            // Set pin mode
            if (feature.enabled) {
                pinMode(feature.pin, INPUT_PULLUP);
            }
        }

        // Check if button is hold
        bool isHold() {
            read();
            return pushed;
        }

        // Return pushed duration
        unsigned long holdDuration() {
            if (pushedTimestamp == 0)
                return 0;
            else
                return millis() - pushedTimestamp;
        }

        // Check if button is clicked
        bool isClicked() {
            read();
            if (!pushed) {
                clickReturned = false;
                return false;
            }
            else if (pushed && !clickReturned) {
                clickReturned = true;
                return true;
            }
            return false;
        }
};