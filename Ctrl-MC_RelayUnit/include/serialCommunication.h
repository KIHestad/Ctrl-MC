/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

class SerialCommunication {
    
    private:

        uint8_t calcCRC(uint8_t code, uint8_t value) {
            uint8_t crc = code+value;
            return crc > 255 ? crc - 255 : crc;
        }

    public:

        void send(uint8_t code, uint8_t value) {
            // Send code as char, and include checksum to relay unit
            Serial.write(code);
            Serial.write(value);
            Serial.write(calcCRC(code, value)); 
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
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                send(codeToHandlebarUnit.errorMissingData, 0);
                return dataReceived;
            }
            // Check if crc is correct
            uint8_t crcExpected = calcCRC(code, data[0]);
            if (crcExpected != data[1]) {
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                send(codeToHandlebarUnit.errorChecksumValidationFailed, 0);
                return dataReceived;
            }
            // Check for handshake, if found return success code to handlebar unit
            CodeToRelayUnit codeToRelayUnit = CodeToRelayUnit();
            if (code == codeToRelayUnit.requestHandshake) {
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                send(codeToHandlebarUnit.successHandshake, 0);
                return dataReceived;
            }
            // All fine, return result
            dataReceived.success = true;
            dataReceived.code = code;
            dataReceived.value = data[0];
            return dataReceived;
        }


};