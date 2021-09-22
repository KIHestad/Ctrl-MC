/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class SerialCommunication {
    
    public:

        void send(uint8_t code) {
            // Send code as char, and include checksum to relay unit
            Serial.write(code);
            Serial.write(255-code);
        }

        SerialCommunicationDataReceived read() {
            // Prepare model
            SerialCommunicationDataReceived dataReceived = SerialCommunicationDataReceived();
            dataReceived.success = false;
            dataReceived.received = false;
            // Check for data in serial buffer 
            if (Serial.available() == 0) {
                // no data found
                return dataReceived;
            }
            // Found data, read and look for CRC
            dataReceived.received = true;
            uint8_t code = Serial.read();
            // Wait for CRC or timeout
            uint8_t crc;
            bool crcRetrived = false;
            int timeout = 200; // milliseconds
            unsigned long readCRCStartTimestamp = millis();
            long timeNowTimestamp = readCRCStartTimestamp;
            while (!crcRetrived && (timeNowTimestamp < readCRCStartTimestamp + timeout))
            {
                if (Serial.available() > 0) {
                    crc = Serial.read();
                    crcRetrived = true;
                }
                timeNowTimestamp = millis();
            }
            // Check if crc missing or bad
            CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
            if (!crcRetrived || code != 255-crc) {
                // missing crc or bad crc
                
                send(codeToHandlebarUnit.errorChecksumValidationFailed);
                return dataReceived;
            }
            // Check for handshake
            CodeToRelayUnit codeToRelayUnit = CodeToRelayUnit();
            if (code == codeToRelayUnit.requestHandshake) {
                send(codeToHandlebarUnit.successHandshake);
                // code is processed, terminate other actions
                return dataReceived;
            }
            // All fine
            dataReceived.success = true;
            dataReceived.code = code;
            dataReceived.codeGroup = code / 10;
            return dataReceived;
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            // Check for serial data sent from handlebar unit
            if (Serial.available() >= 2) {
                dataReceived.received = true;
                uint8_t code = Serial.read();
                uint8_t crc = Serial.read();
                // Validate data
                if (code != 255-crc) {
                    CodeToHandlebarUnit response = CodeToHandlebarUnit();
                    send(response.errorChecksumValidationFailed); 
                    return dataReceived;
                }
                // Validation OK, return data
                dataReceived.success = true;
                dataReceived.codeGroup = code / 10;
                dataReceived.code = code;
            }
            return dataReceived;
        }


};