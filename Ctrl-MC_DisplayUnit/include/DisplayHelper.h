/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class DisplayHelper {

    public:
        
        // Constructor
        void init() {
            // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
            if(!display.begin(SSD1306_SWITCHCAPVCC, Config::DisplaySettings::ScreenAddress)) {
                // TODO, use spaker to send alarm sound signal
                // Serial.println(F("Display (SSD1306) allocation failed"));
                for(;;); // HALT - Don't proceed, loop forever
            }
            display.setTextSize(Config::DisplaySettings::TextSize);
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
                if (timeElapsed > dms.StatusPageProgressbarDuration) {
                    // Switch to status page now
                    gotoStatusPageCancel();
                    bikeStatus.displayMenuPageSelected = 0;
                    bikeStatus.displayMenuSubPageSelected = 0;
                    bikeStatus.displayMenuTimeoutTimestamp = 0;
                    bikeStatus.displayMenuShowRunningStopWatch = 0;
                    if (bikeStatus.ignition == BikeStatusIgnition::ignTestButtonsMode)
                        bikeStatus.ignition = BikeStatusIgnition::ignOff;
                    refreshStatusPage();
                }
                else {
                    // Show progress bar
                    int xLineStart = Config::DisplaySettings::ScreenWidth * timeElapsed / dms.StatusPageProgressbarDuration / 2;
                    int xLineEnd = Config::DisplaySettings::ScreenWidth - xLineStart;
                    display.drawLine(0, 0, Config::DisplaySettings::ScreenWidth, 0, SSD1306_BLACK);
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
            display.drawLine(0, 0, Config::DisplaySettings::ScreenWidth, 0, SSD1306_BLACK);
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
            display.fillRect(0, Config::DisplaySettings::ScreenHeight - Config::DisplaySettings::TextCharHeight -1, Config::DisplaySettings::ScreenWidth, Config::DisplaySettings::TextCharHeight + 2, SSD1306_BLACK); 
        };

        void statusTextSetCursor(uint8_t txtLength) {
            uint8_t textPixelWidth = txtLength * Config::DisplaySettings::TextCharWidth;
            display.setCursor((Config::DisplaySettings::ScreenWidth/2) - (textPixelWidth/2) , Config::DisplaySettings::ScreenHeight - Config::DisplaySettings::TextCharHeight); 
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
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::TextCharWidth;
            display.fillRect(0, (Config::DisplaySettings::ScreenHeight/2) - Config::DisplaySettings::TextCharHeight, Config::DisplaySettings::ScreenWidth, Config::DisplaySettings::TextCharHeight + 2, SSD1306_BLACK); 
            display.setCursor((Config::DisplaySettings::ScreenWidth/2) - (textPixelWidth/2) , (Config::DisplaySettings::ScreenHeight/2) - Config::DisplaySettings::TextCharHeight);
            display.println(txt);
            display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                display.display();
        }

        void rowTextShow(String txt, uint8_t rowNum, bool displayImmediately = true) {
            if (rowNum > 3)
                rowNum = 3;
            uint8_t yPos = (rowNum*(Config::DisplaySettings::TextCharHeight+5)) + 4;
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::TextCharWidth;

            display.fillRect(0, yPos, Config::DisplaySettings::ScreenWidth, Config::DisplaySettings::TextCharHeight, SSD1306_BLACK); 
            display.setCursor((Config::DisplaySettings::ScreenWidth/2) - (textPixelWidth/2) , yPos);
            display.println(txt);
            //display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                display.display();
        }

    private:

        // Get x position for centered text
        int getXposForCenterText(int textLength) {
            return (Config::DisplaySettings::ScreenWidth/2)-(textLength*Config::DisplaySettings::TextCharWidth/2);
        }
        // Get y position for centered text, parameter num = row number; 1, 2 or 3
        int getYposForCenterText(int rowNum) {
            int rowRelativeToMid = rowNum -2; // -1 = first, 0 = second(mid), 1 third and last
            int centerRowTopPos = (Config::DisplaySettings::ScreenHeight/2)-Config::DisplaySettings::TextCharHeight/2;
            return (centerRowTopPos + ((Config::DisplaySettings::TextCharHeight+1)*rowRelativeToMid*2));
        }
        // Write centered text at spesific row
        void setCursorForCenteredText(int rowNum, int textLength) {
            display.setCursor(getXposForCenterText(textLength), getYposForCenterText(rowNum)); 
        }
        
        
};