/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <Arduino.h>
#include <DHT.h> // Temp/Humidity sensor lib
#include <_config.h> // To be user edited to enable/disable features and configure arduino board
#include <SerialCommunication.h> // Ctrl-MC_Common/lib
#include <OnBoardLed.h>
#include <Relay.h>
#include <Action.h>

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
    // Check for incoming data from handlebar unit, if success trigger action
    SerialCommunication::Data serialData = serialCommunication.read();
    if (serialData.received) {
        Action action = Action();
        action.checkReceivedData(serialData);
    }

    // Check for repeated actions, ex: turn signal blink, horn alarm signal - consider trigger from handlebar unit, then this section is not needed

    // Check for input signals to send to handlebar unit, ex: temperature, neutral switch, oil pressure, running engine

}