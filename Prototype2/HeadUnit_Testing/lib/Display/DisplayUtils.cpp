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

void Display::drawDiagonalLine(int x1, int y1, int x2, int y2, int thickness) {
    // Calculate perpendicular offsets
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx*dx + dy*dy);
    
    float perpX = -dy / length * (thickness / 2.0);
    float perpY = dx / length * (thickness / 2.0);
    
    // Calculate the four corners of the thick line
    int x1a = x1 + (int)perpX;
    int y1a = y1 + (int)perpY;
    int x1b = x1 - (int)perpX;
    int y1b = y1 - (int)perpY;
    int x2a = x2 + (int)perpX;
    int y2a = y2 + (int)perpY;
    int x2b = x2 - (int)perpX;
    int y2b = y2 - (int)perpY;
    
    // Draw two triangles to form the thick line
    u8g2.drawTriangle(x1a, y1a, x1b, y1b, x2a, y2a);
    u8g2.drawTriangle(x1b, y1b, x2a, y2a, x2b, y2b);
}

void Display::drawRectangle(int x1, int y1, int x2, int y2) {
    int x = min(x1, x2);
    int y = min(y1, y2);
    int width = abs(x2 - x1);
    int height = abs(y2 - y1);
    u8g2.drawBox(x, y, width, height);
}