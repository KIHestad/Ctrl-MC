/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class ControlDisplay {
    private:

        // Get x position for centered text
        int getXposForCenterText(int textLength) {
            return (DISPLAY_SCREEN_WIDTH/2)-(textLength*DISPLAY_TEXT_CHAR_WIDTH/2);
        }
        // Get y position for centered text, parameter num = row number; 1, 2 or 3
        int getYposForCenterText(int rowNum) {
            int rowRelativeToMid = rowNum -2; // -1 = first, 0 = second(mid), 1 third and last
            int centerRowTopPos = (DISPLAY_SCREEN_HEIGHT/2)-DISPLAY_TEXT_CHAR_HEIGHT/2;
            return (centerRowTopPos + (DISPLAY_TEXT_CHAR_HEIGHT*rowRelativeToMid*2));
        }
        // Write centered text at spesific row
        void setCursorForCenteredText(int rowNum, int textLength) {
            display.setCursor(getXposForCenterText(textLength), getYposForCenterText(rowNum)); 
        }

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
            bikeStatus.displayOffTimestamp = millis();
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

        void statusTextRemove() {
            display.fillRect(0, DISPLAY_SCREEN_HEIGHT-DISPLAY_TEXT_CHAR_HEIGHT -1, DISPLAY_SCREEN_WIDTH, DISPLAY_TEXT_CHAR_HEIGHT -1, SSD1306_BLACK); 
        };

        void statusTextSetCursor(uint8_t txtLength) {
            uint8_t textPixelWidth = txtLength * DISPLAY_TEXT_CHAR_WIDTH;
            display.setCursor((DISPLAY_SCREEN_WIDTH/2) - (textPixelWidth/2) , DISPLAY_SCREEN_HEIGHT - DISPLAY_TEXT_CHAR_HEIGHT -1); 
        }

        void statusTextPrepare(uint8_t txtLength) {
            statusTextRemove();
            statusTextSetCursor(txtLength);
        }

        void statusTextShow(String txt) {
            statusTextRemove();
            statusTextSetCursor(txt.length());
            display.println(txt);
            display.println(F("")); // TODO: Unstable to pass String, does this help?
            display.display();
        }

        // Turn off display by clearing content after a timeout period, show progressbar until display off
        void displayOffProgress() {
            if (bikeStatus.displayOffTimestamp > 0) {
                unsigned long timeElapsed = millis() - bikeStatus.displayOffTimestamp;
                // Check for power off
                if (timeElapsed > bikeStatus.displayOffWaitTime) {
                    // Power off now
                    displayOffRemove();
                    display.clearDisplay();
                    display.display();
                    bikeStatus.displayStatusTextRemoveTimeStamp = 0;
                }
                else {
                    // Show progress bar
                    int xLineStart = DISPLAY_SCREEN_WIDTH * timeElapsed / bikeStatus.displayOffWaitTime / 2;
                    int xLineEnd = DISPLAY_SCREEN_WIDTH - xLineStart;
                    display.drawLine(0, 0, DISPLAY_SCREEN_WIDTH, 0, SSD1306_BLACK);
                    display.drawLine(xLineStart, 0, xLineEnd + 2, 0, SSD1306_WHITE);
                    display.display();
                    bikeStatus.displayOffProgressRunning = true;
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

        void displayOffRemove() {
            // Hide progress bar
            bikeStatus.displayOffTimestamp = 0;
            bikeStatus.displayOffProgressRunning = false;
            int y = DISPLAY_SCREEN_HEIGHT-1;
            display.drawLine(0, y, DISPLAY_SCREEN_WIDTH, y, SSD1306_BLACK);
        };


};