/*
 
  Ctrl-MC // An open source Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 
*/

class SerialCommunication {
    
    private:

        void sendError(int errorCode) {
            Serial.write(errorCode); 
            controlDisplay.prepareForStatusText(20);
            display.println("SERIAL ERROR: " + errorCode);
            display.display();
        }

        void sendSuccess(int successCode) {
            Serial.write(successCode); 
            display.println(F("SERIAL SUCCESS"));
            display.display();
        }

    public:

        

};