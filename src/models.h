/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */
enum IgnitionStatus { ignitionOff, ignitionPasswordStart, ignitionStandby, engineStarting, engineRunning, engineStopping };
enum LightStatus { lightsOff, parkLights, lowBeam, highBeam };
enum IndicatorStatus { indicatorsOff, turnLeft, turnRight, hazard };
enum HornStatus { hornOff, hornInitiating, hornOn };
enum PinType {analogPin, digitalPin};

// Parameters for inputs on the arduino
class Input {
    public:
        int pin;
        String name;
        PinType pinType;
        int expectedValue;
        
};

// Return values for button read
class ButtonStatus {
    public:
        bool enabled = false;
        bool pressed = false;
        int value = 0;
        long timeStamp;
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


