// external libs
#include <Arduino.h>
#include <EEPROM.h>
#include <DHT.h>

// private libs
#include "Display.h"
Display display; // For output to display

// includes
#include "Storage.h"
#include "Data.h"
#include "Button.h"
#include "ButtonEvent.h"
#include "WheelSensor.h"
#include "DisplayEvent.h"

Storage storage; // For storing data to flash memory
Data data; // Main data and variables
Button button(33); // Button data and functions, set pin for button
ButtonEvent buttonEvent; // For handling button events
WheelSensor wheelSensor; // For detecting wheel rotation and calculating speed
DHT dht(27, DHT22); // DHT sensor for temperature and humidity
DisplayEvent displayEvent; // For handling display update events

#include "Interrupts.h"

void setup(void) {
  // Start serial for debugging
  Serial.begin(9600);
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
  // Check if display needs update
  if (displayEvent.displayNeedsUpdate(data)) {
    // Display needs update, first check for wheel rotation to update speed
    wheelSensor.checkForRotations(storage, data);
    // Then output to display
    displayEvent.output(data, button, dht);
  }
}
