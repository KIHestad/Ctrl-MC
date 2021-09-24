class ControlDisplayMenu {

    private:
        int8_t menuScrollSelector = -1; // No menu item selected by default, counts upwards for each menu next button press
        bool btnMenuNextHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        unsigned long showRunningStopWatch = 0; // Set to actual time [millis()] to update time each second
    public:

        void checkForAction() {
            if (showRunningStopWatch > 0 && millis() > showRunningStopWatch + 1000) {
                displayStopWatchTime();
            }
            if (INPUT_MENU_NEXT.enabled)
            {
                bool btnMenuNextPressed = readInput(INPUT_MENU_NEXT);
                if (btnMenuNextHold && !btnMenuNextPressed)
                {
                    // Release
                    btnMenuNextHold = false;
                }
                else if (btnMenuNextPressed && !btnMenuNextHold)
                {
                    // Button pressed, set as hold until detected release
                    btnMenuNextHold = true;
                    // Goto next menu, 0 = first menu item
                    menuScrollSelector = menuScrollSelector + 1;
                    showRunningStopWatch = 0;
                    if (menuScrollSelector >= MENUS_AVAILABLE_LENGTH) {
                        // TODO - goto status screen
                        display.clearDisplay();
                        display.display();
                        menuScrollSelector = -1;
                    }
                    else {
                        // Select the menu according to config
                        MenuItem menuSelected = MENUS_AVAILABLE[menuScrollSelector];
                        // Prepare display content
                        Image image = Image();
                        display.clearDisplay();
                        controlDisplay.statusTextShow(menuSelected.displayName);
                        // Show next menu now
                        if (menuSelected.id == 1) {
                            // Ignition
                            image.unlocked();
                        }
                        else if (menuSelected.id == 2) {
                            // Stopwatch
                            image.stopwatch();
                            displayStopWatchTime();
                            showRunningStopWatch = millis();
                        }
                        else if (menuSelected.id == 3) {
                            // Temp Outside
                            image.temperature();
                        }
                        else if (menuSelected.id == 4) {
                            // Temp System
                            image.temperature();
                        }
                        else if (menuSelected.id == 5) {
                            // Lights
                            image.lightsOff();
                        }
                    }
                    delay(250); // avoid dirty signal
                }
            }
        }

        void displayStopWatchTime() {
            // Stopwatch, get time
            unsigned long allSeconds = millis() / 1000;
            int h = allSeconds / 3600;
            int secsRemaining = allSeconds % 3600;
            int m = secsRemaining / 60;
            int s = secsRemaining % 60;
            // Format time
            String timeFormatted = String();
            timeFormatted = h < 10 ? "0" : "";
            timeFormatted += h;
            timeFormatted += m < 10 ? ":0" : ":";
            timeFormatted += m;
            timeFormatted += s < 10 ? ":0" : ":";
            timeFormatted += s;
            // Display 
            int x = 32;
            int y = (DISPLAY_SCREEN_HEIGHT / 2) - (DISPLAY_TEXT_CHAR_HEIGHT);
            // Clear first?
            display.fillRect(x,y,DISPLAY_SCREEN_WIDTH, DISPLAY_TEXT_CHAR_HEIGHT * 2, SSD1306_BLACK);
            display.setCursor(x, y);
            display.setTextSize(DISPLAY_TEXT_SIZE + 1); // Larger font
            display.println(timeFormatted);
            display.display();
            display.setTextSize(DISPLAY_TEXT_SIZE);
            
        }

};