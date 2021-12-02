class Action {
    
    private:
        
        // Reveived handshake
        void receivedHandshake() {
            // If previously triggered alarm for communication falure, update display now
            if (!bikeStatus.handshakeOK) {
                DisplayImage displayImage = DisplayImage();
                displayImage.retry();
                displayHelper.statusTextShow("COMM RESTORED");
                delay(1000);
                bikeStatus.displayMenuPageSelected = 0;
                bikeStatus.displayMenuSubPageSelected = 0;
                displayHelper.refreshStatusPage();
            }
            // Prepare next handshake
            Config config = Config();
            bikeStatus.handshakeNextTimestamp = millis() + config.handshakeInterval;
            bikeStatus.handshakeOK = true;
        }

        void displayError(SerialCommunication::Data serialData) {
            display.clearDisplay();
            DisplayImage displayImage = DisplayImage();
            displayImage.warning();
            SerialCommunication::SerialValueError errorValue = SerialCommunication::SerialValueError();
            if (serialData.value == errorValue.GeneralError)
                displayHelper.statusTextShow("GENERAL ERROR");
            else if (serialData.value == errorValue.IncompleteData)
                displayHelper.statusTextShow("ERR DATA RECEIVED");
            else if (serialData.value == errorValue.InvalidCRC)
                displayHelper.statusTextShow("ERR CRC RECEIVED");
            else if (serialData.value == errorValue.ReceivedErrorIncompleteData)
                displayHelper.statusTextShow("ERR DATA SENT");
            else if (serialData.value == errorValue.ReceivedErrorInvalidCRC)
                displayHelper.statusTextShow("ERR CRC SENT");
            else if (serialData.value == errorValue.UnknownCode) {
                String errMsg = "ERR CODE SENT: ";
                errMsg += serialData.value;
                displayHelper.statusTextShow(errMsg);
            }
        }

        void displayUnknownCode(SerialCommunication::Data serialData) {
            display.clearDisplay();
            DisplayImage displayImage = DisplayImage();
            displayImage.warning();
            String errMsg = "ERR CODE RECEIVED: ";
            errMsg += serialData.code;
            displayHelper.statusTextShow(errMsg);
        }
    
    public:

        void checkReceivedData(SerialCommunication::Data serialData) {
            // Check received serial data and trigger action
            SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
            if (serialData.code == serialCode.Handshake) 
                receivedHandshake();
            else if (serialData.code == serialCode.sysTempValueInt)
                bikeStatus.sysTempInt = serialData.value - 55; // subtract 55 to convert to negative temp 
            else if (serialData.code == serialCode.sysTempValueDec)
                bikeStatus.sysTempDec = serialData.value;
            else if (serialData.code == serialCode.sysHumidityInt)
                bikeStatus.sysHumidityInt = serialData.value;
            else if (serialData.code == serialCode.sysHumidityDec)
                bikeStatus.sysHumidityDec = serialData.value;
            else if (serialData.code == serialCode.Error)
                displayError(serialData);
            else {
                displayUnknownCode(serialData);
            }
        }

        // If turn signals turned on, perform blink ;-)
        void indicatorBlink() {
            if (bikeStatus.indicator != indOff && millis() > bikeStatus.indicatorNextBlinkTimestamp) {
                bikeStatus.indicatorBlinkOn = !bikeStatus.indicatorBlinkOn;
                uint8_t blinkValue = bikeStatus.indicatorBlinkOn ? 1 : 0;
                SerialCommunication serialCommunication = SerialCommunication();
                Config::RelayUnitOutput output = Config::RelayUnitOutput();
                if (bikeStatus.indicator == indLeft || bikeStatus.indicator == indHazard)
                    serialCommunication.send(output.turnSignalLeft.pin, blinkValue);
                if (bikeStatus.indicator == indRight || bikeStatus.indicator == indHazard)
                    serialCommunication.send(output.turnSignalRight.pin, blinkValue);
                Config::Indicator ind = Config::Indicator();
                bikeStatus.indicatorNextBlinkTimestamp = millis() + ind.blinkSpeed;
                displayHelper.refreshStatusPage();                
            }
        }

        // Trigger handshake
        void performHandshake() {
            // Expect handshake response in regular intervals, if not show alert
            unsigned long timestampNow = millis();
            unsigned long handshakeDelayAccepted = 3000; // Number of millliseconds after last confirmed handshake to accept before trigger alert
            if (timestampNow > bikeStatus.handshakeNextTimestamp + handshakeDelayAccepted) {
                bikeStatus.handshakeOK = false;
                DisplayImage displayImage = DisplayImage();
                displayImage.warning();
                displayHelper.statusTextShow("HANDSHAKE FAILED");
                delay(2000);
            }
            // In frequent intervals trigger handshake request
            if (!bikeStatus.handshakeOK || timestampNow > bikeStatus.handshakeNextTimestamp) {
                // Send handshake request to relay module
                onBoardLed.on();
                SerialCommunication serialCommunication = SerialCommunication();
                serialCommunication.sendHandshake();
                onBoardLed.off();
                // If communication problem, show reconnect icon
                if (!bikeStatus.handshakeOK) {
                    DisplayImage displayImage = DisplayImage();
                    displayImage.retry();
                    displayHelper.statusTextShow("RECONNECTING");
                    delay(1000);
                }
            }
        }



};