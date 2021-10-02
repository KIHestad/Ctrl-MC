class Action {

    public:
    
        void checkReceivedData(SerialCommunicationDataReceived dataReceived) {
            // If code received < 16, then code is relay action (relay 0 - 15)
            // value 0 = off, value 1 = on
            SerialCommunication serialCommunication = SerialCommunication();
            if (dataReceived.code < 16) {
                // Relay action detected
                Relay relay = Relay();
                RelayStatus relayStatus = (dataReceived.value == 1) ? relayOn : relayOff;
                relay.set(dataReceived.code, relayStatus);
                // Send confirmation
                CodeToHandlebarUnit codeToHandlebarUnit = CodeToHandlebarUnit();
                serialCommunication.send(codeToHandlebarUnit.successGeneric,0);
                return;
            }
            // Unknown code
            CodeToHandlebarUnit responseCode = CodeToHandlebarUnit();
            serialCommunication.send(responseCode.errorUnknownCode, 0);
        }

};