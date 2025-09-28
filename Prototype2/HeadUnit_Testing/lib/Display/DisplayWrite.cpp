#include "Display.h"

void Display::speed(int speed) {
    // Clear speed area
    clearArea(0, 0, displayWidth, speedHeight);
    // Draw speed
    u8g2.setFont(u8g2_font_speed);
    int xPos = (displayWidth - u8g2.getStrWidth(String(int(speed)).c_str())) / 2; // Center text horizontally
    u8g2.drawStr(xPos, speedHeight, String(int(speed)).c_str());
}

void Display::rpm(float rpm) {
    // Create string with rpm value as format "0000"
    char rpmString[5]; // Buffer for 4 digits + null terminator
    snprintf(rpmString, sizeof(rpmString), "%04d", int(rpm));
    u8g2.setFont(u8g2_font_speed_small);
    // Righ align text in rpm area
    int textWidth = u8g2.getStrWidth(rpmString);
    int xPos = displayWidth - contentMargin - textWidth;
    int yPos = speedHeight + dividerTotalHeight + rpmHeight + 1;
    // Clear rpm area
    clearArea(xPos, yPos - textStandardHeight, textWidth, textStandardHeight);
    // Write new rpm value
    u8g2.drawStr(xPos, yPos, rpmString);
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
    // Find new position
    int yPos = displayHeight - menuHeight + 2; // top of menu area = y position of checkboxes + 2 for centering in menu area
    int xPos = currentPage * (menuItemSize + spacingWidth) + 2 ; // not use contentMargin here, fixed for centering in menu area
    // Clear previous position
    int previousPage = currentPage == 0 ? menuItemsCount - 1 : currentPage - 1;
    int xPosPrev = previousPage * (menuItemSize + spacingWidth) + 2;
    // Draw previous position as empty solid box
    u8g2.setDrawColor(0);
    u8g2.drawBox(xPosPrev + 2, yPos, menuItemSize - 4,  menuItemSize - 4);
    // Draw new position as filled solid box
    u8g2.setDrawColor(1);
    u8g2.drawBox(xPos + 2, yPos, menuItemSize - 4,  menuItemSize - 4);
}