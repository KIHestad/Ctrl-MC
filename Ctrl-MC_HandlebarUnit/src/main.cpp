#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <models.h>
#include <_config.h> // To be user edited to set controllers features
BikeStatus bikeStatus;
#include <controlDisplay.h>
ControlDisplay controlDisplay;
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
  // Check for power off display
  controlDisplay.displayOffProgress();
  // Depending on ignition status allow different operations
  if (bikeStatus.ignition != ignOn) {
    // Ignintion is not on = off or in password mode
    controlIgnition.checkForPassword();
  }
  else {
    // Ignition is on, allow operations
    controlIgnition.checkForTurnOff();
  }

}