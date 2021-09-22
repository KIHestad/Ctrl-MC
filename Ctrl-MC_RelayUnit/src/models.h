/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

// Enums
enum RelayStatus { relayOn, relayOff, relayInactive };

// Model used to retrive serial communication data
class SerialCommunicationDataReceived {
    public:
        bool received;
        bool success;
        uint8_t codeGroup;
        uint8_t code;
};
