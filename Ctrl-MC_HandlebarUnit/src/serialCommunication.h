/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class SerialCommunication {
    
    private:

        void displayError(String error, int code) {
            displayError(error + code);
        }

        void displayError(String error) {
            display.clearDisplay();
            Image image = Image();
            image.warning();
            controlDisplay.statusTextShow(error);
        }

    public:

        SerialCommunicationDataReceived send(uint8_t code) {
            // Send code as char, and include checksum to relay unit
            Serial.write(code);
            Serial.write(255-code);
            return read();
        }

        SerialCommunicationDataReceived send(uint8_t code, uint8_t expectedResponseCode) {
            SerialCommunicationDataReceived response = send(code);
            // Validate received data against expected response code
            if (response.success && response.code != expectedResponseCode) {
                displayError("INVALID RESPONSE"); 
                response.success = false;
            }
            return response;
        }
        
        SerialCommunicationDataReceived read() {
            // Prepare model
            SerialCommunicationDataReceived response = SerialCommunicationDataReceived();
            response.success = false;
            // Wait for reply or timeout
            uint8_t responseCode = 0;
            uint8_t responseCRC = 0;
            bool responseCodeRetrieved = false;
            bool responseCRCRetrived = false;
            unsigned long timeoutTimestamp = millis() + 500; // milliseconds before timeout
            // Check for data in serial buffer within timeout period, read code then CRC 
            while (!responseCRCRetrived && millis() < timeoutTimestamp)
            {
                if (Serial.available() > 0) {
                    if (!responseCodeRetrieved) {
                        responseCode = Serial.read();
                        responseCodeRetrieved = true;
                    }
                    else {
                        responseCRC = Serial.read();
                        responseCRCRetrived = true;
                    }
                }
            }
            // Check if response data retrieved
            if (!responseCodeRetrieved && !responseCRCRetrived) {
                displayError("COM TIMEOUT"); 
                return response;
            }
            else if (!responseCRCRetrived) {
                displayError("COM MISSING CRC");
                return response;
            }
            else if (!responseCodeRetrieved) {
                displayError("COM MISSING DATA"); 
                return response;
            }
            CodeToHandlebarUnit handlebarUnitCodes = CodeToHandlebarUnit();
            // Return error responses
            if (responseCode != 255-responseCRC) {
                displayError("BAD READ (CRC)"); 
                return response;
            }
            else if (responseCode == handlebarUnitCodes.errorChecksumValidationFailed) {
                displayError("BAD WRITE (CRC)"); 
                return response;
            }
            else if (responseCode == handlebarUnitCodes.errorUnknownCode) {
                displayError("UNKNOWN CODE:"); 
                return response;
            }
            // All fine
            response.success = true;
            response.code = responseCode;
            response.codeGroup = responseCode / 10;
            return response;
        }

        void handshake() {
            if (!bikeStatus.communicationOK || millis() > bikeStatus.communicationLastPing + (SYSTEM_HANDSHAKE_CHECK_INTERVAL * 1000)) {
                // TODO: Only display message if selected
                if (false) {
                    controlDisplay.statusTextShow("HANDSHAKE START");
                }
                // Try send ping to relay module
                CodeToRelayUnit codeToRelayUnit = CodeToRelayUnit();
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                SerialCommunicationDataReceived response = send(codeToRelayUnit.requestHandshake);
                // Check response, if comm falure or invalidg hanshake code response retry communication
                if (response.success && response.code == codeToHandlebarUnit.successHandshake)
                {
                    // Handshake OK
                    bikeStatus.communicationOK = true;
                    bikeStatus.communicationLastPing = millis();
                    // TODO: Only display message if selected
                    if (false) {
                        // Show status text for a short time
                        controlDisplay.statusTextShow("HANDSHAKE SUCCESS");
                        bikeStatus.displayStatusTextRemoveTimeStamp = (millis() + DISPLAY_STATUSTEXT_OFF_WAIT_TIME);
                    }
                }
                else {
                    // Handshake failed, if comm success but invalid response code, show status text message
                    if (response.success && response.code != codeToHandlebarUnit.successHandshake) {
                        controlDisplay.statusTextShow("HANDSHAKE FAILED");
                    }
                    // Initiate retry by setting bike status to comm failure
                    bikeStatus.communicationOK = SYSTEM_HANDSHAKE_IGNORE_COMM_ERROR;  // normally set to false, for debugging it can be set to true
                    if (!SYSTEM_HANDSHAKE_IGNORE_COMM_ERROR) {
                        delay(3000);
                        display.clearDisplay();
                        Image image = Image();
                        controlDisplay.statusTextShow("RECONNECTING");
                        image.retry();
                        delay(2000);
                    }
                    else {
                        bikeStatus.communicationLastPing = millis() + (1000 * 60 * 60); // When SYSTEM_HANDSHAKE_IGNORE_COMM_ERROR is set true, do not check comm for a while
                    }
                }
            }
        }

};