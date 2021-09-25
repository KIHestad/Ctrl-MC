class ControlDisplayMenu {

    private:
        Image image = Image();
        bool btnMenuNextHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        bool btnMenuSelectHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        
        // Ligths parameters
        BikeStatusLights lightsParkSelectNext = lightsMain; // Deafult go to Main lights from park

    public:
        
        void checkForMenuAction() {
            // Check for auto shut down
            if (bikeStatus.displayMenuTimestamp != 0 && millis() > bikeStatus.displayMenuTimestamp) {
                bikeStatus.displayMenuTimestamp = 0;
                controlDisplay.displayOffInititate();
            }
            // If stopwatch is selected, show as running
            if (bikeStatus.displayMenyShowRunningStopWatch > 0 && millis() > bikeStatus.displayMenyShowRunningStopWatch + 1000) {
                displayStopWatchTime();
            }
            // Check if next menu button is pressed
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
                    // Timestamp for display menu auto shutdown
                    bikeStatus.displayMenuTimestamp = millis() + (MENU_SHUTDOWN_WAIT * 1000);
                    // Check if shutdown is in progress, cancel and show same menu if relevant
                    if (bikeStatus.displayOffProgressRunning) {
                        // Stay on same menu, just cancel display off
                        controlDisplay.displayOffRemove();
                    }
                    else {
                        // Goto next menu, 0 = first menu item
                        bikeStatus.displayMenyScrollSelector = bikeStatus.displayMenyScrollSelector + 1;
                    }
                    bikeStatus.displayMenyShowRunningStopWatch = 0;
                    display.clearDisplay();
                    if (bikeStatus.displayMenyScrollSelector >= MENUS_AVAILABLE_LENGTH) {
                        // TODO - goto status screen
                        display.display();
                        bikeStatus.displayMenyScrollSelector = -1;
                    }
                    else {
                        // Select the menu according to config
                        MenuItem menuSelected = MENUS_AVAILABLE[bikeStatus.displayMenyScrollSelector];
                        // Show next menu now
                        if (menuSelected.id == 1) {
                            // Ignition
                            image.ignitionLockFrame();
                            image.ignitionLockKeyHoleUnlocked();
                            display.display();
                            controlDisplay.statusTextShow(menuSelected.displayName);
                        }
                        else if (menuSelected.id == 2) {
                            // Stopwatch
                            image.stopwatch();
                            displayStopWatchTime();
                            bikeStatus.displayMenyShowRunningStopWatch = millis();
                            controlDisplay.statusTextShow(menuSelected.displayName);
                        }
                        else if (menuSelected.id == 3) {
                            // Temp Outside
                            image.temperature();
                            controlDisplay.statusTextShow(menuSelected.displayName);
                        }
                        else if (menuSelected.id == 4) {
                            // Temp System
                            image.temperature();
                            controlDisplay.statusTextShow(menuSelected.displayName);
                        }
                        else if (menuSelected.id == 5) {
                            // Lights
                            showSelectedLights();
                        }
                    }
                    delay(250); // avoid dirty signal
                }
            }
            // Check if select menu item button is pressed
            if (INPUT_MENU_SELECT.enabled)
            {
                bool btnMenuSelectPressed = readInput(INPUT_MENU_SELECT);
                if (btnMenuSelectHold && !btnMenuSelectPressed)
                {
                    // Release
                    btnMenuSelectHold = false;
                }
                else if (btnMenuSelectPressed && !btnMenuSelectHold)
                {
                    // Button pressed, set as hold until detected release
                    btnMenuSelectHold = true;
                    // Timestamp for display menu auto shutdown
                    bikeStatus.displayMenuTimestamp = millis() + (MENU_SHUTDOWN_WAIT * 1000);
                    // Check if shutdown is in progress, cancel it and continue if relevant
                    if (bikeStatus.displayOffProgressRunning) {
                        // Stay on same menu, cancel display off and ignore action
                        controlDisplay.displayOffRemove();
                    }
                    else {
                        // Select the menu according to config
                        MenuItem menuSelected = MENUS_AVAILABLE[bikeStatus.displayMenyScrollSelector];
                        // Show next menu now
                        if (menuSelected.id == 1) {
                            // Ignition actions
                        }
                        else if (menuSelected.id == 2) {
                            // Stopwatch actions
                        }
                        else if (menuSelected.id == 3) {
                            // Temp Outside actions
                        }
                        else if (menuSelected.id == 4) {
                            // Temp System actions
                        }
                        else if (menuSelected.id == 5) {
                            display.clearDisplay();
                            // Lights actions - toggle off, park, on
                            if (bikeStatus.lights == lightsOff) {
                                // Current: Off -> Goto: Park
                                bikeStatus.lights = lightsPark;
                                lightsParkSelectNext = lightsMain;
                            }
                            else if (bikeStatus.lights == lightsPark) {
                                // Current: Park -> Goto: Off or Main
                                bikeStatus.lights = lightsParkSelectNext;
                            }
                            else if (bikeStatus.lights == lightsMain) {
                                // Current: Main -> Goto: Park
                                bikeStatus.lights = lightsPark;
                                lightsParkSelectNext = lightsOff;
                            }
                            showSelectedLights();
                            // TODO: Turn on relays
                        }
                    }
                    delay(250); // avoid dirty signal
                }
            }

        }

        void showSelectedLights() {
            if (bikeStatus.lights == lightsOff) {
                image.menuLightsOff();
                controlDisplay.statusTextShow("LIGHTS OFF");
            }
            else if (bikeStatus.lights == lightsPark) {
                image.menuLightsOff();
                image.menuLightsPark();
                controlDisplay.statusTextShow("PARKING LIGHTS");
            }
            else if (bikeStatus.lights == lightsMain) {
                image.menuLightsOff();
                if (bikeStatus.lightHilo == lightsLow) { 
                    image.menuLightsLow();
                    controlDisplay.statusTextShow("LOW BEAM");
                }
                else if (bikeStatus.lightHilo == lightsHigh) {
                    image.menuLightsHigh();
                    controlDisplay.statusTextShow("HIGH BEAM");
                }
            }
        }

    private:

        
        
        void displayStopWatchTime() {
            // Stopwatch, get time
            unsigned long allSeconds = (millis() - bikeStatus.ignitionOnTimestamp ) / 1000;
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