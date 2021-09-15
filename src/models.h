/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */
enum IgnitionStatus { ignitionOff, ignitionPasswordStart, ignitionStandby, engineStarting, engineRunning, engineStopping };
enum LightStatus { lightsOff, parkLights, lowBeam, highBeam };
enum IndicatorStatus { indicatorsOff, turnLeft, turnRight, hazard };
enum HornStatus { hornOff, hornInitiating, hornOn };
enum PinType { digitalPin, analogPin };

class InputGroup {
    public:
        bool enabled;
        String shortName;
        String displayName;
};


// Parameters for inputs on the arduino
class Input {
    public:
        bool enabled; // Set true if input is to be used, false otherwise
        int pin; // What pin on the Ardiono it is connected to
        PinType pinType; 
        int expectedValue; // For analogRead only when used for button, what value is expected to be received to identify 
        String shortName; // Used for testing/debugging to write to terminal window name of the input
        String displayName; // Used for display to show information about input
};

// Buttons initial and previous status, used to avoid dirty signal from button or accidently double-click 
class ButtonStatusHistory {
    public:
        long lastPressTimestamp = millis() - 1000;
        bool pressed = false;
        int value = 0;
};

// Return values for button read
class ButtonStatus {
    public:
        bool pressed = false;
        int value = 0;
        Input input;
};

// Bike main status
class BikeStatus {
    public:
        IgnitionStatus ignitionStatus = ignitionOff;
        LightStatus lights = lightsOff;
        IndicatorStatus indicators = indicatorsOff;
        HornStatus horn = hornOff; 
};


