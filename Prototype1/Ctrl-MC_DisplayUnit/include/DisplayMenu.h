enum CheckBoxSelected { checkBoxLeft, checkBoxMid, checkBoxRight};

class DisplayMenu {

    public:

        void loopAction() {
            // Check what page is selected
            Config::DisplayMenuItem dispMenuItem = Config::DisplayMenuItem();
            
            // ***********
            // Status page
            // ***********
            if (bikeStatus.displayMenuPageSelected == 0) {
                if (btnMenuMain.isClicked()) {
                    // Goto first main menu item
                    gotoMenuPage(1);
                }
                else if (btnMenuStartStop.isClicked()) {
                    // Goto engine start/stop page
                    gotoMenuPage(nextMenuStartStopPage());
                }
            }

            // *****************
            // Engine start page
            // *****************
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.engineStart.id) {
                Config::RelayUnitOutput ruOutput = Config::RelayUnitOutput();
                if (btnMenuStartStop.isClicked()) {
                    // Goto next engine start/stop page
                    gotoMenuPage(nextMenuStartStopPage());
                }
                else if (btnMenuMain.isHold() && bikeStatus.engine != BikeStatusEngine::engStartMotorEngaged) {
                    // Engage starter motor
                    displayHelper.displayTimeoutInitiate(5000);
                    bikeStatus.engine = BikeStatusEngine::engStartMotorEngaged;
                    serialCommunication.send(ruOutput.coilGround.pin,1);
                    serialCommunication.send(ruOutput.starterMotor.pin,1);
                    DisplayImage displayImage = DisplayImage();
                    displayImage.startEngaged();
                    displayHelper.statusTextShow("STARTING");
                }
                else if (!btnMenuMain.isHold() && bikeStatus.engine == BikeStatusEngine::engStartMotorEngaged) {
                    // Release starter motor
                    displayHelper.displayTimeoutInitiate(5000);
                    bikeStatus.engine = BikeStatusEngine::engUnknownStatus;
                    serialCommunication.send(ruOutput.starterMotor.pin,0);
                    DisplayImage displayImage = DisplayImage();
                    displayImage.start();
                    displayHelper.statusTextShow(dispMenuItem.engineStart.displayName);
                }
            }

            // *****************
            // Engine stop page
            // *****************
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.engineStop.id) {
                Config::RelayUnitOutput ruOutput = Config::RelayUnitOutput();
                if (btnMenuStartStop.isClicked()) {
                    // Goto next engine start/stop page
                    gotoMenuPage(nextMenuStartStopPage());
                }
                else if (btnMenuMain.isClicked()) {
                    // Stop engine
                    bikeStatus.engine = BikeStatusEngine::engStopped;
                    serialCommunication.send(ruOutput.coilGround.pin,0);
                    DisplayImage displayImage = DisplayImage();
                    displayImage.stopClicked();
                    displayHelper.statusTextShow("STOPPING");
                    while (btnMenuMain.isHold()) {
                        delay(100);
                    }
                    displayHelper.displayTimeoutInitiate(0);
                    displayImage.stop();
                    displayHelper.statusTextShow("STOPPED");
                }
            }

            // ********************************************
            // Ignition page
            // Sublevel 0 = main ignition page
            // Syvkevek 1 = turn bike off confirmation page
            // ********************************************
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.ignition.id) {
                // Topmost menu
                if (bikeStatus.displayMenuSubPageSelected == 0) {
                    // Go to next main menu
                    if (btnMenuMain.isClicked())
                        gotoMenuPage(nextMenuMainPage());
                    // Go to sub menu
                    else if (btnMenuStartStop.isClicked()) {
                        bikeStatus.displayMenuSubPageSelected = 1;
                        gotoMenuPage(dispMenuItem.ignition.id);
                    }
                }
                // Sub menu
                else if (bikeStatus.displayMenuSubPageSelected == 1) {
                    // Toggle ignition on/off
                    if (btnMenuMain.isClicked()) {
                        displayHelper.displayTimeoutInitiate();
                        if (checkBoxSelected == checkBoxRight) {
                            checkBoxSelected = checkBoxLeft;
                            displayHelper.statusTextShow("TURN IGNITION OFF", false);
                        }
                        else if (checkBoxSelected == checkBoxLeft) {
                            checkBoxSelected = checkBoxRight;
                            displayHelper.statusTextShow("KEEP IGNITION ON", false);
                        }
                        // Toggle on display
                        DisplayImage displayImage = DisplayImage();
                        displayImage.menuSelectFrameContentInverse(true,true);
                        displayHelper.refresh();
                    }
                    // Select sub menu option, keep on or turn off ignition
                    else if (btnMenuStartStop.isClicked()) {
                        if (checkBoxSelected == checkBoxRight) {
                            // keep on, return to ignition main menu
                            bikeStatus.displayMenuSubPageSelected = 0;
                            gotoMenuPage(dispMenuItem.ignition.id);
                        }
                        else if (checkBoxSelected == checkBoxLeft) {
                            displayHelper.displayTimeoutCancel();
                            // turn off
                            bikeStatus.ignition = ignOff;
                            bikeStatus.lights = lightsOff;
                            bikeStatus.lightHilo = lightsLow;
                            bikeStatus.indicator = indOff;
                            bikeStatus.engine = engStopped;
                            bikeStatus.displayMenuPageSelected = 0;
                            bikeStatus.displayMenuSubPageSelected = 0;
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
                            DisplayImage displayImage = DisplayImage();
                            displayImage.ignOn();
                            displayHelper.refresh();
                            delay(500);
                            displayImage.ignOffToOn2();
                            delay(50);
                            displayImage.ignOffToOn1();
                            delay(50);
                            displayImage.ignOff();
                            displayHelper.statusTextShow("IGNITION TURNED OFF");
                            displayHelper.displayTimeoutInitiate(0);
                        }
                    }
                }
            }

            // ***********
            // Lights page
            // ***********
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.lights.id) {
                if (btnMenuMain.isClicked()) {
                    // Go to next main menu
                    gotoMenuPage(nextMenuMainPage());
                }
                else if (btnMenuStartStop.isClicked()) {
                    // Change lights
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
                    gotoMenuPage(dispMenuItem.lights.id);
                }
            }

            // *********
            // Stopwatch
            // *********
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.stopWatch.id) {
                if (btnMenuMain.isClicked()) {
                    // Go to next main menu
                    gotoMenuPage(nextMenuMainPage());
                }
                else {
                    // Update stopwatch
                    if (millis() > bikeStatus.displayMenuRefreshTimestamp) {
                        displayStopWatchTime();
                        bikeStatus.displayMenuRefreshTimestamp = millis() + 1000;
                    }
                    // TODO: consider option for reset stopwatch, for now just reset timout
                    if (btnMenuStartStop.isClicked())
                        displayHelper.displayTimeoutInitiate();
                }
            }

            // ***********
            // System Temo
            // ***********
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.tempSystem.id) {
                if (btnMenuMain.isClicked()) {
                    // Go to next main menu
                    gotoMenuPage(nextMenuMainPage());
                }
                else {
                    // Change format celcius / farenheit
                    if (btnMenuStartStop.isClicked()) {
                        bikeStatus.tempShowFarenheit = !bikeStatus.tempShowFarenheit;
                        displayHelper.displayTimeoutInitiate();
                        bikeStatus.displayMenuRefreshTimestamp = millis() - 1000;
                    }
                    // Update temp
                    if (millis() > bikeStatus.displayMenuRefreshTimestamp) {
                        displaySystemTemp();
                        bikeStatus.displayMenuRefreshTimestamp = millis() + 3000;
                    }
                }
            }

            // ***************
            // Battery Voltage
            // ***************
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.batteryVoltage.id) {
                if (btnMenuMain.isClicked()) {
                    // Go to next main menu
                    gotoMenuPage(nextMenuMainPage());
                }
                else {
                    // Update battery voltage reading
                    if (millis() > bikeStatus.displayMenuRefreshTimestamp) {
                        displayBatteryVoltage();
                        bikeStatus.displayMenuRefreshTimestamp = millis() + 3000;
                    }
                    // TODO: consider option for reset stopwatch, for now just reset timout
                    if (btnMenuStartStop.isClicked())
                        displayHelper.displayTimeoutInitiate();
                }
            }
        }

        void showSelectedLights() {
            SerialCommunication serialCommunication = SerialCommunication();
            Config::RelayUnitOutput output = Config::RelayUnitOutput();
            DisplayImage displayImage = DisplayImage();
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
                    Config::Headlight headlightConfig = Config::Headlight();
                    uint8_t lightHighValue = headlightConfig.hiWithLow ? 1 : 0;
                    serialCommunication.send(output.lightLow.pin, lightHighValue);
                    serialCommunication.send(output.lightHigh.pin, 1);
                }
            }
        }

    private:

        CheckBoxSelected checkBoxSelected; // Indicates what checkbox is currently selected if shown in menu sub level
        BikeStatusLights lightsParkSelectNext = lightsMain; // Default go to Main lights from park

        uint8_t nextMenuStartStopPage() {
            Config::DisplayMenuItem dispMenuItem = Config::DisplayMenuItem();
            if (bikeStatus.displayMenuPageSelected == 0)
                if (bikeStatus.engine == BikeStatusEngine::engStopped) 
                    return dispMenuItem.engineStart.id;
                else
                    return dispMenuItem.engineStop.id;
            else if (bikeStatus.displayMenuPageSelected == dispMenuItem.engineStart.id)
                return dispMenuItem.engineStop.id;
            else return 0;
        }

        uint8_t nextMenuMainPage() {
            // Go to next main menu utem
            bikeStatus.displayMenuPageSelected++;
            // If above max, return to status page
            if (bikeStatus.displayMenuPageSelected > Config::DisplayMenuItem::menuMainItemsCount)
                bikeStatus.displayMenuPageSelected = 0;
            return bikeStatus.displayMenuPageSelected;
        }

        void gotoMenuPage(uint8_t pageId) {
            // Set new selected page
            bikeStatus.displayMenuPageSelected = pageId;
            // Go back to status page
            if (pageId == 0) {
                displayHelper.refreshStatusPage();
            }
            else
            {
                // Prepare display
                DisplayImage displayImage = DisplayImage();
                Config::DisplayMenuItem dispMenuItem = Config::DisplayMenuItem();
                displayHelper.clearDisplay();
                displayHelper.displayTimeoutInitiate();
                // MenuStartStop Item: Engine start page
                if (pageId == dispMenuItem.engineStart.id) {
                    displayImage.start();
                    displayHelper.statusTextShow(dispMenuItem.engineStart.displayName);
                }
                // MenuStartStop Item: Engine stop page
                else if (pageId == dispMenuItem.engineStop.id) {
                    displayImage.stop();
                    displayHelper.statusTextShow(dispMenuItem.engineStop.displayName);
                }
                // MenuMain Item: Ignition page
                else if (pageId == dispMenuItem.ignition.id) {
                    if (bikeStatus.displayMenuSubPageSelected == 0) {
                        displayImage.ignOn();
                        displayHelper.statusTextShow(dispMenuItem.ignition.displayName);
                        checkBoxSelected =  CheckBoxSelected::checkBoxRight;
                    }
                    else if (bikeStatus.displayMenuSubPageSelected == 1) {
                        clearGraphicsNotStatusText();
                        displayImage.menuSelectFrame(true,true);
                        displayImage.menuSelectIconOff(true,false);
                        displayImage.menuSelectIconOn(false,true);
                        displayImage.menuSelectFrameContentInverse(false,true);
                        if (checkBoxSelected == checkBoxLeft) 
                            displayHelper.statusTextShow("TURN IGNITION OFF", false);
                        else if (checkBoxSelected == checkBoxRight) 
                            displayHelper.statusTextShow("KEEP IGNITION ON", false);
                        displayHelper.refresh();
                    }
                }
                // MenuMain Item: Lights page
                else if (pageId == dispMenuItem.lights.id) {
                    showSelectedLights();
                }
                // MenuMain Item: Stopwatch page
                else if (pageId == dispMenuItem.stopWatch.id) {
                    displayImage.stopwatch();
                    displayHelper.statusTextShow(dispMenuItem.stopWatch.displayName, false);
                    displayStopWatchTime();
                    bikeStatus.displayMenuRefreshTimestamp = millis() + 1000;
                } 
                // MenuMain Item: System temp page
                else if (pageId == dispMenuItem.tempSystem.id) {
                    // Request new temp reading
                    serialCommunication.send(SerialCommunication::SerialCode::sysTempRequest, 0);
                    serialCommunication.send(SerialCommunication::SerialCode::sysHumidityRequest, 0);
                    // Show on display
                    displayImage.temperature();
                    displayHelper.statusTextShow(dispMenuItem.tempSystem.displayName, false);
                    displaySystemTemp();
                    // First update in 1 sek
                    bikeStatus.displayMenuRefreshTimestamp = millis() + 1000;
                } 
                // MenuMain Item: Battery Voltage
                else if (pageId == dispMenuItem.batteryVoltage.id) {
                    // Request new battery reading
                    serialCommunication.send(SerialCommunication::SerialCode::batteryVoltageRequest, 0);
                    // Show on display
                    displayImage.batteryVoltage();
                    displayHelper.statusTextShow(dispMenuItem.batteryVoltage.displayName, false);
                    displayBatteryVoltage();
                    // First update in 1 sek
                    bikeStatus.displayMenuRefreshTimestamp = millis() + 1000;
                } 
                // Unknown page
                else {
                    // unknown menu page, return to status screen
                    displayHelper.clearDisplay();
                    displayImage.warning();
                    displayHelper.statusTextShow("INVALID MENU ITEM");
                    displayHelper.displayTimeoutInitiate(0);
                }
            }
        }

        void clearGraphicsNotStatusText() {
            displayHelper.fillRect(0, 0, Config::DisplaySettings::screenWidth, Config::DisplaySettings::screenHeight-Config::DisplaySettings::textCharHeight, 0);
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
            int y = (Config::DisplaySettings::screenHeight / 2) - (Config::DisplaySettings::textLargeCharHeight) + 2;
            // Clear first?
            displayHelper.setTextSize(Config::DisplaySettings::textLargeSize); // Larger font
            displayHelper.fillRect(x,y,Config::DisplaySettings::screenWidth, Config::DisplaySettings::textLargeCharHeight, 0);
            displayHelper.setCursor(x, y);
            displayHelper.println(timeFormatted);
            displayHelper.refresh();
            displayHelper.setTextSize(Config::DisplaySettings::textSize);
            
        }

        void displaySystemTemp() {
            // Format temperature
            float temp = (float)(bikeStatus.sysTempInt);
            temp += (float)(bikeStatus.sysTempDec) / 10;
            String tempSubFix = " C";
            // Alternative for Farenheit: T(°F) = T(°C) × 9/5 + 32 
            if (bikeStatus.tempShowFarenheit) {
                temp = (temp * 1.8) + 32;
                tempSubFix = " F";
            }
            String tempFormatted = String(temp, 1) + tempSubFix;
            // Format humidity
            float humidity = (float)(bikeStatus.sysHumidityInt);
            humidity += (float)(bikeStatus.sysHumidityDec) / 10;
            String humFormatted = String(humidity,1);
            humFormatted += "%";
            // Display 
            int x = 32;
            int y = (Config::DisplaySettings::screenHeight / 2) - (Config::DisplaySettings::textLargeCharHeight) + 2;
            // Show sys temp
            displayHelper.setTextSize(Config::DisplaySettings::textLargeSize); // Larger font
            displayHelper.fillRect(x,y,Config::DisplaySettings::screenWidth, Config::DisplaySettings::textLargeCharHeight, 0);
            displayHelper.setCursor(x, y);
            displayHelper.println(tempFormatted);
            displayHelper.setTextSize(Config::DisplaySettings::textSize);
            // Show humidity in status bar
            String statusText = String("SYS TEMP/HUM: ");
            statusText += humFormatted;
            displayHelper.statusTextShow(statusText);
            // Request new temp reading
            serialCommunication.send(SerialCommunication::SerialCode::sysTempRequest, 0);
            serialCommunication.send(SerialCommunication::SerialCode::sysHumidityRequest, 0);
        }

        void displayBatteryVoltage() {
            // Format voltage
            float batteryVoltage = (float)(bikeStatus.batteryVoltage / 10);
            String batteryVoltageFormatted = String(batteryVoltage, 1);
            batteryVoltageFormatted += " V";
            // Display 
            int x = 32;
            int y = (Config::DisplaySettings::screenHeight / 2) - (Config::DisplaySettings::textLargeCharHeight) + 2;
            // Show 
            displayHelper.setTextSize(Config::DisplaySettings::textLargeSize); // Larger font
            displayHelper.fillRect(x,y,Config::DisplaySettings::screenWidth, Config::DisplaySettings::textLargeCharHeight, 0);
            displayHelper.setCursor(x, y);
            displayHelper.println(batteryVoltageFormatted);
            displayHelper.setTextSize(Config::DisplaySettings::textSize);
            displayHelper.refresh();
            // Request new battery reading
            serialCommunication.send(SerialCommunication::SerialCode::batteryVoltageRequest, 0);
        }

};