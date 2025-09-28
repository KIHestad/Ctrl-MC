#include "Display.h"

void Display::background() {
    clearDisplay();
    backgroundRpm();
    backgroundMenuCheckboxes();
}

void Display::backgroundRpm() {
    // Frame for rpm graphic
    int yPosTop = speedHeight + dividerTotalHeight;
    int width = displayWidth - (2 * contentMargin);
    int slantedCorner = 8;
    int slCornerInner = 5;
    u8g2.drawLine(contentMargin + slantedCorner, yPosTop, displayWidth - contentMargin -1, yPosTop); // top - top-horizontal
    u8g2.drawLine(displayWidth - contentMargin -1, yPosTop, displayWidth - contentMargin -1, yPosTop + rpmGraphWidth); // top - right vertical
    u8g2.drawLine(displayWidth - contentMargin -1, yPosTop + rpmGraphWidth, contentMargin + rpmGraphWidth + slCornerInner, yPosTop + rpmGraphWidth); // top - bottom horizontal
    u8g2.drawLine(contentMargin + rpmGraphWidth + slCornerInner, yPosTop + rpmGraphWidth, contentMargin + rpmGraphWidth, yPosTop + rpmGraphWidth + slCornerInner); // slanted corner inner
    u8g2.drawLine(contentMargin + rpmGraphWidth, yPosTop + rpmGraphWidth + slCornerInner, contentMargin + rpmGraphWidth, yPosTop + rpmHeight); // left - right vertical
    u8g2.drawLine(contentMargin + rpmGraphWidth, yPosTop + rpmHeight, contentMargin, yPosTop + rpmHeight); // left - bottom horoizontal
    u8g2.drawLine(contentMargin, yPosTop + rpmHeight, contentMargin + rpmGraphWidth, yPosTop + rpmHeight); // bottom horizontal
    u8g2.drawLine(contentMargin, yPosTop + rpmHeight, contentMargin, yPosTop + slantedCorner); // left vertical
    u8g2.drawLine(contentMargin, yPosTop + slantedCorner, contentMargin + slantedCorner, yPosTop); // Slant top-left corner
    
    // Write rpm icon
    u8g2.setFont(u8g2_font_speed_small);
    int textWidth = u8g2.getStrWidth("<0000");
    int xPos = displayWidth - contentMargin - textWidth;
    int yPos = speedHeight + dividerTotalHeight + rpmHeight + 1;
    u8g2.drawStr(xPos, yPos, "<");
}

void Display::backgroundFuel() {
    // Fuel icon
    u8g2.setFont(u8g2_font_speed_small);
    int xPos = contentMargin; 
    int yPos = speedHeight + dividerTotalHeight + rpmHeight + dividerTotalHeight + textStandardHeight + 6;
    u8g2.drawStr(xPos, yPos, ">");
    // Frame for fuel level bar
    int barX = 12;
    int barY = yPos - textStandardHeight; // Align bottom of text   
    int barWidth = displayWidth - barX - contentMargin;
    int barHeight = textStandardHeight; 
    u8g2.drawFrame(barX, barY, barWidth, barHeight);
}

void Display::backgroundMenuCheckboxes() {
    // Space between menu items
    int totalWidth = displayWidth - (2 * contentMargin);
    int spacingWidth = (totalWidth - (menuItemSize * menuItemsCount)) / (menuItemsCount - 1);
    int yPos = displayHeight - menuHeight; // top of menu area = y position of checkboxes
    // Checkbox position
    for (int i = 0; i < menuItemsCount; i++) {
        int xPos = i * (menuItemSize + spacingWidth) + 2; // not use contentMargin here, fixed for centering in menu area
        u8g2.drawFrame(xPos, yPos, menuItemSize, menuItemSize);
    }
}