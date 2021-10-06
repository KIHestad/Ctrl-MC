/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#ifndef serialCommunicationDef
    #define serialCommunicationDef
    #if (ARDUINO >= 100)
        #include "Arduino.h"
    #endif

    class SerialCommunication {
        public:
            
            // Class for data sent as over serial port
            struct Data {
                    bool received = false; // set true if data was received
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

            // Class for error codes sent as value
            struct SerialValueError {
                    const uint8_t GeneralError = 100;
                    const uint8_t IncompleteData = 200;
                    const uint8_t InvalidCRC = 201;
                    const uint8_t ReceivedErrorIncompleteData = 210;
                    const uint8_t ReceivedErrorInvalidCRC = 211;
                    const uint8_t UnknownCode = 255;
            };

            // Clear the serial buffer
            void clearBuffer();
            // Send handshake request
            void sendHandshake();
            // Main methods for send and read serial data
            void send(uint8_t code, uint8_t value);
            Data read();

        private:
            
            // Calculate CRC / checksum based of code and value
            uint8_t calcCRC(uint8_t code, uint8_t value);

    };

#endif