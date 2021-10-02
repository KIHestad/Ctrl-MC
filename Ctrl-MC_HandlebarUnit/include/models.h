/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// System enums
enum TemperatureDefaultType { tempCelcius, tempFarenheit };
enum PinType {pinDigital, pinAnalog };
enum ChecBoxSelected { checkBoxLeft, checkBoxMid, checkBoxRight};
enum ImagePosition {imgPosMenuCenter, imgPosCenter, imgPos2Left, imgPos2Right, imgPos3Left, imgPos3RightTop, imgPos3RightBottom};

// Bike main status
enum BikeStatusIgnition { ignOff, ignPasswordMode, ignOn };
enum BikeStatusEngine { engStopped, engStartMotorEngaged, engUnknownStatus, engRunning };
enum BikeStatusLights { lightsOff, lightsPark, lightsMain };
enum BikeStatusLightsHiLo { lightsLow, lightsHigh };
enum BikeStatusIndicator { indOff, indLeft, indRight, indHazard };

class BikeStatus {
    public:

        bool debugMode; // Flag for running in debug mode
        bool communicationOK; // Flag that indicates that communitcation to relay module is OK
        unsigned long communicationLastPing; // Last successful ping to relay, for triggering new ping after ping interval set in settings
        unsigned long ignitionOnTimestamp; // Set timestamp for when iginition was last turned on, used for stopwatch
        
        uint8_t displayMenyScrollSelector; // The current display menu selected by NEXT MENU ITEM button, counts upwards for each menu on button press
        uint8_t displayMenySubLevelSelector; // The current submenu selected
        unsigned long displayMenuTimestamp; // The timestamp for last display menu next or select action is selected, used for determing when to trigger goto status page
        unsigned long displayGotoStatusPageTimestamp; // Timestamp for showing progressbar when goto status page was triggered
        bool displayGotoStatusPageProgress; // Flag set to true when progress goto status page is running 
        unsigned long displayStatusTextRemoveTimeStamp; // Set timestamp to the future for auto remove status text
        unsigned long displayMenyShowRunningStopWatch; // Set to actual time [millis()] to update time each second
        
        unsigned long indicatorLastBlinkTimestamp; // Timestamp for controller to know when to blink next time
        bool indicatorBlinkOn; // Flag to know to turn on or off turn signal, toggles for each ite
        bool neutral; // Flag set if bike gears in neutral position

        BikeStatusIgnition ignition;
        BikeStatusEngine engine;
        BikeStatusLights lights;
        BikeStatusLightsHiLo lightHilo;
        BikeStatusIndicator indicator;
};

// Used to define pins allocation for inputs and custom features for button inputs
class Input {
    public:
        bool enabled; // If input is to be used or not
        uint8_t pin; // Arduino borad pin
        PinType pinType; // Digital is best, alternative analoge with valuerange
        uint8_t analogValueExpected; // If analog pin, the expected value returned has to be set
        unsigned long activateOnLongPress = 0; // Number of milliseconds, 0 = long not activated

};

// Model used to retrive serial communication data
class SerialCommunicationDataReceived {
    public:
        bool success;
        uint8_t code;
        uint8_t value;
};

// Model for menu items
class MenuItem {
    public:
        uint8_t id; // Identifier used by code to know what to do
        String displayName; // Name of menu item to show on display
};
