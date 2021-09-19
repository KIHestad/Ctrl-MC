
Adafruit_SSD1306 display(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, &Wire, DISPLAY_SCREEN_ADDRESS);
#include <image.h>

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
                Serial.println(F("Display (SSD1306) allocation failed"));
                for(;;); // HALT - Don't proceed, loop forever
            }
            display.setTextSize(DISPLAY_TEXT_SIZE);
            display.setTextColor(SSD1306_WHITE);
            Serial.println("Display OK");
            showSplash();
            bikeStatus.displayOffTimestamp = millis();
        };

        // Show splash screen
        void showSplash() {
            Image image = Image();
            image.kiHestadLogo();
            delay(3000);
            display.clearDisplay();
            setCursorForCenteredText(1, 7);
            display.println(F("Ctrl-MC"));
            display.display();
            delay(500);
            setCursorForCenteredText(2, 21);
            display.println(F("Motorcycle Controller"));
            display.display();
            delay(500);
            setCursorForCenteredText(3, 12);
            display.println(F("by KI Hestad"));
            display.display();
            delay(500);
        };

        // Write status text at bottom of display, remove any other text in that area first
        void prepareForStatusText(int textLength) {
            display.fillRect(0, DISPLAY_SCREEN_HEIGHT-DISPLAY_TEXT_CHAR_HEIGHT -1, DISPLAY_SCREEN_WIDTH, DISPLAY_TEXT_CHAR_HEIGHT +1, SSD1306_BLACK); 
            display.setCursor(getXposForCenterText(textLength), DISPLAY_SCREEN_HEIGHT - DISPLAY_TEXT_CHAR_HEIGHT); 
        };

        // Turn off display by clearing content after a timeout period, show progressbar until display off
        void displayOffProgress() {
            if (bikeStatus.displayOffTimestamp > 0) {
                long timeElapsed = millis() - bikeStatus.displayOffTimestamp;
                // Check for power off
                if (timeElapsed > bikeStatus.displayOffWaitTime) {
                    // Power off now
                    displayOffCancel();
                    display.clearDisplay();
                    display.display();
                }
                else {
                    // Show progress bar
                    int y = DISPLAY_SCREEN_HEIGHT-1;
                    int xLineStart = DISPLAY_SCREEN_WIDTH * timeElapsed / bikeStatus.displayOffWaitTime / 2;
                    int xLineEnd = DISPLAY_SCREEN_WIDTH - xLineStart;
                    display.drawLine(0, y, DISPLAY_SCREEN_WIDTH, y, SSD1306_BLACK);
                    display.drawLine(xLineStart, y, xLineEnd + 2, y, SSD1306_WHITE);
                    display.display();
                    bikeStatus.displayOffProgressRunning = true;
                }
            }
        };

        void displayOffCancel() {
            // Hide progress bar
            bikeStatus.displayOffTimestamp = 0;
            bikeStatus.displayOffProgressRunning = false;
            int y = DISPLAY_SCREEN_HEIGHT-1;
            display.drawLine(0, y, DISPLAY_SCREEN_WIDTH, y, SSD1306_BLACK);
        };


};