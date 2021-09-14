/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

enum IgnitionStatus { ignitionOff, ignitionStandby, engineStarting, engineRunning, engineStopping };
enum LightStatus { lightsOff, parkLights, lowBeam, highBeam };
enum IndicatorStatus { indicatorsOff, turnLeft, turnRight, hazard };
enum HornStatus { hornOff, hornInitiating, hornOn };
enum PinType { digitalPin, analogPin };

class ButtonStatusRead {
    public:
        bool pressed = false;
        long timeStamp;
};

class ButtonStatus {
    public:
        bool pressed = false;
        long pressedTime;
        long releasedTime;
};

class BikeStatus {
    public:
        IgnitionStatus ignitionStatus = ignitionStandby;
        LightStatus lights = lightsOff;
        IndicatorStatus indicators = indicatorsOff;
        HornStatus horn = hornOff; 
};
