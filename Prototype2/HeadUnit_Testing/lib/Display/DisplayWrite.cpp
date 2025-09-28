#include "Display.h"
#include "ImageElefant.cpp" // Include the image data

void Display::speed(int speed) {
    // Clear speed area
    clearArea(0, 0, displayWidth, speedHeight);
    // Draw speed
    u8g2.setFont(u8g2_font_speed);
    int xPos = (displayWidth - u8g2.getStrWidth(String(int(speed)).c_str())) / 2; // Center text horizontally
    u8g2.drawStr(xPos, speedHeight, String(int(speed)).c_str());
}

void Display::rpm(float rpm) {
    // Clear whole rpm area
    clearArea(0, speedHeight + dividerTotalHeight, displayWidth, rpmHeight + 1);
    backgroundRpm(); // Redraw static background elements
    // Create string with rpm value as format "0000"
    char rpmString[9]; // Buffer for 4 digits + null terminator
    snprintf(rpmString, sizeof(rpmString), "%04d", int(rpm));
    u8g2.setFont(u8g2_font_speed_medium);
    // Righ align text in rpm area
    int textWidth = u8g2.getStrWidth(rpmString);
    int xPos = displayWidth - contentMargin - textWidth;
    int yPos = speedHeight + dividerTotalHeight + rpmHeight + 1;
    // Write new rpm value
    u8g2.drawStr(xPos, yPos, rpmString);
    // Prepare graph, center line on grapth = 77 pixels total
    int rpmVerticalBarMax = 19; // 25%
    int rpmSlantedBarMax = 7; // 10%
    int rpmHorizontalBarMax = 51; // 65%
    // Calculate filled length based on rpm value
    int rpmBarLength = (int)round(rpm / rpmGaugeMax * 77);
    // Fist part vertical bar from bottom
    int rpmBarPart = min(rpmBarLength, rpmVerticalBarMax);
    if (rpmBarPart >= 0) {
        xPos = contentMargin + 2;
        yPos = speedHeight + dividerTotalHeight + rpmHeight - 1;
        drawRectangle(xPos, yPos, xPos + rpmGraphWidth - 3, yPos - rpmBarPart);
        // Second part slanted bar
        rpmBarLength -= rpmBarPart;
        rpmBarPart = min(rpmBarLength, rpmSlantedBarMax);
        if (rpmBarPart >= 0) {
                
            xPos = contentMargin + (rpmGraphWidth / 2);
            yPos -= rpmVerticalBarMax - 2;
            drawDiagonalLine(xPos, yPos, xPos + rpmBarPart, yPos - rpmBarPart, 9);
            // Third part horizontal bar
            rpmBarLength -= rpmBarPart;
            rpmBarPart = min(rpmBarLength, rpmHorizontalBarMax);
            if (rpmBarPart >= 0) {
                xPos = contentMargin + rpmSlantedBarMax + 2;
                yPos = speedHeight + dividerTotalHeight + 2;
                u8g2.drawBox(xPos, yPos, rpmBarPart, 7);
            }
        }
    }
    
}

void Display::fuel(float fuelLevel) {
    // Bar
    int xPos = 14;
    int yPos = speedHeight + dividerTotalHeight + rpmHeight + dividerTotalHeight + 8;
    int maxWidth = displayWidth - xPos - 3;
    float fuelLevelInPercentages = fuelLevel / fuelTankCapacity;
    int barWidth = (int)round(fuelLevelInPercentages * maxWidth);
    int barHeight = textStandardHeight - 4;
    // Clear progressbar area
    clearArea(xPos, yPos, maxWidth, barHeight);
    // Set progressbar area
    u8g2.setDrawColor(1);
    u8g2.drawBox(xPos, yPos, barWidth, barHeight);
    // Prepare Fuel litres text
    u8g2.setFont(u8g2_font_speed_small); 
    char txt[10];
    if (fuelLevel >= 10) {
        sprintf(txt, "%dl", (int)round(fuelLevel));
    }
    else {
        sprintf(txt, "%.1fl", fuelLevel);
    }
    yPos += (textStandardHeight * 2) + 2;
    // Clear text area
    clearArea(0, yPos - textStandardHeight, displayWidth, textStandardHeight);
    // Write Fuel litres text
    u8g2.drawStr(contentMargin, yPos, txt);
    // Remaining kilometers based on average consumption
    float km = fuelLevel / fuelAvgConsumption * 100.0;
    sprintf(txt, "%dkm", (int)round(km));
    int stringWidth = u8g2.getStrWidth(txt);
    u8g2.drawStr(displayWidth - stringWidth - contentMargin, yPos, txt);
}

void Display::clearPageArea() {
    // Clear page area
    int yPos = speedHeight + rpmHeight + 2*dividerTotalHeight;
    int height = pageHeight;
    clearArea(0, yPos, displayWidth, height);
}

void Display::clearMenuArea() {
    // Clear the menu area at the bottom of the display
    int yPos = speedHeight + rpmHeight + 2*dividerTotalHeight + pageHeight;
    clearArea(0, yPos, displayWidth, displayHeight - yPos);
}

void Display::rowText(int row, const char* text) {
    // Expect row to be 1 or 2
    textOrNumRowDisplay(row, text, false);
}

void Display::rowNum(int row, const char* text) {
    textOrNumRowDisplay(row, text, true);
}

void Display::rowTime(int row, const char* text) {
    textOrNumRowDisplay(row, 8, text);
}

void Display::rowClear(int row) {
    textOrNumRowClear(row);
}   

void Display::menuName(const char* text) {
    // Clear menu name area
    int yPos = displayHeight - menuHeight - 2;
    u8g2.setFont(u8g2_font_5x7_tf);
    clearArea(0, yPos - 7, displayWidth, 7);
    // Draw menu name centered
    textCentered(yPos, text);
}

void Display::menu(int currentPage, bool autoPager) {
    // Space between menu items
    int totalWidth = displayWidth - (2 * contentMargin);
    int spacingWidth = (totalWidth - (menuItemSize * menuItemsCount)) / (menuItemsCount - 1);
    // Page icon size
    int offsetLeft = 5;
    int width = 3;
    int height = 3;
    // Find new position
    int yPos = displayHeight - menuHeight + 2; // top of menu area = y position of checkboxes + 2 for centering in menu area
    int xPos = currentPage * (menuItemSize + spacingWidth) + offsetLeft; // not use contentMargin here, fixed for centering in menu area
    // Clear previous position
    int previousPage = currentPage == 0 ? menuItemsCount - 1 : currentPage - 1;
    int xPosPrev = previousPage * (menuItemSize + spacingWidth) + offsetLeft;
    // Draw previous position as empty solid box
    u8g2.setDrawColor(0);
    u8g2.drawBox(xPosPrev, yPos, width, height);
    // Draw new position as filled solid box
    u8g2.setDrawColor(1);
    u8g2.drawBox(xPos, yPos, width, height);
}

void Display::drawElefant() {
    // Draw elefant image at fixed position
    int xPos = (int)round((displayWidth - 56) / 2.0) + 1; // Centered horizontally
    int yPos = speedHeight + 2 * dividerTotalHeight + rpmHeight +2;
    u8g2.drawBitmap(xPos, yPos, 56/8, 46, epd_bitmap_elefantelefant_smalle2);
}