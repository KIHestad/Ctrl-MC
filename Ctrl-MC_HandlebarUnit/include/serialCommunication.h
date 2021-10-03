/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class SerialCommunication {
    
    private:

        uint8_t calcCRC(uint8_t code, uint8_t value) {
            uint8_t crc = code+value;
            return crc > 255 ? crc - 255 : crc;
        }
        
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

        void send(uint8_t code, uint8_t value) {
            // Send code as char, and include checksum to relay unit
            Serial.write(code);
            Serial.write(value);
            Serial.write(calcCRC(code, value)); 
        }
        
        void clearBuffer() {
            while (Serial.available() > 0) {
                Serial.read();
            }
        }

        SerialCommunicationDataReceived read() {
            // Prepare model
            SerialCommunicationDataReceived dataReceived = SerialCommunicationDataReceived();
            dataReceived.success = false;
            // Check for data in serial buffer 
            if (Serial.available() == 0) {
                // no data found
                return dataReceived;
            }
            // Found data = code, read and look for value and CRC
            uint8_t code = Serial.read();
            uint8_t dataItems = 0;
            uint8_t data[2];
            unsigned long readUntilTimestamp = millis() + 500;
            while (dataItems < 2 && millis() < readUntilTimestamp)
            {
                if (Serial.available() > 0) {
                    data[dataItems] = Serial.read();
                    dataItems++;
                }
            }
            // Check if compete data found, should be 2 dataitems = value + crc
            if (dataItems < 1) {
                displayError("INCOMPLETE DATA");
                return dataReceived;
            }
            // Check if crc is correct
            CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
            uint8_t crcExpected = calcCRC(code, data[0]);
            if (crcExpected != data[1]) {
                displayError("INVALID READ (CRC)"); 
                return dataReceived;
            }
            else if (code == codeToHandlebarUnit.errorMissingData) {
                displayError("INCOMPETE SEND"); 
                return dataReceived;
            }
            else if (code == codeToHandlebarUnit.errorChecksumValidationFailed) {
                displayError("INVALID SEND (CRC)"); 
                return dataReceived;
            }
            else if (code == codeToHandlebarUnit.errorUnknownCode) {
                displayError("UNKNOWN CODE SENT"); 
                return dataReceived;
            }
            else if (code == codeToHandlebarUnit.successHandshake) {
                if (!bikeStatus.communicationOK) {
                    Image image = Image();
                    image.retry();
                    controlDisplay.statusTextShow("COMM RESTORED");
                    delay(1000);
                    bikeStatus.displayMenyPageSelected = 0;
                    bikeStatus.displayMenySubPageSelected = 0;
                    controlDisplay.refreshStatusPage();
                }

                bikeStatus.communicationOK = true;
                bikeStatus.communicationLastPing = millis();
                return dataReceived;
            }
            // All fine
            dataReceived.success = true;
            dataReceived.code = code;
            dataReceived.value = data[0];
            return dataReceived;
        }

        void performHandshake() {
            // Expect handshake response in regular intervals
            unsigned long timestampNow = millis();
            unsigned long handshakeDelayAccepted = 3000; // Number of millliseconds after last confirmed handshake to accept before trigger alert
            if (timestampNow > bikeStatus.communicationLastPing + (SYSTEM_HANDSHAKE_CHECK_INTERVAL * 1000) + handshakeDelayAccepted) {
                bikeStatus.communicationOK = false;
                Image image = Image();
                image.warning();
                controlDisplay.statusTextShow("HANDSHAKE FAILED");
                delay(2000);
            }
            // In frequent intervals trigger handshake request
            if (!bikeStatus.communicationOK || timestampNow > bikeStatus.communicationLastPing + (SYSTEM_HANDSHAKE_CHECK_INTERVAL * 1000)) {
                // Send handshake request to relay module
                CodeToRelayUnit codeToRelayUnit = CodeToRelayUnit();
                send(codeToRelayUnit.requestHandshake, 0);
                // If communication problem, show reconnect icon
                if (!bikeStatus.communicationOK) {
                    Image image = Image();
                    image.retry();
                    controlDisplay.statusTextShow("RECONNECTING");
                    delay(1000);
                }
            }
        }

};