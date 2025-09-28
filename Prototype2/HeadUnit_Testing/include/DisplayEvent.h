#ifndef DisplayEvent_h
#define DisplayEvent_h


class DisplayEvent {

public:

    // Decide if display update is needed based on data changes or time interval
    bool displayNeedsUpdate(Data data) {
        return (data.currentMs - data.displayUpdatePreviousMs > data.displayUpdateIntervalMs) || data.displayUpdateNeeded;
    }

    // Handle output to display based on current data and button state
    void output(Data& data, Button& button, DHT dht) {
        
        // Draw background if needed
        if (data.backgroundRedraw) {
            display.background();
            data.backgroundRedraw = false;
        }

        // Section 1 : Display speed
        int speedToDisplay = round(data.currentSpeed);
        if (speedToDisplay != data.currentSpeedDisplayed) {
            display.speed(speedToDisplay);
            data.currentSpeedDisplayed = speedToDisplay;
        }

        // Section 2 : Display rpm
        if (data.engineRpm != data.engineRpmDisplayed) { 
            display.rpm(data.engineRpm);
            data.engineRpmDisplayed = data.engineRpm;
        }

        // Section 3 : Background based on current page
        bool forceUpdatePage = false;
        if (data.displayPageSelected != data.displayPageSelectedLast) {
            // Page changed, clear content area
            display.clearPageArea();
            // Deal with the menu depending on the page
            if (data.displayPageSelected == 0) {         
                display.clearMenuArea(); // Need to redraw menu area because coming from Elefant page
                display.backgroundMenu();
            }
            if (data.displayPageSelected != 4) { // Show menu pager if not elefant page
                display.backgroundMenu();
                display.menu(data.displayPageSelected, false);
            }
            else  {
                display.clearMenuArea(); // Clear menu area when going to elefant page
            }
            // Add static background elements if needed
            switch (data.displayPageSelected) {
                case 0: display.backgroundFuel(); display.menuName("FUEL"); break;
                case 1: display.menuName("TEMP/HUM"); break;
                case 2: display.menuName("TIMER"); break;
                case 3: display.menuName("TRIP/TOT"); break;                
            }
            // Set timestamp for menu name write
            data.displayMenuNameSetMs = data.currentMs;
            // Remember last page
            data.displayPageSelectedLast = data.displayPageSelected;
            // Force update of page content
            forceUpdatePage = true;
        }
        else if (data.displayMenuNameSetMs > 0 && (data.currentMs - data.displayMenuNameSetMs) > data.displayMenuNameTimoutMs) {
            // Clear menu name and pager after some time
            display.clearMenuArea();
            data.displayMenuNameSetMs = 0; // reset to avoid multiple clears
        }

        // Section 3 : Content based on current page
        switch (data.displayPageSelected) {
            case 0: {
                // Fuel level, show data
                if (forceUpdatePage || data.fuelLevel != data.fuelLevelDisplayed) {
                    display.fuel(data.fuelLevel);
                    data.fuelLevelDisplayed = data.fuelLevel;
                }                
                // Display countdown to reset fuel level
                if (data.displayCountdown > 0) {
                    float fuelLevelPercentage = data.fuelLevel / data.fuelTankCapacity;
                    char countdownString[20];
                    if (fuelLevelPercentage > 0.6)
                        sprintf(countdownString, "HALF %d", data.displayCountdown);
                    else if ((fuelLevelPercentage*data.fuelTankCapacity) > (data.fuelTankReserve * 1.1))
                        sprintf(countdownString, "RESERVE %d", data.displayCountdown);
                    else
                        sprintf(countdownString, "FULL %d", data.displayCountdown);
                    display.menuName(countdownString);
                }
                break;
            }
            case 1: {
                // Temperature and humidity, not read to often, DHT22 max is 0.5Hz = every 2 seconds
                if (forceUpdatePage || data.tempHumUpdatePreviousMs == 0 || (data.currentMs - data.tempHumUpdatePreviousMs) > data.tempHumUpdateIntervalMs) {
                    data.tempHumUpdatePreviousMs = data.currentMs;
                    int temperature = (int)round(dht.readTemperature()); 
                    int humidity = (int)round(dht.readHumidity()); 
                    int humidityFarenheit = (int)round(dht.convertCtoF(temperature));
                    if (forceUpdatePage || humidity != data.humidityDisplayed || temperature != data.temperatureDisplayed) {
                        char tempStr[10], humStr[10];
                        sprintf(tempStr, "%dC  %dF", temperature, humidityFarenheit);
                        sprintf(humStr, "%d", humidity);
                        strcat(humStr, "%");
                        display.rowNum(1, tempStr);
                        display.rowNum(2, humStr);
                        data.humidityDisplayed = humidity;
                        data.temperatureDisplayed = temperature;
                    }
                }
                break;
            }
            case 2: { 
                // Session info, distance travelled 
                char sessionString[9];
                if (data.sessionCounter < 1000) {
                    sprintf(sessionString, "%dm", (int)data.sessionCounter);
                } else {
                    sprintf(sessionString, "%.2fkm", data.sessionCounter / 1000.0);
                }
                display.rowNum(1, sessionString);
                // Time spent since startup
                int hours = data.currentMs / 3600000;
                int minutes = (data.currentMs % 3600000) / 60000;
                int seconds = (data.currentMs % 60000) / 1000;
                char timeString[9]; 
                sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);
                display.rowTime(2, timeString);
                break;
            }
            case 3: {
                // Trip counter
                char str[9]; 
                sprintf(str, "%.1fkm", data.tripCounter / 1000);
                display.rowNum(1, str);
                // Total counter
                sprintf(str, "%dkm", (int)round(data.totalCounter));
                display.rowNum(2, str);
                // Display countdown to reset trip
                if (data.displayCountdown > 0) {
                    char countdownString[9];
                    sprintf(countdownString, "RESET %d", data.displayCountdown);
                    display.menuName(countdownString);
                }
                break;
            }
            default:
                display.drawElefant();
                break;
        }

        // Send buffer to display
        display.outputNow();
        // Update last update time and reset update flag
        data.displayUpdatePreviousMs = data.currentMs;
        data.displayUpdateNeeded = false;
    };
};

#endif
