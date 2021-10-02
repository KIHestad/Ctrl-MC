/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class ControlDisplay {

    public:
        
        // Constructor
        void init() {
            // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
            if(!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_SCREEN_ADDRESS)) {
                // TODO, use spaker to send alarm sound signal
                // Serial.println(F("Display (SSD1306) allocation failed"));
                for(;;); // HALT - Don't proceed, loop forever
            }
            display.setTextSize(DISPLAY_TEXT_SIZE);
            display.setTextColor(SSD1306_WHITE);
            showSplash();
            gotoStatusPageInitiate();
        };

        // Show splash screen
        void showSplash() {
            Image image = Image();
            image.kiHestadLogo();
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
                // Check for power off
                if (timeElapsed > DISPLAY_OFF_WAIT_TIME) {
                    // Power off now
                    gotoStatusPageCancel();
                    refreshStatusPage();
                    bikeStatus.displayStatusTextRemoveTimeStamp = 0;
                    bikeStatus.displayMenuTimestamp = 0;
                    bikeStatus.displayMenyScrollSelector = 0;
                    bikeStatus.displayMenySubLevelSelector = 0;
                    bikeStatus.displayMenyShowRunningStopWatch = 0;
                }
                else {
                    // Show progress bar
                    int xLineStart = DISPLAY_SCREEN_WIDTH * timeElapsed / DISPLAY_OFF_WAIT_TIME / 2;
                    int xLineEnd = DISPLAY_SCREEN_WIDTH - xLineStart;
                    display.drawLine(0, 0, DISPLAY_SCREEN_WIDTH, 0, SSD1306_BLACK);
                    display.drawLine(xLineStart, 0, xLineEnd + 2, 0, SSD1306_WHITE);
                    display.display();
                    bikeStatus.displayGotoStatusPageProgress = true;
                }
            }
            if (bikeStatus.displayStatusTextRemoveTimeStamp > 0 ) {
                if (millis() > bikeStatus.displayStatusTextRemoveTimeStamp) {
                    statusTextRemove();
                    display.display();
                    bikeStatus.displayStatusTextRemoveTimeStamp = 0;
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
            display.drawLine(0, 0, DISPLAY_SCREEN_WIDTH, 0, SSD1306_BLACK);
        };

        // Refresh and show the status page if not a menu item is selected
        void refreshStatusPage() {
            if (bikeStatus.displayMenyScrollSelector == 0)
            {
                // Prepare display for status page
                gotoStatusPageCancel();
                display.clearDisplay();
                if (bikeStatus.ignition == ignOn)
                {
                    Image image = Image();
                    // Dependig of bike status show 1, 2 or 3 image icons
                    if (bikeStatus.indicator != indOff) {
                        // Turn signals are on, show 3 icon layout, turn signal indicator as big
                        if (bikeStatus.indicator != indOff && bikeStatus.indicatorBlinkOn) {
                            if (bikeStatus.indicator == indLeft)
                                image.indicatorLeft(imgPos3Left);
                            else if (bikeStatus.indicator == indRight)
                                image.indicatorRight(imgPos3Left);
                            else if (bikeStatus.indicator == indHazard)
                                image.indicatorHazard(imgPos3Left);
                        }
                        if (bikeStatus.lights != lightsOff) {
                            if (bikeStatus.lights == lightsPark)
                                image.lightsParkSmall(imgPos3RightTop);
                            else if (bikeStatus.lights == lightsMain && bikeStatus.lightHilo == lightsLow)
                                image.lightsLowSmall(imgPos3RightTop);
                            else if (bikeStatus.lights == lightsMain && bikeStatus.lightHilo == lightsHigh)
                                image.lightsHighSmall(imgPos3RightTop);
                        }
                        if (bikeStatus.neutral) {
                            image.neutralSmall(imgPos3RightBottom);
                        }
                    }
                    else if (bikeStatus.lights != lightsOff) {
                        // Both lights and neutral/in gear to be shown, show to icon layout
                        if (bikeStatus.lights == lightsPark)
                            image.lightsParkBig(imgPos2Left);
                        else if (bikeStatus.lights == lightsMain && bikeStatus.lightHilo == lightsLow)
                            image.lightsLowBig(imgPos2Left);
                        else if (bikeStatus.lights == lightsMain && bikeStatus.lightHilo == lightsHigh)
                            image.lightsHighBig(imgPos2Left);
                        if (bikeStatus.neutral) {
                            image.neutralBig(imgPos2Right);
                        }
                    }
                    else {
                        if (bikeStatus.neutral) {
                            image.neutralBig(imgPosCenter);
                        }
                    }
                }
                display.display();
            }
        }

        void statusTextRemove() {
            display.fillRect(0, DISPLAY_SCREEN_HEIGHT-DISPLAY_TEXT_CHAR_HEIGHT -1, DISPLAY_SCREEN_WIDTH, DISPLAY_TEXT_CHAR_HEIGHT + 2, SSD1306_BLACK); 
        };

        void statusTextSetCursor(uint8_t txtLength) {
            uint8_t textPixelWidth = txtLength * DISPLAY_TEXT_CHAR_WIDTH;
            display.setCursor((DISPLAY_SCREEN_WIDTH/2) - (textPixelWidth/2) , DISPLAY_SCREEN_HEIGHT - DISPLAY_TEXT_CHAR_HEIGHT); 
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

    private:

        // Get x position for centered text
        int getXposForCenterText(int textLength) {
            return (DISPLAY_SCREEN_WIDTH/2)-(textLength*DISPLAY_TEXT_CHAR_WIDTH/2);
        }
        // Get y position for centered text, parameter num = row number; 1, 2 or 3
        int getYposForCenterText(int rowNum) {
            int rowRelativeToMid = rowNum -2; // -1 = first, 0 = second(mid), 1 third and last
            int centerRowTopPos = (DISPLAY_SCREEN_HEIGHT/2)-DISPLAY_TEXT_CHAR_HEIGHT/2;
            return (centerRowTopPos + ((DISPLAY_TEXT_CHAR_HEIGHT+1)*rowRelativeToMid*2));
        }
        // Write centered text at spesific row
        void setCursorForCenteredText(int rowNum, int textLength) {
            display.setCursor(getXposForCenterText(textLength), getYposForCenterText(rowNum)); 
        }
        
        
};