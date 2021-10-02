/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <models.h>
#include <codes.h>
#include <_config.h> // To be user edited to enable/disable features and configure arduino board
#include <utils.h>
BikeStatus bikeStatus;
Adafruit_SSD1306 display(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, &Wire, DISPLAY_SCREEN_ADDRESS);
#include <image.h>
#include <controlDisplay.h>
ControlDisplay controlDisplay;
#include <serialCommunication.h>
SerialCommunication serialCommunication;
#include <controlDisplayMenu.h>
ControlDisplayMenu controlDisplayMenu;
#include <controlHandlebarButtons>
ControlHandlebarButtons controlHandlebarButtons;
#include <controlIgnition.h>
ControlIgnition controlIgnition;
#include <action.h>
Action action;
#include <init.h>

void setup() {
  // Init
  Serial.begin(9600);
  // Setup initial values
  Init init = Init();
  init.run();
}

void loop() {
  // Check for data from relay unit
  SerialCommunicationDataReceived dataReceived = serialCommunication.read();
  if (dataReceived.success) {
    action.checkReceivedData(dataReceived);
  }
  // Check progress for switching back to status page
  controlDisplay.gotoStatusPage();
  // Depending on ignition status allow different operations
  if (bikeStatus.ignition != ignOn) {
    // Ignintion is not on = off or in password mode
    controlIgnition.checkForPassword();
  }
  else {
    // Ignition is on, allow operations, inititate handshake to check that communication to relay unit is working
    serialCommunication.performHandshake();
    // Check for selected menu
    controlDisplayMenu.checkForMenuAction();
    // Check handlebarbuttons
    controlHandlebarButtons.checkForButtonAction();
    // Check for runnning actions
    action.indicatorBlink();
  }

}