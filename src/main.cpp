#include <Arduino.h>
#include <models.h>
#include <_config.h>
#include <setup.h>
#include <utils.h>
#include <test.h>
#include <controlIgnition.h>
#include <controlIndicators.h>
#include <controlHorn.h>
#include <controlLights.h>

PinSetup pinSetup; // Arduione pins allocation
Test test; // Enable testing classes
BikeStatus bikeStatus; // The bike properties, affected by and limits / controls how control switches works
// Features
ControlIgnition controlIgnition; // Main control for turning on/off the iginition = enable the controllers features
ControlHorn controlHorn; // Signal horn
ControlIndicators controlIndicators; // Indicators / Turn signals
ControlLights controlLights; // Lights off/park/on - high/low beam 

void setup() {
  // Init
  Serial.begin(9600);
  pinSetup.setPinMode();
  Serial.println("Ctrl-MC Started");
}

void loop() {
  // Run tests if enabled
  if (TEST_READ_ENABLED_INPUTS)
    test.displayInputs();
  // Regradless of ignition status check the ignition control, gives option to turn on or off the ignition
  bikeStatus = controlIgnition.action(bikeStatus);
  // Orhter controls are only available when bike is turned on
  if (bikeStatus.ignitionStatus != ignitionOff && bikeStatus.ignitionStatus != ignitionPasswordStart)  {
    // ignition is turned on, check all controls
    bikeStatus = controlIndicators.action(bikeStatus);
    bikeStatus = controlHorn.action(bikeStatus);
  }
}