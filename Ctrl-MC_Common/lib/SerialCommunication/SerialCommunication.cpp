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
SerialCommunication::Response SerialCommunication::read() {
    // Prepare model
    SerialCommunication::Response response = SerialCommunication::Response();
    // Check for data in serial buffer 
    if (Serial.available() == 0) {
        // no data found
        return response;
    }
    // Found data = code, read and look for value and CRC
    response.received = true;
    response.code = Serial.read();
    uint8_t dataItems = 0;
    uint8_t crc;
    unsigned long timeoutTimestamp = millis() + 500;
    // Look for serial value and crc
    while (dataItems < 2 && millis() < timeoutTimestamp)
    {
        if (Serial.available() > 0) {
            if (dataItems == 0)
                response.value = Serial.read();
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
        response.code = serialCode.Error;
        response.value = serialValueError.IncompleteData;
        return response;
    }
    
    // Check if crc is correct
    uint8_t crcExpected = calcCRC(response.code, response.value);
    if (crcExpected != crc) {
        response.code = serialCode.Error;
        response.value = serialValueError.InvalidCRC;
        return response;
    }
    
    // Check for handshake
    if (response.code == serialCode.Handshake && response.value == 0) {
        response.success = true;
        return response;
    }

    // Check for relay action
    if (response.code < 16 && (response.value == 0 || response.value == 1)) {
        response.success = true;
        response.relayAction = true;
        return response;
    }

    // Unknown code is receviced
    response.code = serialCode.Error;
    response.value = serialValueError.UnknownCode;
    return response;

}

        