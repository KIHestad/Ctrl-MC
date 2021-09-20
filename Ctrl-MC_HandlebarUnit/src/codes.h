/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

// Should be integers from 0-127 (128-255 = checksum codes)
// When retrieving a code, it is divided by 10 to get 0-12 to classify a code into a group

class CodeGroupToRelayUnit {
    
    public:
        
        const int ignition = 0;
        const int startMotor = 1;
        const int indicators = 2;
        const int system = 12;
};

class CodeToRelayUnit {
    
    public:
        
        const int ignitionTurnOff = 0;
        const int ignitionTurnOn = 1;

        const int startMotorDisengage = 10;
        const int startMotorEngage = 11;

        const int indicatorsOff = 20;
        const int indicatorLeftOn = 21;
        const int indicatorRightOn = 22;
        const int indicatorHazardOn = 23;

        const int passValue = 120;
        const int requestTemperature = 126;
        const int requestHandshake = 127;
};

class CodeToHandlebarUnit {
    public: 
        // Errors
        const int errorInvalidDataValue = 0;
        const int errorInvalidChecksumValue = 1;
        const int errorChecksumValidationFailed = 2;
        // Success
        const int successSerialRead = 255;
        const int successHandshake = 254;
};