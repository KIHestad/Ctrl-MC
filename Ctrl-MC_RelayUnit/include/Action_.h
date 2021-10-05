class Action {

    public:
    
        void checkReceivedData(SerialCommunication::Response response) {
            // Check recied response and trigger action
            SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
            if (response.success) {
                if (response.relayAction)
                    relayAction(response);
                else if (response.code == serialCode.Handshake) {
                    SerialCommunication serialCommunication = SerialCommunication();
                    serialCommunication.sendHandshake();
                }
                else {
                    SerialCommunication serialCommunication = SerialCommunication();
                    SerialCommunication::SerialValueError serialValueError = SerialCommunication::SerialValueError();
                    serialCommunication.send(serialCode.Error, serialValueError.UnknownCode);    
                }
            }
            else {
                SerialCommunication serialCommunication = SerialCommunication();
                serialCommunication.send(response.code, response.value);
            }
        }

        void relayAction(SerialCommunication::Response response) {
            Relay relay = Relay();
            Relay::RelayStatus relayStatus = (response.value == 1) ? Relay::RelayStatus::relayOn : Relay::RelayStatus::relayOff;
            relay.set(response.code, relayStatus);
            return;
    }

};