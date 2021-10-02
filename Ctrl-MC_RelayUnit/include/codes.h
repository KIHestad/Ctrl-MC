/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// Code to relay unit must be a 8 bit int from 0-255 to be able to send it using serial communication as a char
// When sending a code over seraial connection it is always sent with an additional "crc"-code for verification, the crc-code is just the code "reversed" (255-code) to create a checksum to compare against code
// Turn on/off relays uses first 5 bit: 1-4bit = max 16 relays, 5bit = on/off
// Code > 200 is system codes for spesific tasks

class CodeToRelayUnit {
    
    public:
        // For ordinary relay action use 4 bit pin code + 1 bit on/off = total 5 bit = 0-31
        const uint8_t requestHandshake = 250;
};

class CodeToHandlebarUnit {
    public: 
        // For ordinary relay response use 4 bit pin code + 1 bit on/off = total 5 bit = 0-31
        
        
        // General/System success response
        const uint8_t successHandshake = 250;
        const uint8_t successGeneric = 251;

        // Errors response
        const uint8_t errorMissingData = 253;
        const uint8_t errorUnknownCode = 254;
        const uint8_t errorChecksumValidationFailed = 255;
};