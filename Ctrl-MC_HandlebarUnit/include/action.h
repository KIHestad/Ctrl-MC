class Action {
    
    public:

        void checkReceivedData(SerialCommunicationDataReceived dataReceived) {
            

        }

        void indicatorBlink() {
            if (bikeStatus.indicator != indOff && millis() > bikeStatus.indicatorNextBlinkTimestamp) {
                bikeStatus.indicatorBlinkOn = !bikeStatus.indicatorBlinkOn;
                uint8_t blinkValue = bikeStatus.indicatorBlinkOn ? 1 : 0;
                if (bikeStatus.indicator == indLeft || bikeStatus.indicator == indHazard)
                    serialCommunication.send(RELAY_IND_LEFT, blinkValue);
                if (bikeStatus.indicator == indRight || bikeStatus.indicator == indHazard)
                    serialCommunication.send(RELAY_IND_RIGHT, blinkValue);
                bikeStatus.indicatorNextBlinkTimestamp = millis() + IND_BLINK_SPEED;
                controlDisplay.refreshStatusPage();                
            }
        }



};