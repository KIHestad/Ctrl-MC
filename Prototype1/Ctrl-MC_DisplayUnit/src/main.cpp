/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// External libaries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>

// Init U8G2 library for outpur to OLED display
// U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0); //, /* reset=*/ U8X8_PIN_NONE); // Page buffer mode - USING I2C
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, 5, 3, 1); // Using SPI, parameters: landscape rotation, pins for cs, dc and reset


// Common lbraries
#include "../../Ctrl-MC_Common/lib/SerialCommunication/SerialCommunication.h" // Ctrl-MC_Common/lib
#include "../../Ctrl-MC_Common/lib/Config/Config.h" // Ctrl-MC_Common/lib -> To be user edited to enable/disable features and configure arduino board
SerialCommunication serialCommunication;
#include "../../Ctrl-MC_Common/lib/OnBoardLed/OnBoardLed.h" // Ctrl-MC_Common/lib
OnBoardLed onBoardLed;

// Project includes
#include <BikeStatus.h>
BikeStatus bikeStatus;
#include <Button.h>
Button btnClutch;
Button btnIndicatorLeft;
Button btnIndicatorRight;
Button btnLightsHiLo;
Button btnMenuMain;
Button btnMenuStartStop;
Button btnBrakeFront;
Button btnHorn;
#include <ButtonHelper.h>
#include <DisplayImage.h>
#include <DisplayHelper.h>
DisplayHelper displayHelper;
#include <DisplayMenu.h>
DisplayMenu displayMenu;
#include <ButtonEvent.h>
ButtonEvent buttonEvent;
#include <Action.h>
Action action;
// Features
#include <TestButtons.h>
TestButtons testButtons;
#include <IgnitionButtonPassword.h>
IgnitionButtonPassword ignitionButtonPassword;
// Iniate class
#include <init.h>

void setup() {
    // Setup initial values
    Init init = Init();
    init.run();
}

void loop() {
    // Check for incoming serial data from relay unit
    SerialCommunication::Data serialData = SerialCommunication::Data();
    serialData = serialCommunication.read();
    if (serialData.received) 
        action.checkReceivedData(serialData);
    // Check progress for switching back to status page
    displayHelper.displayTimeout();
    // Depending on ignition status allow different operations
    if (bikeStatus.ignition != BikeStatusIgnition::ignOn) {
        // Ignintion is not on, meaning it is off or in password mode
        // Check for button testing
        testButtons.loopAction();
        // Check for turning on ignintion using button password
        ignitionButtonPassword.loopAction();
    }
    else {
        // Ignition is on, allow operations, inititate handshake to check that communication to relay unit is working
        action.performHandshake();
        // Check for selected menu
        displayMenu.loopAction();
        // Check handlebarbuttons
        buttonEvent.loopAction();
        // Check for runnning actions
        action.indicatorBlink();
    }

}