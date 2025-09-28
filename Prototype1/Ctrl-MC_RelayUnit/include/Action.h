class Action {

    public:
    
        // Main method for performing proper action based on serial request from handlebar unit
        void checkReceivedData(SerialCommunication::Data serialData) {
            // Check received data and trigger action
            SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
            if (serialData.code < 40) 
                // Code 0-39, trigger on/off relay based on value
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
            else if (serialData.code == serialCode.batteryVoltageRequest) {
                // Return battery voltage according to voltage factor
                double readValue = analogRead(Config::RelayUnitInput::batteryVoltage);
                // Factor used to convert analog real signal to real
                double adcVoltageFactor = Config::BatteryVoltage::adcFactor / (Config::BatteryVoltage::resistor2 / (Config::BatteryVoltage::resistor1+Config::BatteryVoltage::resistor2)); 
                double batteryVoltage = readValue * adcVoltageFactor;
                // Correct reading according to samples converted to expotensial curve, multiply with 10
                double correctedBatteryVoltage = 19.12387 / ( 6.70041 * exp(-0.19703 * batteryVoltage ) +1);
                // Send data * 10 to include one decimal, to be divided by 10 on display unit
                uint8_t serialDataValue = (uint8_t)round(correctedBatteryVoltage * 10);
                // Return result
                serialCommunication.send(serialCode.batteryVoltageValue, correctedBatteryVoltage);
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