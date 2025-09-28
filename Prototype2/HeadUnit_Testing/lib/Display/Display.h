#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include <U8g2lib.h>
#include <Font.h>
#include "Globals.h"  // Include shared u8g2 object declaration

class Display {

private:
    
    // General display properties
    unsigned int displayWidth; // Width of the display in pixels
    unsigned int displayHeight; // Height of the display in pixels
    const unsigned int textStandardHeight = 9; // Height of each text line
    // Speed display properties
    const unsigned int contentMargin = 1; // left and right margin for content areas
    const unsigned int dividerTotalHeight = 9; // total Height for divider, margins top/bottom included
    const unsigned int speedHeight = 30; // Height of speed output
    const unsigned int rpmHeight = 30; // Height of rpm gauge area
    const unsigned int pageHeight = 35; // Height of page controlled by menu
    const unsigned int menuHeight = 6; // Height of menu area at bottom
    // Menu pages (5): 0=fuel-graph, 1=fuel-numbers, 2=temp/humidity, 3=session, 4=trip/total
    const unsigned int menuItemsCount = 5; // Number of menu items/pages
    const unsigned int menuItemSize = 8; // Size of menu item check box, outer frame
    const unsigned int rpmGraphWidth = 10; // Width of rpm graph outer frame
    // Fixed properties set by init()
    int rpmGaugeMax;
    int rpmGaugeWarning;
    int rpmGaugeDanger;
    float fuelTankCapacity;
    float fuelAvgConsumption;
    
    // DisplayUtils.cpp -> Display Utility functions
    void textCentered(unsigned int yPos, const char* text);
    void divider(int yPos);
    void clearArea(int x, int y, int w, int h);
    int getTextRowYPos(int row);
    void textOrNumRowDisplay(int row, const char* text, bool isNumber);
    void textOrNumRowDisplay(int row, int xPos, const char* text);
    void textOrNumRowClear(int row);
    void drawDiagonalLine(int x1, int y1, int x2, int y2, int thickness);
    void drawRectangle(int x1, int y1, int x2, int y2);
    
    public:
    
    // Display Core
    void init(int rpmGaugeMax, int rpmGaugeDanger, int rpmGaugeWarning, float fuelTankCapacity, float fuelAvgConsumption);
    void splash();
    void startupAnimation(float fuelLevel);
    void clearDisplay();
    void outputNow();
    
    // Display Background
    void background();
    void backgroundRpm();
    void backgroundFuel();
    void backgroundMenu();
    
    // Display Write
    void speed(int speed);
    void rpm(float rpm);
    void fuel(float fuelLevel);
    void clearPageArea();
    void clearMenuArea();
    void menuName(const char* text);
    void menu(int currentPage, bool autoPager);
    void drawElefant();
    void rowText(int row, const char* text);
    void rowNum(int row, const char* text);
    void rowTime(int row, const char* text);
    void rowClear(int row);

};

#endif