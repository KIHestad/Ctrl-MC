class OnBoardLed {
    
    public:
        
        void init() {
            // Onboard LED pin
            Config::RelayUnitOnBoardLed onBoardLed = Config::RelayUnitOnBoardLed();
            if (onBoardLed.config.enabeld) {
                pinMode(onBoardLed.config.pin, OUTPUT);
                digitalWrite(onBoardLed.config.pin, onBoardLed.off);
            }
        }
        
        void blink(size_t count, unsigned long delayInMilliseconds) {
            Config::RelayUnitOnBoardLed onBoardLed = Config::RelayUnitOnBoardLed();
            if (onBoardLed.config.enabeld) {
                for (size_t i = 0; i < count; i++)
                {
                    digitalWrite(onBoardLed.config.pin, onBoardLed.on);
                    delay(delayInMilliseconds);
                    digitalWrite(onBoardLed.config.pin, onBoardLed.on);
                    delay(delayInMilliseconds);
                }
            }
        }
        
        void on() {
            Config::RelayUnitOnBoardLed onBoardLed = Config::RelayUnitOnBoardLed();
            digitalWrite(onBoardLed.config.pin, onBoardLed.on);
        }

        void off() {
            Config::RelayUnitOnBoardLed onBoardLed = Config::RelayUnitOnBoardLed();
            digitalWrite(onBoardLed.config.pin, onBoardLed.off);
        }
};