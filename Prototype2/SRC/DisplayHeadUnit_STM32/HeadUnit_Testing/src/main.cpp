// external libs
#include <Arduino.h>
#include <EEPROM.h>
#include <DHT.h>
#include <Wire.h>

// private libs
#include "Display.h"
#include "Globals.h"  // For u8g2 global object
Display display; // For output to display

// includes
#include "Storage.h"
#include "Data.h"
#include "Button.h"
#include "ButtonEvent.h"
#include "WheelSensor.h"
#include "RpmSensor.h"
#include "DisplayEvent.h"

Storage storage; // For storing data to flash memory
Data data; // Main data and variables
Button button(data.pinButton); // Button data and functions, set pin for button
ButtonEvent buttonEvent; // For handling button events
WheelSensor wheelSensor; // For detecting wheel rotation and calculating speed
RpmSensor rpmSensor; // For detecting engine rpm
DHT dht(data.pinDhtSensor, DHT22); // DHT sensor for temperature and humidity
DisplayEvent displayEvent; // For handling display update events

#include "Interrupts.h"

void setup(void) {
  // Start serial for debugging
  // Serial.begin(115200);

  // Setup I2C for OLED display
  pinMode(PA8, INPUT_PULLUP);
  pinMode(PA9, INPUT_PULLUP);
  Wire.setSDA(PA8);
  Wire.setSCL(PA9);
  Wire.begin();  
  // Initialize Flash Storage, set data from storage
  storage.init(); // run: storage.reset(); to reset all stored values
  // Initialize main data, set values from storage
  data.init(storage.data);
  // Init temp/humidity sensor
  dht.begin();
  // Initialize display hardware
  display.init(data.engineRpmMax, data.engineRpmDanger, data.engineRpmWarning, data.fuelTankCapacity, data.fuelAvgConsumption);
  display.startupAnimation(data.fuelLevel);
  // Initialize interrupt for hall sensor
  interruptsInit();
}

void loop(void) {
  // button read to update its state
  button.read();
  // check for button events
  buttonEvent.action(data, button, storage);
  // Normal loop code
  data.currentMs = millis();
  // Check if display needs regular update
  if (displayEvent.displayNeedsRegularUpdate(data)) {
    // Display needs update, first check for wheel rotation to update speed
    wheelSensor.checkForRotations(storage, data);
    // Then check for rpm sensor to update rpm
    rpmSensor.checkForRotations(data);
    // Then output to display
    displayEvent.mainOutput(data, button, dht);
  }
  // Check if display needs rpm update only
  else if (displayEvent.displayNeedsRpmUpdate(data)) {
    // Then check for rpm sensor to update rpm
    rpmSensor.checkForRotations(data);
    // Then output to display
    displayEvent.rpmOutput(data);
  }

}
