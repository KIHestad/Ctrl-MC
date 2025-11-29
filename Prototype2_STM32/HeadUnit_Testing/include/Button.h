#ifndef Button_h
#define Button_h

class Button {

private:
    // Input pin for the button
    uint8_t _pin;

    // State tracking flags
    bool _isPressing = false; 
    bool _isLongPressing = false;
    bool _shortPressTrigger = false;
    bool _longPressTrigger = false;
    bool _longPressTriggerExecuted = false;

    // State variables
    int _currentState = HIGH; // current button reading, default = button not pressed
    int _lastState = HIGH; // save reading to compare on next iteration, default = button not pressed

    // Timing variables
    unsigned long _lastDebounceTime = 0; // To track debounce timing
    unsigned long _pressStartTime = 0; // To calculate long press duration

    // Constants
    static const unsigned long DEBOUNCE_DELAY = 50;
    static const unsigned long LONG_PRESS_TIME = 1000;


public:
    // Constructor: Initializes the button on the specified pin.
    Button(uint8_t pin) {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP); // Use internal pull-up resistor
    }

    // Read the button state and update internal flags.
    void read() {
        unsigned long currentTime = millis();
        int reading = digitalRead(_pin);
        // Debounce logic: reset timer if state has changed to detect if unstable
        if (reading != _lastState) {
            _lastDebounceTime = currentTime;
        }
        // If the reading has been stable for longer than the debounce delay
        if ((currentTime - _lastDebounceTime) > DEBOUNCE_DELAY) {
            // The reading is stable, check If state has changed fram unpressed to pressed or vice versa
            if (reading != _currentState) {
                _currentState = reading;
                // Reading stable, state change detected, check if pressed or released
                if (_currentState == LOW) { 
                    // Button was just pressed
                    _pressStartTime = currentTime;
                    _isPressing = true;
                    _isLongPressing = false;                    
                } 
                else { 
                    // Button was just released
                    if (_isLongPressing) {
                        _longPressTrigger = true; // It was a long press
                    } else if (_isPressing) {
                        _shortPressTrigger = true; // It was a short press
                    }
                    _isPressing = false;
                    _isLongPressing = false;
                }
            }
            // Same state as last check, consider if long press happened because button is being held down long enough
            // Ignore this check if long press trigger event has happened, _longPressTriggeredWaitForRelease is then set to true
            else if (_isPressing && !_isLongPressing && !_longPressTriggerExecuted) {
                if ((currentTime - _pressStartTime) > LONG_PRESS_TIME) {
                    _isPressing = false;
                    _isLongPressing = true;
                }
            }
        }
        // Remember the reading for next time
        _lastState = reading;
    }

    // Returns true ONCE after a short press is completed (on release).
    bool isPressed() {
        if (_shortPressTrigger) {
            _shortPressTrigger = false;
            return true;
        }
        return false;
    }

    // Returns true ONCE after a long press is completed (on release).
    bool isLongPressed() {
        if (_longPressTrigger) {
            _longPressTrigger = false;
            return true;
        }
        return false;
    }

    void cancelLongPressingState() {
        _isLongPressing = false;
        _longPressTrigger = false;        
        _longPressTriggerExecuted = false;
    }

    // Returns true continuously while the button is held in a long press state.
    bool isLongPressing() {
        return _isLongPressing;
    }

    // Returns the duration (in ms) the button has been held in a long press state.
    unsigned long getLongPressDuration() {
        if (_isLongPressing && !_longPressTriggerExecuted) {
            // Returns time since the press first started
            return millis() - _pressStartTime;
        }
        return 0;
    }

    // Returns true if any button event (press or long press) is happening.
    bool eventHappening() {
        return _isPressing || (_isLongPressing && !_longPressTriggerExecuted);
    }   


};

#endif