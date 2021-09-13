/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

enum IgnitionStatus { ignitionOff, ignitionStandby, engineStarting, engineRunning, engineStopping };
enum LightStatus { lightsOff, parkLights, lowBeam, highBeam };
enum IndicatorStatus { indicatorsOff, turnLeft, turnRight, hazard };
enum HornStatus { hornOff, hornInitiating, hornOn };

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
