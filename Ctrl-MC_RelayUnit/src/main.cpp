/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <Arduino.h>
#include <DHT.h>
#include <models.h>
#include <codes.h>
#include <_config.h> // To be user edited to enable/disable features and configure arduino board
#include <utils.h>
#include <init.h>
#include <serialCommunication.h>
#include <action.h>

SerialCommunication serialCommunication;

void setup() {
    Serial.begin(9600);
    Init init;
    init.run();
    serialCommunication = SerialCommunication();
}

void loop() {
    // Check for incoming data from handlebar unit, if found also trigger action
    SerialCommunicationDataReceived dataReceived = serialCommunication.read();
    if (dataReceived.success) {
        Action action = Action();
        action.checkReceivedData(dataReceived);
    }

    // Check for repeated actions, ex: turn signal blink, horn alarm signal

    // Check for input signals to send to handlebar unit, ex: temperature, neutral switch, oil pressure, running engine

}