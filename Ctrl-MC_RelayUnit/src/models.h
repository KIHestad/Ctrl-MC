/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

// Enums
enum RelayStatus { relayOn, relayOff, relayInactive };

// Used tp retrive serial communication data
class SerialCommunicationData {
    public:
        bool retrieved;
        int codeGroup;
        int code;
};