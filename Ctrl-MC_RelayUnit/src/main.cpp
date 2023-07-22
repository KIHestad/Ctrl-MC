/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// External libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
// Common libraries
#include "../../Ctrl-MC_Common/lib/Config/Config.h" // To be user edited to enable/disable features and configure arduino board
#include "../../Ctrl-MC_Common/lib/SerialCommunication/SerialCommunication.h" 
#include "../../Ctrl-MC_Common/lib/OnBoardLed/OnBoardLed.h" 
// Initiate classes
DHT dhtSensor(Config::RelayUnitInput::tempSensor, DHT22);
SerialCommunication serialCommunication;
// Project includes
#include <Relay.h>
#include <Action.h>

OnBoardLed onBoardLed;

void setup() {
    // Serial comm
    // Serial.begin(Config::serialCommSpeed);
    HardwareSerial SerialPort(2); // use UART2
    SerialPort.begin(Config::serialCommSpeed, SERIAL_8N1, Config::serialPort_U2_RX, Config::serialPort_U2_TX);
    serialCommunication = SerialCommunication();
    serialCommunication.clearBuffer();
    // Temp sensor - to be replaced with gyre/accelerometer
    dhtSensor.begin();
    // Init relay
    Relay relay = Relay();
    relay.init();
    // Init onboard led
    Config::RelayUnitOutput ruOutput = Config::RelayUnitOutput();
    onBoardLed = OnBoardLed();
    onBoardLed.init(ruOutput.onBoardLed);
}

void loop() {
    // Check for incoming serial data from handlebar unit, if success trigger action
    SerialCommunication::Data serialData = serialCommunication.read();
    if (serialData.received) {
        Action action = Action();
        action.checkReceivedData(serialData);
    }

    // TODO: Check for input signals to relay unit, send to handlebar unit when changed, ex: neutral switch, oil pressure, running/stopped engine

}