enum ChecBoxSelected { checkBoxLeft, checkBoxMid, checkBoxRight};

class DisplayMenu {

    private:
        DisplayImage displayImage = DisplayImage();
        ChecBoxSelected checkBoxSelected; // Indicates what checkbox is currently selected if shown in menu sub level
        BikeStatusLights lightsParkSelectNext = lightsMain; // Deafult go to Main lights from park

    public:
        
        void loopAction() {
            // Check for auto shut down
            if (bikeStatus.displayMenuTimeoutTimestamp > 0 && millis() > bikeStatus.displayMenuTimeoutTimestamp) {
                bikeStatus.displayMenuTimeoutTimestamp = 0;
                displayHelper.gotoStatusPageInitiate();
            }
            // If stopwatch is selected, show as running
            if (bikeStatus.displayMenyShowRunningStopWatch > 0 && millis() > bikeStatus.displayMenyShowRunningStopWatch + 1000) {
                displayStopWatchTime();
            }
            
            // Check if next menu button is pressed - PERFORM GOTO NEXT MENU ITEM
            if (btnMenuNext.isClicked())
            {
                // Timestamp for display menu auto shutdown
                Config::DisplayMenuSettings dms = Config::DisplayMenuSettings();
                bikeStatus.displayMenuTimeoutTimestamp = millis() + (dms.ShutdownWait);
                // Check if progress for goto status page is in progress, cancel and show same menu if relevant
                if (bikeStatus.displayGotoStatusPageProgress) {
                    // Stay on same menu, cancel goto status page
                    displayHelper.gotoStatusPageCancel();
                }
                else {
                    // Goto next menu if not sub menu is selected, 0 = no menu currently selected, 1 = first menu item
                    if (bikeStatus.displayMenySubPageSelected == 0) {
                        bikeStatus.displayMenyPageSelected++;
                        display.clearDisplay();
                    }
                }
                bikeStatus.displayMenyShowRunningStopWatch = 0;
                Config::DisplayMenuItemShow dmis = Config::DisplayMenuItemShow();
                if (bikeStatus.displayMenyPageSelected >= dmis.count + 1) {
                    // Goto status screen
                    bikeStatus.displayMenyPageSelected = 0;
                    bikeStatus.displayMenuTimeoutTimestamp = 0;
                    displayHelper.gotoStatusPageCancel();
                    displayHelper.refreshStatusPage();
                }
                else {
                    // Select the menu according to config
                    Config::DisplayMenuItemShow dmis = Config::DisplayMenuItemShow();
                    Config::DisplayMenuItemInfo dmiSelected = dmis.item[bikeStatus.displayMenyPageSelected - 1];
                    // Show menu now
                    if (dmiSelected.id == 1) {
                        // Ignition
                        if (bikeStatus.displayMenySubPageSelected == 0)
                        {
                            // No sub level menu selected, show default ingnition onb
                            displayImage.ignOn();
                            displayHelper.statusTextShow("IGNITION ON");
                            checkBoxSelected = checkBoxRight;
                        }
                        else
                        {
                            // Sub level selected, toggle checkboxes
                            if (checkBoxSelected == checkBoxRight) {
                                checkBoxSelected = checkBoxLeft;
                                displayHelper.statusTextShow("TURN OFF", false);
                            }
                            else if (checkBoxSelected == checkBoxLeft) {
                                checkBoxSelected = checkBoxRight;
                                displayHelper.statusTextShow("IGNITION ON", false);
                            }
                            // Toggle on display
                            displayImage.menuSelectFrameContentInverse(true,true);
                            display.display();
                        }
                    }
                    else if (dmiSelected.id == 2) {
                        // Stopwatch
                        displayImage.stopwatch();
                        displayStopWatchTime();
                        bikeStatus.displayMenyShowRunningStopWatch = millis();
                        displayHelper.statusTextShow(dmiSelected.displayName);
                    }
                    else if (dmiSelected.id == 3) {
                        // Temp Outside
                        displayImage.temperature();
                        displayHelper.statusTextShow(dmiSelected.displayName);
                    }
                    else if (dmiSelected.id == 4) {
                        // Temp System
                        displayImage.temperature();
                        displayHelper.statusTextShow(dmiSelected.displayName);
                    }
                    else if (dmiSelected.id == 5) {
                        // Lights
                        showSelectedLights();
                    }
                }
            }
            
            // Check if select menu item button is pressed - PERFORM ACTION
            if (btnMenuSelect.isClicked())
            {
                // Timestamp for display menu auto shutdown
                Config::DisplayMenuSettings dms = Config::DisplayMenuSettings();
                bikeStatus.displayMenuTimeoutTimestamp = millis() + (dms.ShutdownWait);
                // Check if progress for goto status page is in progress, cancel it and continue if relevant
                if (bikeStatus.displayGotoStatusPageProgress) {
                    // Stay on same menu, cancel display off and ignore action
                    displayHelper.gotoStatusPageCancel();
                    display.display();
                }
                else {
                    // Select the menu according to config
                    Config::DisplayMenuItemShow dmis = Config::DisplayMenuItemShow();
                    Config::DisplayMenuItemInfo dmiSelected = dmis.item[bikeStatus.displayMenyPageSelected - 1];
                    // Show next menu now
                    if (dmiSelected.id == 1) {
                        // Ignition actions
                        if (bikeStatus.displayMenySubPageSelected == 0) {
                            // initially show ignition on checkboxes
                            clearGraphicsNotStatusText();
                            displayImage.menuSelectFrame(true,true);
                            displayImage.menuSelectIconOff(true,false);
                            displayImage.menuSelectIconOn(false,true);
                            displayImage.menuSelectFrameContentInverse(false,true);
                            display.display();
                            bikeStatus.displayMenySubPageSelected = 1; // Indicate first level sub menu selected
                        }
                        else if (bikeStatus.displayMenySubPageSelected == 1) {
                            // perform action
                            bikeStatus.displayMenySubPageSelected = 0;
                            if (checkBoxSelected == checkBoxRight) {
                                // keep on, return to ignition main menu
                                clearGraphicsNotStatusText();
                                displayImage.ignOn();
                                displayHelper.statusTextShow("IGNITION ON");
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
                                serialCommunication.send(output.mainPower.pin, 0);
                                serialCommunication.send(output.coilGround.pin, 0);
                                serialCommunication.send(output.starterMotor.pin, 0);
                                serialCommunication.send(output.turnSignalLeft.pin, 0);
                                serialCommunication.send(output.turnSignalRight.pin, 0);
                                serialCommunication.send(output.lightPark.pin, 0);
                                serialCommunication.send(output.lightLow.pin, 0);
                                serialCommunication.send(output.lightHigh.pin, 0);
                                serialCommunication.send(output.lightBrake.pin, 0);
                                serialCommunication.send(output.horn.pin, 0);
                                // show end screen
                                displayImage.ignOn();
                                delay(500);
                                displayImage.ignOffToOn2();
                                delay(50);
                                displayImage.ignOffToOn1();
                                delay(50);
                                displayImage.ignOff();
                                displayHelper.statusTextShow("IGNITION TURNED OFF");
                                displayHelper.gotoStatusPageInitiate();
                            }
                        }
                    }
                    else if (dmiSelected.id == 2) {
                        // Stopwatch actions
                    }
                    else if (dmiSelected.id == 3) {
                        // Temp Outside actions
                    }
                    else if (dmiSelected.id == 4) {
                        // Temp System actions
                    }
                    else if (dmiSelected.id == 5) {
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
                    }
                }
            }
        }

        void showSelectedLights() {
            SerialCommunication serialCommunication = SerialCommunication();
            Config::RelayUnitOutput output = Config::RelayUnitOutput();
            if (bikeStatus.lights == lightsOff) {
                displayImage.lightsOffBig(imgPosMenuCenter);
                displayHelper.statusTextShow("LIGHTS OFF");
                serialCommunication.send(output.lightPark.pin, 0);
                serialCommunication.send(output.lightLow.pin, 0);
                serialCommunication.send(output.lightHigh.pin, 0);
            }
            else if (bikeStatus.lights == lightsPark) {
                displayImage.lightsParkBig(imgPosMenuCenter);
                displayHelper.statusTextShow("PARKING LIGHTS");
                serialCommunication.send(output.lightPark.pin, 1);
                serialCommunication.send(output.lightLow.pin, 0);
                serialCommunication.send(output.lightHigh.pin, 0);
            }
            else if (bikeStatus.lights == lightsMain) {
                if (bikeStatus.lightHilo == lightsLow) { 
                    displayImage.lightsLowBig(imgPosMenuCenter);
                    displayHelper.statusTextShow("LOW BEAM");
                    serialCommunication.send(output.lightLow.pin, 1);
                    serialCommunication.send(output.lightHigh.pin, 0);
                }
                else if (bikeStatus.lightHilo == lightsHigh) {
                    displayImage.lightsHighBig(imgPosMenuCenter);
                    displayHelper.statusTextShow("HIGH BEAM");
                    serialCommunication.send(output.lightLow.pin, 0);
                    serialCommunication.send(output.lightHigh.pin, 1);
                }
            }
        }

    private:

        void clearGraphicsNotStatusText() {
            display.fillRect(0, 0, Config::DisplaySettings::ScreenWidth, Config::DisplaySettings::ScreenHeight-Config::DisplaySettings::TextCharHeight, SSD1306_BLACK);
        }

        // Display text on menu select checkboxes, checkbox frame start on y-pos 3, sixe: 50x50, frame border 2px
        void menuSelectCheckboxText(String text, bool left, bool right) {
            uint8_t y = 3 + 35;
            uint8_t textPixLen = text.length() * Config::DisplaySettings::TextCharHeight;
            if (left) {
                uint8_t x = ((Config::DisplaySettings::ScreenWidth/2)-6-25)-(textPixLen/2);
                display.setCursor(x,y);
                display.println(text);
            }
            if (right) {
                uint8_t x = ((Config::DisplaySettings::ScreenWidth/2)+6+25)-(textPixLen/2);
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
            int y = (Config::DisplaySettings::ScreenHeight / 2) - (Config::DisplaySettings::TextCharHeight);
            // Clear first?
            display.fillRect(x,y,Config::DisplaySettings::ScreenWidth, Config::DisplaySettings::TextCharHeight * 2, SSD1306_BLACK);
            display.setCursor(x, y);
            display.setTextSize(Config::DisplaySettings::TextSize + 1); // Larger font
            display.println(timeFormatted);
            display.display();
            display.setTextSize(Config::DisplaySettings::TextSize);
            
        }


};