#include <Arduino.h>
#include <_config.h>
#include <setup.h>
#include <models.h>
#include <utils.h>
#include <controlIgnition.h>
#include <controlIndicators.h>
#include <controlHorn.h>
#include <controlLights.h>

PinSetup pin; // arduione pins allocation
BikeStatus bikeStatus; // the bike properties, affected by and limits / controls how control switches works
ControlIgnition controlIgnition; // main control for engine start/stop
ControlIndicators controlIndicators; // manages the handlebar switch buttons for indicators
ControlHorn controlHorn; // manages the handlebar horn switch buttons
ControlLights controlLights; // manages the handlebar light switch buttons

void setup() {
  // init
  Serial.begin(9600);
  // construct classes
  pin = PinSetup();
  pin.setPinMode();
  bikeStatus = BikeStatus();
  controlIndicators = ControlIndicators();
  controlHorn = ControlHorn();
}

void loop() {
  // Regradless of ignition status check the ignition control, gives option to turn of the ignition
  bikeStatus = controlIgnition.action(bikeStatus);
  // Orhter controls are only available when bike is turned on
  if (bikeStatus.ignitionStatus != ignitionOff) {
    // ignition is turned on, check all controls
    bikeStatus = controlIndicators.action(bikeStatus);
    bikeStatus = controlHorn.action(bikeStatus);
  }
}