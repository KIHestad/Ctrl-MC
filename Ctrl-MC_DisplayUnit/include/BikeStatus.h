/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

enum BikeStatusIgnition { ignOff, ignPasswordMode, ignTestButtonsMode, ignOn };
enum BikeStatusEngine { engStopped, engStartMotorEngaged, engUnknownStatus, engRunning };
enum BikeStatusLights { lightsOff, lightsPark, lightsMain };
enum BikeStatusLightsHiLo { lightsLow, lightsHigh };
enum BikeStatusIndicator { indOff, indLeft, indRight, indHazard };

class BikeStatus {
    public:

        bool debugMode; // Flag for running in debug mode
        bool handshakeOK; // Flag that indicates that communitcation to relay module is OK
        unsigned long handshakeNextTimestamp; // Timestamp for when next handshake should be triggered
        
        unsigned long ignitionOnTimestamp; // Set timestamp for when iginition was last turned on, used for stopwatch
        
        uint8_t displayMenuPageSelected; // The current page to show on display, selected by NEXT MENU ITEM button, 0=show status page
        uint8_t displayMenuSubPageSelected; // The current submenu selected
        unsigned long displayMenuTimeoutTimestamp; // The timestamp in the future for set after each menu action to trigger automatically return to status page
        unsigned long displayMenuShowRunningStopWatch; // Set to actual time [millis()] to update time each second
        unsigned long displayGotoStatusPageTimestamp; // Timestamp for showing progressbar when goto status page was triggered
        bool displayGotoStatusPageProgress; // Flag set to true when progress goto status page is running 
        
        unsigned long indicatorNextBlinkTimestamp; // Timestamp for controller to know when to blink next time
        bool indicatorBlinkOn; // Flag to know to turn on or off turn signal, toggles for each ite
        bool hornActive; // Flag set to true if signal horn is on
        bool lightBrakeActive; // Flag set to true if brake lever is initiated
        bool neutral; // Flag set if bike gears in neutral position
        bool lightHighBeamFlash; // Flag set if hi/lo button is used as passing switch, set true when hi/lo button is pressed and holded for flashing with high beam

        BikeStatusIgnition ignition;
        BikeStatusEngine engine;
        BikeStatusLights lights;
        BikeStatusLightsHiLo lightHilo;
        BikeStatusIndicator indicator;

        BikeStatus() {
            this->debugMode = false;
            this->handshakeOK = true;
            this->handshakeNextTimestamp = millis();
            this->ignitionOnTimestamp = millis();
            
            this->displayMenuPageSelected = 0; // No display menu selected, show status page as default
            this->displayMenuSubPageSelected = 0; // No sub menu level selected as default
            this->displayMenuTimeoutTimestamp = 0; 
            this->displayMenuShowRunningStopWatch = 0;
            this->displayGotoStatusPageTimestamp = 0;
            this->displayGotoStatusPageProgress = false;
            
            this->ignition = BikeStatusIgnition::ignOff;
            this->neutral = true;
            this->engine = BikeStatusEngine::engStopped;
            this->lights = BikeStatusLights::lightsOff;
            this->lightHilo = BikeStatusLightsHiLo::lightsLow;
            this->lightHighBeamFlash = false;
            this->hornActive = false;
            this->lightBrakeActive = false;
            this->indicator = BikeStatusIndicator::indOff;
        }
};