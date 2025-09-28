#include "Display.h"

void Display::clearArea(int x, int y, int w, int h) {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, w, h);
    u8g2.setDrawColor(1);
}

void Display::textCentered(unsigned int yPos, const char* text) {
    int stringWidth = u8g2.getStrWidth(text);
    int xPos = (displayWidth - stringWidth) / 2;
    u8g2.drawStr(xPos, yPos, text);
}

int Display::getTextRowYPos(int row) {
    // Find page area top position + top margin
    int yTopPos = speedHeight + rpmHeight + (dividerTotalHeight * 2) + 1;
    // Add row + spacing between rows
    yTopPos += ((row - 1) * textStandardHeight) + (4 * row);
    // Add height of text to get baseline position
    return yTopPos + textStandardHeight; 
}

void Display::textOrNumRowClear(int row) {
    // Get y position for the specified row
    int yPos = getTextRowYPos(row);
    // Clear the area for the specified row
    clearArea(0, yPos - textStandardHeight, displayWidth, textStandardHeight);
}

// Expect row to be 1, 2 or 3 for bottom text lines, row 3 is bottom line
void Display::textOrNumRowDisplay(int row, const char* text, bool isNumber) {
    // Get y position for the specified row
    int yPos = getTextRowYPos(row);
    // Clear the area for the specified row
    clearArea(0, yPos - textStandardHeight, displayWidth, textStandardHeight);
    // Font selection
    if (isNumber) {
        u8g2.setFont(u8g2_font_speed_small); 
    } else {
        u8g2.setFont(u8g2_font_tenthinnerguys_tf); 
    }
    // Calculate text width
    int textWidth = u8g2.getStrWidth(text);
    // Center text horizontally
    int xPos = (displayWidth - textWidth) / 2;
    // Draw text
    u8g2.drawStr(xPos, yPos, text);
}

// Expect row to be 1, 2 or 3 for bottom text lines, row 3 is bottom line
void Display::textOrNumRowDisplay(int row, int xPos, const char* text) {
    // Get y position for the specified row
    int yPos = getTextRowYPos(row);
    // Clear the area for the specified row
    clearArea(0, yPos - textStandardHeight, displayWidth, textStandardHeight);
    u8g2.setFont(u8g2_font_speed_small); 
    // Draw text
    u8g2.drawStr(xPos, yPos, text);
}

void Display::divider(int yPos) {
    yPos += dividerTotalHeight / 2; // center the line in the divider area
    u8g2.drawHLine(0, yPos, displayWidth);
}