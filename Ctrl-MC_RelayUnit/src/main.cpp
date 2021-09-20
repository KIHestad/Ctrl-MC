/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

#include <Arduino.h>
#include <models.h>
#include <codes.h>
#include <_config.h> // To be user edited to enable/disable features and configure arduino board
#include <utils.h>
#include <mainInit.h>
#include <serialCommunication.h>
MainInit mainInit;
SerialCommunication serialCommunication;
CodeToRelayUnit codeReceived;
CodeGroupToRelayUnit codeGroupReceived;
Relay relay;

void setup() {
    Serial.begin(9600);
    mainInit.setPinMode();
}

void loop() {
    // Check for incoming data from handlebar unit
    SerialCommunicationData data = serialCommunication.read();
    if (data.retrieved) {
        // Data read, perform action 
        if (data.codeGroup == codeGroupReceived.ignition) {
            RelayStatus currentIgnitionStatus = relay.getStatus(OUTPUT_PIN_MAIN_IGNITION);
            if (currentIgnitionStatus != relayInactive)
            {
                RelayStatus newIgnitionStatus;
                if (data.code == codeReceived.ignitionTurnOn)
                    newIgnitionStatus = relayOn;
                else if (data.code == codeReceived.ignitionTurnOff)
                    newIgnitionStatus = relayOff;
                if (currentIgnitionStatus != newIgnitionStatus)
                    relay.set(OUTPUT_PIN_MAIN_IGNITION, newIgnitionStatus);
            }
        }
    }
}