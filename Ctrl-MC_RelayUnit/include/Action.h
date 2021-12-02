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
                serialCommunication.sendHandshake();
            }
            else if (serialData.code == serialCode.Error) {
                // Error occured, send error code and value back
                serialCommunication.send(serialData.code, serialData.value);
            }
            else if (serialData.code == serialCode.sysTempRequest) {
                // Return temperature
                float temp = dhtSensor.readTemperature() + 55; // add 55 to make negative temperature as positive value
                if (temp < 0) temp = 0; // avoid lower temp reading than -55 degrees
                uint8_t tempInt = (uint8_t)temp; // convert to integer
                temp = temp - tempInt; // remove int part, dec remaining
                uint8_t tempDec = (uint8_t)(temp * 10); // grab one decimal
                serialCommunication.send(serialCode.sysTempValueInt, tempInt);
                serialCommunication.send(serialCode.sysTempValueDec, tempDec);
            }
            else if (serialData.code == serialCode.sysHumidityRequest) {
                // Return humidity
                float hum = dhtSensor.readHumidity();
                if (hum < 0) hum = 0; // avoid lower temp reading than 0
                uint8_t humInt = (uint8_t)hum; // convert to integer
                hum = hum - humInt; // remove int part, dec remaining
                uint8_t humDec = (uint8_t)(hum * 10); // grab one decimal
                serialCommunication.send(serialCode.sysHumidityInt, humInt);
                serialCommunication.send(serialCode.sysHumidityDec, humDec);
            }
            else {
                // Unhandled request
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