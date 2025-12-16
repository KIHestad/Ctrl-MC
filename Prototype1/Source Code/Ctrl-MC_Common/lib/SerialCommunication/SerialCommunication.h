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
                // 0-39 reserved for triggering relay on/off
                // Request and return codes for temperature and humidity
                static const uint8_t sysTempRequest = 40;
                static const uint8_t sysTempValueInt = 41; // send temperature integer value+55 (range = -55 to +200 degrees)
                static const uint8_t sysTempValueDec = 42; // send temperature decimal value
                static const uint8_t sysHumidityRequest = 43;
                static const uint8_t sysHumidityInt = 44; // send humidity integer value
                static const uint8_t sysHumidityDec = 45; // send humidity decimal value
                // Request and return codes for battery voltage
                static const uint8_t batteryVoltageRequest = 50;
                static const uint8_t batteryVoltageValue = 51; // Voltage in 10X to include one decimal
                // System codes
                static const uint8_t Handshake = 250;
                static const uint8_t Error = 255;
            };

            // Class for error codes sent as value
            struct SerialValueError {
                static const uint8_t GeneralError = 100;
                static const uint8_t IncompleteData = 200;
                static const uint8_t InvalidCRC = 201;
                static const uint8_t ReceivedErrorIncompleteData = 210;
                static const uint8_t ReceivedErrorInvalidCRC = 211;
                static const uint8_t UnknownCode = 255;
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