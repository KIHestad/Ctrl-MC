/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// Code must be 8 bit int from 0-255 to be able to send it using serial communication as a char
// Code group is just code divided on 10 to conveniant create a group of codes with the actual code to identify action
// When sending a code over seraial connection it is always sent with an additional "crc"-code for verification, the crc-code is just the code "reversed" (255-code) to create a checksum to compare against code

class CodeGroupToRelayUnit {
    
    public:
        
        const uint8_t ignition = 0;
        const uint8_t startMotor = 1;
        const uint8_t indicators = 2;
        const uint8_t system = 25;
};

class CodeToRelayUnit {
    
    public:
        
        const uint8_t ignitionTurnOff = 0;
        const uint8_t ignitionTurnOn = 1;

        const uint8_t startMotorDisengage = 10;
        const uint8_t startMotorEngage = 11;

        const uint8_t indicatorsOff = 20;
        const uint8_t indicatorLeftOn = 21;
        const uint8_t indicatorRightOn = 22;
        const uint8_t indicatorHazardOn = 23;

        const uint8_t requestHandshake = 250;
};

class CodeToHandlebarUnit {
    public: 
        
        
        
        // General/System success response
        const uint8_t successHandshake = 250;
        const uint8_t successGeneric = 251;

        // Errors response
        const uint8_t errorMissingData = 253;
        const uint8_t errorUnknownCode = 254;
        const uint8_t errorChecksumValidationFailed = 255;
};