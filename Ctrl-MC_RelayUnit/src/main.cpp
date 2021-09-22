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
// Relays
#include <relayIgnition.h>

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
    SerialCommunicationDataReceived data = serialCommunication.read();
    if (data.success) {
        
        if (data.codeGroup == codeGroupReceived.ignition) {
            RelayIgnition r = RelayIgnition();
            r.action(data);            
        }
        else {
            CodeToHandlebarUnit responseCode = CodeToHandlebarUnit();
            serialCommunication.send(responseCode.errorChecksumValidationFailed);
        }
    }
}