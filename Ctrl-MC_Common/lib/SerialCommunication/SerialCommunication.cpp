/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <SerialCommunication.h>

// Calculate CRC based on code and value
uint8_t SerialCommunication::calcCRC(uint8_t code, uint8_t value) {
    uint8_t crc = code+value;
    return crc > 255 ? crc - 255 : crc;
}

// Clear serial bugger
void SerialCommunication::clearBuffer() {
    while (Serial.available() > 0) {
        Serial.read();
    }
}

// Send code, value and crc
void SerialCommunication::send(uint8_t code, uint8_t value) {
    // Send code as char, and include checksum to relay unit
    Serial.write(code);
    Serial.write(value);
    Serial.write(calcCRC(code, value)); 
}

// Send handshake request or response
void SerialCommunication::sendHandshake() {
    SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
    send(serialCode.Handshake, 0);
}

// Read serial data
SerialCommunication::Data SerialCommunication::read() {
    // Prepare model
    SerialCommunication::Data serialData = SerialCommunication::Data();
    // Check for data in serial buffer 
    if (Serial.available() == 0) {
        // no data found
        return serialData;
    }
    // Found data = code, read and look for value and CRC
    serialData.received = true;
    serialData.code = Serial.read();
    uint8_t dataItems = 0;
    uint8_t crc = 0;
    unsigned long timeoutTimestamp = millis() + 500;
    // Look for serial value and crc
    while (dataItems < 2 && millis() < timeoutTimestamp)
    {
        if (Serial.available() > 0) {
            if (dataItems == 0)
                serialData.value = Serial.read();
            else // dataItems == 1
                crc = Serial.read();
            dataItems++;
        }
    }
    
    // Prepare check read data
    SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
    SerialCommunication::SerialValueError serialValueError = SerialCommunication::SerialValueError();    

    // Check if compete data found, should be 2 dataitems = value + crc
    if (dataItems < 1) {
        serialData.code = serialCode.Error;
        serialData.value = serialValueError.IncompleteData;
        return serialData;
    }
    
    // Check if crc is correct
    uint8_t crcExpected = calcCRC(serialData.code, serialData.value);
    if (crcExpected != crc) {
        serialData.code = serialCode.Error;
        serialData.value = serialValueError.InvalidCRC;
        return serialData;
    }

    // Check if received error
    if (serialData.code == serialCode.Error) {
        // Modify system error codes
        if (serialData.value == serialValueError.IncompleteData)
            serialData.value = serialValueError.ReceivedErrorIncompleteData;
        else if (serialData.value == serialValueError.InvalidCRC)
            serialData.value = serialValueError.ReceivedErrorInvalidCRC;
    }

    // All done, return received serial data    
    return serialData;

}

        