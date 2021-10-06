class Action {

    public:
    
        // Main method for performing proper action based on serial request from handlebar unit
        void checkReceivedData(SerialCommunication::Data serialData) {
            // Check received data and trigger action
            SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
            if (serialData.code < 16) 
                // Code 0-15, trigger on/off relay based on value
                relayAction(serialData);
            else if (serialData.code == serialCode.Handshake) {
                // Handshake received, return handshake back
                SerialCommunication serialCommunication = SerialCommunication();
                serialCommunication.sendHandshake();
            }
            else if (serialData.code == serialCode.Error) {
                // Error occured, send error code and value back
                SerialCommunication serialCommunication = SerialCommunication();
                serialCommunication.send(serialData.code, serialData.value);
            }
            else {
                // Unhandled request
                SerialCommunication serialCommunication = SerialCommunication();
                SerialCommunication::SerialValueError serialValueError = SerialCommunication::SerialValueError();
                serialCommunication.send(serialCode.Error, serialValueError.UnknownCode);    
            }
        }

        void relayAction(SerialCommunication::Data serialData) {
            Relay relay = Relay();
            Relay::RelayStatus relayStatus = (serialData.value == 1) ? Relay::RelayStatus::relayOn : Relay::RelayStatus::relayOff;
            relay.set(serialData.code, relayStatus);
            return;
    }

};