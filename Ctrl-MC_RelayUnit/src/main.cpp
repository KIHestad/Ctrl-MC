/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <Arduino.h>
#include <Config.h> // Ctrl-MC_Common/lib -> To be user edited to enable/disable features and configure arduino board
#include <SerialCommunication.h> // Ctrl-MC_Common/lib
#include <OnBoardLed.h>
#include <Relay.h>
#include <Action.h>
// #include <DHT.h> // Temp/Humidity sensor lib

SerialCommunication serialCommunication;

void setup() {
    Serial.begin(9600);
    Relay relay = Relay();
    relay.init();
    OnBoardLed onBoardLed = OnBoardLed();
    onBoardLed.init();
    serialCommunication = SerialCommunication();
}

void loop() {
    // Check for incoming serial data from handlebar unit, if success trigger action
    SerialCommunication::Data serialData = serialCommunication.read();
    if (serialData.received) {
        Action action = Action();
        action.checkReceivedData(serialData);
    }

    // Check for input signals to relay unit, send to handlebar unit when changed, ex: neutral switch, oil pressure, running/stopped engine

}