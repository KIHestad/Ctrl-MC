/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class DisplayHelper {

    public:
        
        // Constructor
        void init() {
            u8g2.begin();
            u8g2.setFont(u8g2_font_luRS08_tr);
            u8g2.setFontRefHeightExtendedText();
            u8g2.setDrawColor(1);
            u8g2.setFontPosTop();
            u8g2.setFontDirection(0);
            showSplash();
            displayTimeoutInitiate(0);
        };

        static void clearDisplay() {
            u8g2.clearBuffer();
        }

        static void refresh() {
            u8g2.sendBuffer();
        }

        static void fillRect(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, uint8_t color) {
            // color: 0 = BLACK (erase), 1 = WHITE
            u8g2.setDrawColor(color);
            u8g2.drawBox(x , y , w, w);
            u8g2.setDrawColor(1);
        }

        static void setTextSize(uint8_t size) {
            if (size == 1)
                u8g2.setFont(u8g2_font_luBS08_tr);
            else if (size == 2)
                u8g2.setFont(u8g2_font_luBS12_tr);
            else 
                u8g2.setFont(u8g2_font_luBS24_tr);
        }   

        static void setCursor(int x, int y) {
            u8g2.setCursor(x, y);
        }

        static void println(String s) {
            u8g2.print(s);
        }

        // Show splash screen
        void showSplash() {
            clearDisplay();
            DisplayImage::kiHestadLogo();
            delay(1750);
            clearDisplay();
            setCursorForCenteredText(1, 7);
            println("Ctrl-MC");
            refresh();
            delay(250);
            setCursorForCenteredText(2, 21);
            println("Motorcycle Controller");
            refresh();
            delay(250);
            setCursorForCenteredText(3, 12);
            println("by KI Hestad");
            refresh();
            delay(250);
        };

        // Inititate display timeout
        void displayTimeoutInitiate() {
            displayTimeoutCancel();
            bikeStatus.displayTimeoutTimestamp = millis() + Config::DisplaySettings::timeoutDelay + Config::DisplaySettings::timeoutProgressbarDuration;
        };
        void displayTimeoutInitiate(unsigned long delay) {
            displayTimeoutCancel();
            bikeStatus.displayTimeoutTimestamp = millis() + delay + Config::DisplaySettings::timeoutProgressbarDuration;
        };

        // Goto status page after a timeout period, show progressbar until done
        void displayTimeout() {
            if (bikeStatus.displayTimeoutTimestamp > 0) {
                unsigned long timeNow = millis();
                // Check progress
                if (timeNow > bikeStatus.displayTimeoutTimestamp) {
                    // Reset bike status
                    bikeStatus.displayTimeoutTimestamp = 0;
                    // Reset display
                    if (bikeStatus.ignition != BikeStatusIgnition::ignOn) {
                        // Iginition is not on, clear display
                        bikeStatus.ignition = BikeStatusIgnition::ignOff;
                        clearDisplay();
                        refresh();
                    }
                    else {
                        // Ignition is on, reset display menu parameters and switch to status page now
                        bikeStatus.displayMenuRefreshTimestamp = 0;
                        bikeStatus.displayMenuPageSelected = 0;
                        bikeStatus.displayMenuSubPageSelected = 0;
                        refreshStatusPage();
                    }
                }
                else if (timeNow > bikeStatus.displayTimeoutTimestamp - Config::DisplaySettings::timeoutProgressbarDuration) {
                    // Show progress bar
                    unsigned long timeElapsed = Config::DisplaySettings::timeoutProgressbarDuration - (bikeStatus.displayTimeoutTimestamp - timeNow);
                    int xLineStart = Config::DisplaySettings::screenWidth * timeElapsed / Config::DisplaySettings::timeoutProgressbarDuration / 2;
                    int xLineEnd = Config::DisplaySettings::screenWidth - xLineStart;
                    u8g2.setDrawColor(0);
                    u8g2.drawLine(0, progressBarY, Config::DisplaySettings::screenWidth, progressBarY);
                    u8g2.setDrawColor(1);
                    u8g2.drawLine(xLineStart, progressBarY, xLineEnd , progressBarY);
                    refresh();
                }
            }
        };

        // Return true if progressbar for goto status page is running
        bool displayTimeoutProgressRunning() {
            return (bikeStatus.displayTimeoutTimestamp > 0);
        }

        // Terminate display autosuhutdown and hide progress bar
        void displayTimeoutCancel() {
            // If timeout set, cancel it
            if (bikeStatus.displayTimeoutTimestamp > 0) {
                // If progressbar showing, remove it
                if (millis() > bikeStatus.displayTimeoutTimestamp - Config::DisplaySettings::timeoutProgressbarDuration) {
                    u8g2.setDrawColor(0);
                    u8g2.drawLine(0, progressBarY, Config::DisplaySettings::screenWidth, progressBarY);
                    u8g2.setDrawColor(1);
                    refresh();
                };
                // Cancel timeout now
                bikeStatus.displayTimeoutTimestamp = 0;
            }
        };

        // Refresh and show the status page if not a menu item is selected
        void refreshStatusPage() {
            if (bikeStatus.displayMenuPageSelected == 0)
            {
                // Prepare display for status page
                displayTimeoutCancel();
                clearDisplay();
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
                refresh();
            }
        }

        void statusTextRemove() {
            fillRect(0, Config::DisplaySettings::screenHeight - Config::DisplaySettings::textCharHeight -1, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight + 2, 0); 
        };

        void statusTextSetCursor(uint8_t txtLength) {
            uint8_t textPixelWidth = txtLength * Config::DisplaySettings::textCharWidth;
            setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , Config::DisplaySettings::screenHeight - Config::DisplaySettings::textCharHeight); 
        }

        void statusTextPrepare(uint8_t txtLength) {
            statusTextRemove();
            statusTextSetCursor(txtLength);
        }

        void statusTextShow(String txt, bool displayImmediately = true) {
            statusTextRemove();
            statusTextSetCursor(txt.length());
            println(txt);
            if (displayImmediately)
                refresh();
        }

        void centeredTextShow(String txt, bool displayImmediately = true) {
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::textCharWidth;
            fillRect(0, (Config::DisplaySettings::screenHeight/2) - Config::DisplaySettings::textCharHeight, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight + 2, 0); 
            setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , (Config::DisplaySettings::screenHeight/2) - Config::DisplaySettings::textCharHeight);
            println(txt);
            if (displayImmediately)
                refresh();
        }

        void rowTextShow(String txt, uint8_t rowNum, bool displayImmediately = true) {
            if (rowNum > 3)
                rowNum = 3;
            uint8_t yPos = (rowNum*(Config::DisplaySettings::textCharHeight+5)) + 4 + 9;
            uint8_t textPixelWidth = txt.length() * Config::DisplaySettings::textCharWidth;

            fillRect(0, yPos, Config::DisplaySettings::screenWidth, Config::DisplaySettings::textCharHeight, 0); 
            setCursor((Config::DisplaySettings::screenWidth/2) - (textPixelWidth/2) , yPos);
            println(txt);
            //display.println(F("")); // TODO: Unstable to pass String, does this help?
            if (displayImmediately)
                refresh();
        }

        void showDebugModeInfo() {
            uint8_t x = Config::DisplaySettings::screenWidth - 6;
            uint8_t y = Config::DisplaySettings::screenHeight - 8;
            fillRect(x,y,6,8,1);
            refresh();
            delay(100);
            fillRect(x,y,6,8,0);
            setCursor(x,y);
            println("D");
            refresh();
        }

    private:

        // Position for progressbar
        uint8_t progressBarY = 0;

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
            setCursor(getXposForCenterText(textLength), getYposForCenterText(rowNum)); 
        }
        
        
};