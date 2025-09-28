#ifndef Data_H
#define Data_H

class Data {
    
    public:

        // For debugging
        unsigned long debugLong = 0;
        
        // Display page properties
        const unsigned int displayPagesTotal = 5; // total number of display pages
        unsigned int displayPageSelected = 0; // current display page, 0 = main page
        unsigned int displayPageSelectedLast = 1; // last display page, to detect page change
        unsigned long displayMenuNameSetMs = 0; // time in milliseconds when menu name was set, used to fade out menu name after some time
        const unsigned long displayMenuNameTimoutMs = 5000; // time in milliseconds to show menu name after page change
        unsigned long displayPageSelectedTimeStamp = 0; // timestamp of last display page change, used to fade out page name after some time
        const unsigned long displayPageSelectedShowTimeMs = 5000; // time in milliseconds to show page name after page change
        bool displayUpdateNeeded = true; // Flag to indicate if display needs immediate update, not waiting for regular interval
        int displayCountdown = 0; // Set a value to show the number as a countdown on display, used for reset button
        bool backgroundRedraw = true; // Flag to indicate if gauges background needs to be redrawn, on startup and when changing some pages
    
        // Speed calcutaions
        const float wheelCircumference = 220.0; // Wheel circumference in cm
        const float cmMicrosToKmh = 36000.0;
        const unsigned long zeroSpeedTimeoutMs = 2000; // 2000 = 2 seconds, if no pulse is received for this duration (in milliseconds), set speed to 0.
        float currentSpeed = 0.0; // in km/h, calculated from hall sensor pulses
        int currentSpeedDisplayed = -1; // Last speed value displayed, to check if speed changed and needs update on display
        
        // Main property for reading time spent 
        unsigned long currentMs; // current time in milliseconds set in loop()
        unsigned long displayUpdatePreviousMs = 0; // previous time in milliseconds
        const unsigned long displayUpdateIntervalMs = 250; // interval in milliseconds for regular display update, also used to check if display needs update

        // Properties for hall sensor reading using interrupt
        static const int pulseReadingsCount = 10;
        volatile unsigned long pulseReadings[pulseReadingsCount] = {0};
        volatile int currentPulseIndex = 0;
        volatile unsigned long lastPulseTimeMicros = 0; // Time of last pulse in microseconds, used to calculate pulseIntervalMicros on next pulse
        bool wheelRotaionDetected = false; // Set when weel rotation is detected, reset when processed, used to avoid setting speed if no new pulse is received
        unsigned int wheelRotations = 0; // Count of wheel rotations, for debugging
        unsigned int currentWheelRotations = 0; // Count of wheel rotations currently processed
        
        // Trip counters for current session, trip and totals, and for output to display
        float sessionCounter = 0.0; // meters for this session only
        float sessionCounterToUpdateFlash = 0.0; // counter to track how much to update flash memory since last save
        float totalCounter = 0.0; // in kilometers, to be set from storage
        float tripCounter = 0.0; // in kilometers, possible to reset, to be set from storage

        // Fuel level 
        const float fuelAvgConsumption = 6.5; // in liters per 100 km
        const float fuelTankCapacity = 19.0; // in liters, tank capacity
        const float fuelTankReserve = 3.0; // in liters, tank reserve level
        float fuelTripCounter = 0.0; // in km, what distance was driven since last refuel, to be read from storage
        float fuelLevel = 0.0; // in liters, how much fuel when fuelTripCounter was reset, to be read from storege
        float fuelLevelDisplayed = -1.0; // Last fuel level value displayed, to check if fuel level changed and needs update on display
        
        // Humidity and temperature
        int temperatureDisplayed = -100.0; // in degrees Celsius, last read temperature value, to check if changed and needs update on display
        int humidityDisplayed = -1.0; // in percent, last read humidity value, to check if changed and needs update on display
        float tempHumUpdateIntervalMs = 15000.0; // interval in milliseconds to read temperature and humidity, DHT22 sensor max is 0.5Hz = every 2 seconds
        float tempHumUpdatePreviousMs = 0.0; // previous time in milliseconds when temperature and humidity was read

        // Engine RPM simulation for demo purposes
        unsigned int engineRpmMax = 11000;
        unsigned int engineRpmWarning = 7500;
        unsigned int engineRpmDanger = 8500;
        unsigned int engineRpm = 0; // Current RPM value, to be set from sensor in future
        unsigned int engineRpmDisplayed = -1; // Last RPM value displayed, to check if RPM changed and needs update on display
        int engineRpmSimulation[20] = {
            500, 550, 520, 500, 510, 500, 510, 500, 500, 500, 
            490, 480, 490, 500, 500, 500, 510, 500, 510, 500};
        int engineRpmSimulationIndex = 0;

        // Set initial values 
        void init(Storage::Data storageData) {
            // Get from storage
            totalCounter = storageData.totalCounter.value;
            tripCounter = storageData.tripCounter.value;
            fuelTripCounter = storageData.fuelTripCounter.value;
            // calculate fuel level from last refuel and fuel consumption
            if (fuelTripCounter > 0) {
                float fuelUsed = (fuelAvgConsumption / 100.0) * fuelTripCounter; // in liters
                fuelLevel = storageData.fuelLevelWhenRefueled.value - fuelUsed;
                if (fuelLevel < 0) fuelLevel = 0.0;
                if (fuelLevel > fuelTankCapacity) fuelLevel = fuelTankCapacity;
            } 
            else {
                fuelLevel = storageData.fuelLevelWhenRefueled.value;
            }
            
        };

};

#endif