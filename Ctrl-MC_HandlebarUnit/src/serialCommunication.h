/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

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
            uint8_t responseCode;
            uint8_t responseCRC;
            bool responseCodeRetrieved = false;
            bool responseCRCRetrived = false;
            long timeNowTimestamp = millis();
            long timeoutTimestamp = timeNowTimestamp + 500; // milliseconds before timeout
            // Check for data in serial buffer within timeout period, read code then CRC 
            while ((!responseCodeRetrieved && !responseCRCRetrived) || timeNowTimestamp < timeoutTimestamp)
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
                timeNowTimestamp = millis();
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
            if (!bikeStatus.communicationOK || millis() > bikeStatus.communicationLastPing + (RELAY_UNIT_PING_INTERVAL * 1000)) {
                // Display message
                controlDisplay.statusTextShow("HANDSHAKE START");
                // Try send ping to relay module
                CodeToRelayUnit codeToRelayUnit = CodeToRelayUnit();
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                SerialCommunicationDataReceived response = send(codeToRelayUnit.requestHandshake, codeToHandlebarUnit.successHandshake);
                // Check response, if comm falure or invalidg hanshake code response retry communication
                if (!response.success || (response.success && response.code != codeToHandlebarUnit.successHandshake))
                {
                    // Handshake failed, if comm success but invalid response code, show status text message
                    if (response.code != codeToHandlebarUnit.successHandshake) {
                        controlDisplay.statusTextShow("INVALID HANDSHAKE");
                    }
                    // Initiate retry by setting bike status to comm failure
                    bikeStatus.communicationOK = false;
                    delay(3000);
                    display.clearDisplay();
                    Image image = Image();
                    image.retry();
                    delay(2000);
                }
                else {
                    // Handshake OK
                    bikeStatus.communicationOK = true;
                    bikeStatus.communicationLastPing = millis();
                    // Show timestamp if in debug mode
                    // TODO
                    if (bikeStatus.debugMode || true) {
                        unsigned long allSeconds=millis()/1000;
                        int runHours= allSeconds/3600;
                        int secsRemaining=allSeconds%3600;
                        int runMinutes=secsRemaining/60;
                        int runSeconds=secsRemaining%60;
                        display.setCursor(0,0);
                        display.fillRect(0, 0, DISPLAY_SCREEN_WIDTH, DISPLAY_TEXT_CHAR_HEIGHT -1, SSD1306_BLACK);
                        display.setCursor(0,0);
                        display.println(runHours);
                        display.setCursor(16,0);
                        display.println(runMinutes);
                        display.setCursor(32,0);
                        display.println(runSeconds);
                    }
                    // Show status text for a short time
                    controlDisplay.statusTextShow("HANDSHAKE SUCCESS");
                    bikeStatus.displayStatusTextRemoveTimeStamp = (millis() + DISPLAY_STATUSTEXT_OFF_WAIT_TIME);
                }
            }
        }

};