/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class DisplayHelper {

    public:
        
        // Constructor
        void init() {
            // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
            if(!display.begin(SSD1306_SWITCHCAPVCC, Config::DisplaySettings::screenAddress)) {
                // TODO, use spaker to send alarm sound signal
                // Serial.println(F("Display (SSD1306) allocation failed"));
                for(;;); // HALT - Don't proceed, loop forever
            }
            display.setTextSize(Config::DisplaySettings::textSize);
            display.setTextColor(SSD1306_WHITE);
            showSplash();
            gotoStatusPageInitiate();
        };

        // Show splash screen
        void showSplash() {
            DisplayImage displayImage = DisplayImage();
            displayImage.kiHestadLogo();
            delay(1750);
            display.clearDisplay();
            setCursorForCenteredText(1, 7);
            display.println(F("Ctrl-MC"));
            display.display();
            delay(250);
            setCursorForCenteredText(2, 21);
            display.println(F("Motorcycle Controller"));
            display.display();
            delay(250);
            setCursorForCenteredText(3, 12);
            display.println(F("by KI Hestad"));
            display.display();
            delay(250);
        };

        // Goto status page after a timeout period, show progressbar until done
        void gotoStatusPage() {
            if (bikeStatus.displayGotoStatusPageTimestamp > 0) {
                unsigned long timeElapsed = millis() - bikeStatus.displayGotoStatusPageTimestamp;
                // Check progress
                Config::DisplayMenuSettings dms = Config::DisplayMenuSettings();
                if (timeElapsed > dms.statusPageProgressbarDuration) {
                    // Switch to status page now
                    gotoStatusPageCancel();
                    bikeStatus.displayMenuPageSelected = 0;
                    bikeStatus.displayMenuSubPageSelected = 0;
                    bikeStatus.displayMenuTimeoutTimestamp = 0;
                    bikeStatus.displayMenuShowRunningStopWatch = 0;
                    bikeStatus.displayMenuShowSystemTempRefreshTimestamp = 0;
                    if (bikeStatus.ignition == BikeStatusIgnition::ignTestButtonsMode)
                        bikeStatus.ignition = BikeStatusIgnition::ignOff;
                    refreshStatusPage();
                }
                else {
                    // Show progress bar
                    int xLineStart = Config::DisplaySettings::screenWidth * timeElapsed / dms.statusPageProgressbarDuration / 2;
                    int xLineEnd = Config::DisplaySettings::screenWidth - xLineStart;
                    display.drawLine(0, 0, Config::DisplaySettings::screenWidth, 0, SSD1306_BLACK);
                    display.drawLine(xLineStart, 0, xLineEnd + 2, 0, SSD1306_WHITE);
                    display.display();
                    bikeStatus.displayGotoStatusPageProgress = true;
                }
            }
        };

        // Inititate display autosuhutdown
        void gotoStatusPageInitiate() {
            bikeStatus.displayGotoStatusPageTimestamp = millis();
        };

        // Terminate display autosuhutdown and hide progress bar
        void gotoStatusPageCancel() {
            bikeStatus.displayGotoStatusPageTimestamp = 0;
            bikeStatus.displayGotoStatusPageProgress = false;
            display.drawLine(0, 0, Config::DisplaySettings::screenWidth, 0, SSD1306_BLACK);
        };

        // Refresh and show the status page if not a menu item is selected
        void refreshStatusPage() {
            if (bikeStatus.displayMenuPageSelected == 0)
            {
                // Prepare display for status page
                gotoStatusPageCancel();
                display.clearDisplay();
                if (bikeStatus.ignition == ignOn)
                {
                    DisplayImage displayImage = DisplayImage();
                    // Dependig of bike status show 1, 2 or 3 image icons
                    if (bikeStatus.indicator != indOff) {
                        // Turn signals are on, show 3 icon layout, turn signal indicator as big
                        if (bikeStatus.indicator != indOff && bikeStatus.indicatorBlinkOn) {
                            if (bikeStatus.indicator == indLeft)
                                displayImage.indicatorLeft(imgPos3Left);
                            else if (bikeStatus.indicator == indRight)
                                displayImage.indicatorRight(imgPos3Left);
                            else if (bikeStatus.indicator == indHazard)
                                displayImage.indicatorHazard(imgPos3Left);
                        }
                        if (bikeStatus.lights != lightsOff || bikeStatus.lightHighBeamFlash) {
                            if (bikeStatus.lightHighBeamFlash)
                                displayImage.lightsHighSmall(imgPos3RightTop);
                            else if (bikeStatus.lights == lightsPark)
                                displayImage.lightsParkSmall(imgPos3RightTop);
                            else if (bikeStatus.lightHilo == lightsLow)
                                displayImage.lightsLowSmall(imgPos3RightTop);
                            else if (bikeStatus.lightHilo == lightsHigh)
                                displayImage.lightsHighSmall(imgPos3RightTop);
                        }
                        if (bikeStatus.neutral) {
                            displayImage.neutralSmall(imgPos3RightBottom);
                        }
                    }
                    else if (bikeStatus.lights != lightsOff || bikeStatus.lightHighBeamFlash) {
                        // Both lights and neutral/in gear to be shown, show to icon layout
                        if (bikeStatus.lightHighBeamFlash)
                            displayImage.lightsHighBig(imgPos2Left);
                        else if (bikeStatus.lights == lightsPark)
                            displayImage.lightsParkBig(imgPos2Left);
                        else if (bikeStatus.lightHilo == lightsLow)
                            displayImage.lightsLowBig(imgPos2Left);
                        else if (bikeStatus.lightHilo == lightsHigh)
                            displayImage.lightsHighBig(imgPos2Left);
                        // Neutral
                        if (bikeStatus.neutral) {
                            displayImage.neutralBig(imgPos2Right);
                        }
                    }
                    else {
                        if (bikeStatus.neutral) {
                            displayImage.neutralBig(imgPosCenter);
                        }
                    }
                }
                display.display();
            }
        }

        void statusTextRemove() {
            display.fillRect(0, Config::DisplaySettings::screenHeight - Config::DisplaySettings::textCharHeight -1, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight + 2, SSD1306_BLACK); 
        };

        void statusTextSetCursor(uint8_t txtLength) {
            uint8_t textPixelWidth = txtLength * Config::DisplaySettings::textCharWidth;
            display.setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , Config::DisplaySettings::screenHeight - Config::DisplaySettings::textCharHeight); 
        }

        void statusTextPrepare(uint8_t txtLength) {
            statusTextRemove();
            statusTextSetCursor(txtLength);
        }

        void statusTextShow(String txt, bool displayImmediately = true) {
            statusTextRemove();
            statusTextSetCursor(txt.length());
            display.println(txt);
            display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                display.display();
        }

        void centeredTextShow(String txt, bool displayImmediately = true) {
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::textCharWidth;
            display.fillRect(0, (Config::DisplaySettings::screenHeight/2) - Config::DisplaySettings::textCharHeight, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight + 2, SSD1306_BLACK); 
            display.setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , (Config::DisplaySettings::screenHeight/2) - Config::DisplaySettings::textCharHeight);
            display.println(txt);
            display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                display.display();
        }

        void rowTextShow(String txt, uint8_t rowNum, bool displayImmediately = true) {
            if (rowNum > 3)
                rowNum = 3;
            uint8_t yPos = (rowNum*(Config::DisplaySettings::textCharHeight+5)) + 4;
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::textCharWidth;

            display.fillRect(0, yPos, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight, SSD1306_BLACK); 
            display.setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , yPos);
            display.println(txt);
            //display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                display.display();
        }

    private:

        // Get x position for centered text
        int getXposForCenterText(int textLength) {
            return (Config::DisplaySettings::screenWidth/2)-(textLength*Config::DisplaySettings::textCharWidth/2);
        }
        // Get y position for centered text, parameter num = row number; 1, 2 or 3
        int getYposForCenterText(int rowNum) {
            int rowRelativeToMid = rowNum -2; // -1 = first, 0 = second(mid), 1 third and last
            int centerRowTopPos = (Config::DisplaySettings::screenHeight/2)-Config::DisplaySettings::textCharHeight/2;
            return (centerRowTopPos + ((Config::DisplaySettings::textCharHeight+1)*rowRelativeToMid*2));
        }
        // Write centered text at spesific row
        void setCursorForCenteredText(int rowNum, int textLength) {
            display.setCursor(getXposForCenterText(textLength), getYposForCenterText(rowNum)); 
        }
        
        
};