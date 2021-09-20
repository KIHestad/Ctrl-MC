/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

class SerialCommunication {
    
    private:

        void sendError(int errorCode) {
            Serial.write(errorCode); 
            // TODO: TEMP
            OnBoardLed onBoardLed = OnBoardLed();
            onBoardLed.blink(5);
        }

        void sendSuccess(int successCode) {
            Serial.write(successCode); 
            // TODO: TEMP
            OnBoardLed onBoardLed = OnBoardLed();
            onBoardLed.blinkSlow(1);
        }

    public:

        SerialCommunicationData read() {
            // Prepare model
            CodeToHandlebarUnit returnCodeToSend = CodeToHandlebarUnit();
            SerialCommunicationData data = SerialCommunicationData();
            data.retrieved = false;
            // Check for serial data retrieved
            if (Serial.available() > 0) {
            int value = -1;
            int checksum = -1;
                // Found data in buffer
                value = Serial.read();
                // Validate data, allow only value 0-126 as command
                if (value > 127) {
                    // Invalid value or data/checksum bytes out of sync
                    sendError(returnCodeToSend.errorInvalidDataValue); // Error code 0: invalid data or retrived checksum as data byte
                    return data;
                }
                // Found valid data, look for checksum - timeout if not received to avoid hang
                bool readChecksum = false;
                int timeout = 200; // milliseconds
                long readStartTimestamp = millis();
                long timeNowTimestamp = readStartTimestamp;
                while (!readChecksum && (timeNowTimestamp > readStartTimestamp + timeout)) {
                    if (Serial.available() > 0) {
                        checksum = Serial.read();
                        readChecksum = true;
                    }
                    timeNowTimestamp = millis();
                }
                // Validate checksum
                if (value < 128) {
                    // Invalid checksum or data/checksum bytes out of sync
                    sendError(returnCodeToSend.errorInvalidChecksumValue); // Error code 1: invalid checksum or retrived data as checksum byte
                    return data;
                }
                // Validate data against checksum
                if (value != (checksum - 128)) {
                    // Invalid data according to checksum
                    sendError(returnCodeToSend.errorInvalidChecksumValue); // Error code 2: checksum does not match data
                    return data;
                }
                // Validation OK, return data
                data.codeGroup = value / 10;
                data.code = value;
                data.retrieved = true;
                sendSuccess(returnCodeToSend.successSerialRead);
            }
            return data;
        }

};