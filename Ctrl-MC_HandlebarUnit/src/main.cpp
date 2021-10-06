/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// External libaries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Common lbraries
#include <SerialCommunication.h> // Ctrl-MC_Common/lib
// Project includes
#include <models.h>
#include <Config.h> // To be user edited to enable/disable features and configure arduino board
#include <utils.h>
BikeStatus bikeStatus;
Adafruit_SSD1306 display(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, &Wire, DISPLAY_SCREEN_ADDRESS);
#include <image.h>
#include <controlDisplay.h>
ControlDisplay controlDisplay;

#include <controlDisplayMenu.h>
ControlDisplayMenu controlDisplayMenu;
#include <controlHandlebarButtons>
ControlHandlebarButtons controlHandlebarButtons;
#include <action.h>
Action action;
#include <controlIgnition.h>
ControlIgnition controlIgnition;
#include <init.h>

SerialCommunication serialCommunication;

void setup() {
  // Init
  Serial.begin(9600);
  // Setup initial values
  Init init = Init();
  init.run();
  // Clear searial buffer
  serialCommunication = SerialCommunication();
  serialCommunication.clearBuffer();
  // Read bike status from relay unit
  // TODO 
}

void loop() {
  // Check for incoming serial data from relay unit
  SerialCommunication::Data serialData = SerialCommunication::Data();
  serialData = serialCommunication.read();
  if (serialData.received) 
    action.checkReceivedData(serialData);

  // Check progress for switching back to status page
  controlDisplay.gotoStatusPage();
  // Depending on ignition status allow different operations
  if (bikeStatus.ignition != ignOn) {
    // Ignintion is not on = off or in password mode
    controlIgnition.checkForPassword();
  }
  else {
    // Ignition is on, allow operations, inititate handshake to check that communication to relay unit is working
    action.performHandshake();
    // Check for selected menu
    controlDisplayMenu.checkForMenuAction();
    // Check handlebarbuttons
    controlHandlebarButtons.checkForButtonAction();
    // Check for runnning actions
    action.indicatorBlink();
  }

}