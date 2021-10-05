/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#ifndef serialCommunicationDef
    #define serialCommunicationDef
    #if (ARDUINO >= 100)
        #include "Arduino.h"
    #endif

    class SerialCommunication {
        public:
            
            // Class for response data returned by read method
            struct Response {
                    bool received = false; // set true if data was received
                    bool success = false; // set true if complete data set found, and crc validation success
                    bool relayAction = false; // set true if code = 0-15
                    uint8_t code;
                    uint8_t value;
            };

            // Class for codes
            struct SerialCode {
                    // 0-15 reserved for triggering relay on/off
                    // System codes
                    const uint8_t Handshake = 250;
                    const uint8_t Error = 255;
            };

            // Class for handshake response values - auto send triggered from read when Serial Code: "HandshakeRequest" is received
            struct SerialValueError {
                    const uint8_t GeneralError = 251;
                    const uint8_t IncompleteData = 252;
                    const uint8_t InvalidCRC = 253;
                    const uint8_t UnknownCode = 255;
            };

            // Clear the serial buffer
            void clearBuffer();
            // Send handshake request
            void sendHandshake();
            // Main methods for send and read serial data
            void send(uint8_t code, uint8_t value);
            Response read();

        private:
            
            // Calculate CRC / checksum based of code and value
            uint8_t calcCRC(uint8_t code, uint8_t value);

    };

#endif