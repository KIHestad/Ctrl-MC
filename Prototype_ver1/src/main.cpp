#include <Arduino.h>
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <models.h>
#include <_config.h>
#include <setup.h>
#include <utils.h>
#include <test.h>
#include <controlIgnition.h>
#include <controlIndicators.h>
#include <controlHorn.h>
#include <controlLights.h>
#include <controlDisplay.h>

Setup setupActions; // Arduione pins allocation
Test test; // Enable testing classes
// ControlDisplay controlDisplay; // Controller for display
BikeStatus bikeStatus; // The bike properties, affected by and limits / controls how control switches works
// // Features
ControlIgnition controlIgnition; // Main control for turning on/off the iginition = enable the controllers features
ControlHorn controlHorn; // Signal horn
ControlIndicators controlIndicators; // Indicators / Turn signals
ControlLights controlLights; // Lights off/park/on - high/low beam 
#define DISPLAY_SCREEN_ADDRESS 0x3C                     // Check the display for address
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  // Init
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Ctrl-MC Started");
  // Display
  Serial.println("DISPLAY ON");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_SCREEN_ADDRESS)) {
      Serial.println(F("DISPLAY (SSD1306) ALLOCATION FAILED"));
      for(;;); // Don't proceed, loop forever
  }
  Serial.println("Display");
  display.display();
  delay(1000);
  Serial.println("Clear");
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10,20);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Ctrl-MC"));


  // Globals actions
  //controlDisplay.TurnOn();
  setupActions.setPinMode();
  setupActions.initButtonStatusHisory();
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