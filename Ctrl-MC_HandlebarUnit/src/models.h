/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// Bike main status
enum BikeStatusIgnition { ignOff, ignPasswordMode, ignOn };
enum BikeStatusEngine { engStopped, engRunning };
enum BikeStatusLights { lightsOff, lightsPark, lightsMain };
class BikeStatus {
    public:

        bool debugMode; // Flag for running in debug mode
        unsigned long displayOffTimestamp; // Timestamp for when display off was initiated
        unsigned long displayOffWaitTime; // Number of milliseconds to run shutdown with progressbar befor display is turned off
        bool displayOffProgressRunning; // Flag set to true when progress is running 
        unsigned long displayStatusTextRemoveTimeStamp; // Set timestamp to the future for auto remove status text
        bool communicationOK; // Flag that indicates that communitcation to relay module is OK
        unsigned long communicationLastPing; // Last successful ping to relay, for triggering new ping after ping interval set in settings
        BikeStatusIgnition ignition;
        BikeStatusEngine engine;
        BikeStatusLights lights;

        // Constructor
        void init() {
            debugMode = false;
            displayOffTimestamp = 0;
            displayOffWaitTime = 6000;
            displayOffProgressRunning = false;
            displayStatusTextRemoveTimeStamp = 0;
            communicationOK = false;
            communicationLastPing = millis();
            ignition = ignOff;
            engine = engStopped;
            lights = lightsOff;
        }
};

// Used to define pins allocation for inputs and custom features for button inputs
class Input {
    public:
        bool enabled; // If input is to be used or not
        uint8_t pin; // Arduino borad pin
        unsigned long activateOnLongPress = 0; // Number of milliseconds, 0 = long not activated
};

// Model used to retrive serial communication data
class SerialCommunicationDataReceived {
    public:
        bool dataRead;
        bool success;
        uint8_t codeGroup;
        uint8_t code;
};

