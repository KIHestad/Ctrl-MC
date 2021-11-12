class ControlDisplayMenu {

    private:
        Image image = Image();
        bool btnMenuNextHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        bool btnMenuSelectHold = false; // Set to true when pressed until released to avoid continuosly presses to be detected
        ChecBoxSelected checkBoxSelected; // Indicates what checkbox is currently selected if shown in menu sub level
        // Ligths parameters
        BikeStatusLights lightsParkSelectNext = lightsMain; // Deafult go to Main lights from park

    public:
        
        void checkForMenuAction() {
            // Check for auto shut down
            if (bikeStatus.displayMenuTimeoutTimestamp > 0 && millis() > bikeStatus.displayMenuTimeoutTimestamp) {
                bikeStatus.displayMenuTimeoutTimestamp = 0;
                controlDisplay.gotoStatusPageInitiate();
            }
            // If stopwatch is selected, show as running
            if (bikeStatus.displayMenyShowRunningStopWatch > 0 && millis() > bikeStatus.displayMenyShowRunningStopWatch + 1000) {
                displayStopWatchTime();
            }
            
            // Check if next menu button is pressed - PERFORM GOTO NEXT MENU ITEM
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
                    bikeStatus.displayMenuTimeoutTimestamp = millis() + (MENU_SHUTDOWN_WAIT * 1000);
                    // Check if progress for goto status page is in progress, cancel and show same menu if relevant
                    if (bikeStatus.displayGotoStatusPageProgress) {
                        // Stay on same menu, cancel goto status page
                        controlDisplay.gotoStatusPageCancel();
                    }
                    else {
                        // Goto next menu if not sub menu is selected, 0 = no menu currently selected, 1 = first menu item
                        if (bikeStatus.displayMenySubPageSelected == 0) {
                            bikeStatus.displayMenyPageSelected++;
                            display.clearDisplay();
                        }
                    }
                    bikeStatus.displayMenyShowRunningStopWatch = 0;
                    if (bikeStatus.displayMenyPageSelected >= MENUS_AVAILABLE_LENGTH + 1) {
                        // Goto status screen
                        bikeStatus.displayMenyPageSelected = 0;
                        bikeStatus.displayMenuTimeoutTimestamp = 0;
                        controlDisplay.gotoStatusPageCancel();
                        controlDisplay.refreshStatusPage();
                    }
                    else {
                        // Select the menu according to config
                        MenuItem menuSelected = MENUS_AVAILABLE[bikeStatus.displayMenyPageSelected - 1];
                        // Show menu now
                        if (menuSelected.id == 1) {
                            // Ignition
                            if (bikeStatus.displayMenySubPageSelected == 0)
                            {
                                // No sub level menu selected, show default ingnition onb
                                image.ignOn();
                                controlDisplay.statusTextShow("IGNITION ON");
                                checkBoxSelected = checkBoxRight;
                            }
                            else
                            {
                                // Sub level selected, toggle checkboxes
                                if (checkBoxSelected == checkBoxRight) {
                                    checkBoxSelected = checkBoxLeft;
                                    controlDisplay.statusTextShow("TURN OFF", false);
                                }
                                else if (checkBoxSelected == checkBoxLeft) {
                                    checkBoxSelected = checkBoxRight;
                                    controlDisplay.statusTextShow("IGNITION ON", false);
                                }
                                // Toggle on display
                                image.menuSelectFrameContentInverse(true,true);
                                display.display();
                            }
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
            
            // Check if select menu item button is pressed - PERFORM ACTION
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
                    bikeStatus.displayMenuTimeoutTimestamp = millis() + (MENU_SHUTDOWN_WAIT * 1000);
                    // Check if progress for goto status page is in progress, cancel it and continue if relevant
                    if (bikeStatus.displayGotoStatusPageProgress) {
                        // Stay on same menu, cancel display off and ignore action
                        controlDisplay.gotoStatusPageCancel();
                        display.display();
                    }
                    else {
                        // Select the menu according to config
                        MenuItem menuSelected = MENUS_AVAILABLE[bikeStatus.displayMenyPageSelected - 1];
                        // Show next menu now
                        if (menuSelected.id == 1) {
                            // Ignition actions
                            if (bikeStatus.displayMenySubPageSelected == 0) {
                                // initially show ignition on checkboxes
                                clearGraphicsNotStatusText();
                                image.menuSelectFrame(true,true);
                                image.menuSelectIconOff(true,false);
                                image.menuSelectIconOn(false,true);
                                image.menuSelectFrameContentInverse(false,true);
                                display.display();
                                bikeStatus.displayMenySubPageSelected = 1; // Indicate first level sub menu selected
                            }
                            else if (bikeStatus.displayMenySubPageSelected == 1) {
                                // perform action
                                bikeStatus.displayMenySubPageSelected = 0;
                                if (checkBoxSelected == checkBoxRight) {
                                    // keep on, return to ignition main menu
                                    clearGraphicsNotStatusText();
                                    image.ignOn();
                                    controlDisplay.statusTextShow("IGNITION ON");
                                }
                                else if (checkBoxSelected == checkBoxLeft) {
                                    // turn off
                                    bikeStatus.ignition = ignOff;
                                    bikeStatus.lights = lightsOff;
                                    bikeStatus.lightHilo = lightsLow;
                                    bikeStatus.indicator = indOff;
                                    
                                    bikeStatus.engine = engStopped;
                                    bikeStatus.displayMenyPageSelected = 0;
                                    // TODO - turn off relays
                                    SerialCommunication serialCommunication = SerialCommunication();
                                    Config::RelayUnitOutput output = Config::RelayUnitOutput();
                                    serialCommunication.send(output.turnSignalLeft.pin, 0);
                                    serialCommunication.send(output.turnSignalRight.pin, 0);
                                    // show end screen
                                    image.ignOn();
                                    delay(500);
                                    image.ignOffToOn2();
                                    delay(50);
                                    image.ignOffToOn1();
                                    delay(50);
                                    image.ignOff();
                                    controlDisplay.statusTextShow("IGNITION TURNED OFF");
                                    controlDisplay.gotoStatusPageInitiate();
                                }
                            }
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
                image.lightsOffBig(imgPosMenuCenter);
                controlDisplay.statusTextShow("LIGHTS OFF");
            }
            else if (bikeStatus.lights == lightsPark) {
                image.lightsParkBig(imgPosMenuCenter);
                controlDisplay.statusTextShow("PARKING LIGHTS");
            }
            else if (bikeStatus.lights == lightsMain) {
                if (bikeStatus.lightHilo == lightsLow) { 
                    image.lightsLowBig(imgPosMenuCenter);
                    controlDisplay.statusTextShow("LOW BEAM");
                }
                else if (bikeStatus.lightHilo == lightsHigh) {
                    image.lightsHighBig(imgPosMenuCenter);
                    controlDisplay.statusTextShow("HIGH BEAM");
                }
            }
        }

    private:

        void clearGraphicsNotStatusText() {
            display.fillRect(0, 0, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT-DISPLAY_TEXT_CHAR_HEIGHT, SSD1306_BLACK);
        }

        // Display text on menu select checkboxes, checkbox frame start on y-pos 3, sixe: 50x50, frame border 2px
        void menuSelectCheckboxText(String text, bool left, bool right) {
            uint8_t y = 3 + 35;
            uint8_t textPixLen = text.length() * DISPLAY_TEXT_CHAR_WIDTH;
            if (left) {
                uint8_t x = ((DISPLAY_SCREEN_WIDTH/2)-6-25)-(textPixLen/2);
                display.setCursor(x,y);
                display.println(text);
            }
            if (right) {
                uint8_t x = ((DISPLAY_SCREEN_WIDTH/2)+6+25)-(textPixLen/2);
                display.setCursor(x,y);
                display.println(text);
            }
        }
        
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