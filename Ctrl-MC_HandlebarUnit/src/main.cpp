/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

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
#include <controlDisplayMenu.h>
ControlDisplayMenu controlDisplayMenu;
#include <controlHandlebarButtons>
ControlHandlebarButtons controlHandlebarButtons;
#include <serialCommunication.h>
SerialCommunication serialCommunication;
#include <controlIgnition.h>
ControlIgnition controlIgnition;
#include <setup.h>

void setup() {
  // Init
  Serial.begin(9600);
  // Setup initial values
  Setup setup = Setup();
  setup.init();
}

void loop() {
  // Check for power off display and remove status text
  controlDisplay.displayOffProgress();
  // Depending on ignition status allow different operations
  if (bikeStatus.ignition != ignOn) {
    // Ignintion is not on = off or in password mode
    controlIgnition.checkForPassword();
  }
  else {
    // Ignition is on, allow operations, inititate handshake to check that communication to relay unit is working
    serialCommunication.handshake();
    // Check for start / stop engine
    controlIgnition.checkForStartStopEngine();
    // Check for selected menu
    controlDisplayMenu.checkForMenuAction();
    // CHeck handlebarbuttons
    controlHandlebarButtons.checkForButtonAction();
  }

}