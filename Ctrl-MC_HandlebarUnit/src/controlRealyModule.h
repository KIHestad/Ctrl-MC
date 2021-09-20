class ControlRelayModule {
    
    public:

        void CheckCommunication() {
            if (!bikeStatus.communicationOK) {
                // Display message
                controlDisplay.prepareForStatusText(19);
                display.println(F("Connecting to Relay"));
                display.display();
                // Try send ping to relay module
                Serial.write(0); // ping signal
                Serial.write(0+128); // checksum
                // Wait for reply
                int receivedCode = -1;
                while (receivedCode == -1)
                {
                    if (Serial.available() > 0) 
                        receivedCode = Serial.read();
                }
                CodeToHandlebarUnit codeReceived = CodeToHandlebarUnit();
                // Check result and output result
                if (receivedCode == codeReceived.successSerialRead) {
                    controlDisplay.prepareForStatusText(19);
                    display.println("SUCCESS - Queue: " + Serial.available());
                    display.display();
                }
                else if (receivedCode == codeReceived.errorInvalidDataValue || receivedCode == codeReceived.errorInvalidChecksumValue || receivedCode == codeReceived.errorChecksumValidationFailed) {
                    controlDisplay.prepareForStatusText(14);
                    display.println("CHECKSUM ERROR"); 
                    display.display();
                }
                else {
                    controlDisplay.prepareForStatusText(18);
                    display.println("ERROR: " + receivedCode);
                    display.display();
                }
                delay(2000);
            }

        }

};