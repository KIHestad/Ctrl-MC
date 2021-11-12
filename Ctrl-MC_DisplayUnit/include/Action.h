class Action {
    
    private:
        
        // Reveived handshake
        void receivedHandshake() {
            // If previously triggered alarm for communication falure, update display now
            if (!bikeStatus.handshakeOK) {
                Image image = Image();
                image.retry();
                controlDisplay.statusTextShow("COMM RESTORED");
                delay(1000);
                bikeStatus.displayMenyPageSelected = 0;
                bikeStatus.displayMenySubPageSelected = 0;
                controlDisplay.refreshStatusPage();
            }
            // Prepare next handshake
            bikeStatus.handshakeNextTimestamp = millis() + (SYSTEM_HANDSHAKE_CHECK_INTERVAL * 1000);
            bikeStatus.handshakeOK = true;
        }

        void displayError(SerialCommunication::Data serialData) {
            display.clearDisplay();
            Image image = Image();
            image.warning();
            SerialCommunication::SerialValueError errorValue = SerialCommunication::SerialValueError();
            if (serialData.value == errorValue.GeneralError)
                controlDisplay.statusTextShow("GENERAL ERROR");
            else if (serialData.value == errorValue.IncompleteData)
                controlDisplay.statusTextShow("ERR DATA RECEIVED");
            else if (serialData.value == errorValue.InvalidCRC)
                controlDisplay.statusTextShow("ERR CRC RECEIVED");
            else if (serialData.value == errorValue.ReceivedErrorIncompleteData)
                controlDisplay.statusTextShow("ERR DATA SENT");
            else if (serialData.value == errorValue.ReceivedErrorInvalidCRC)
                controlDisplay.statusTextShow("ERR CRC SENT");
            else if (serialData.value == errorValue.UnknownCode) {
                String errMsg = "ERR CODE SENT: ";
                errMsg += serialData.value;
                controlDisplay.statusTextShow(errMsg);
            }
        }

        void displayUnknownCode(SerialCommunication::Data serialData) {
            display.clearDisplay();
            Image image = Image();
            image.warning();
            String errMsg = "ERR CODE RECEIVED: ";
            errMsg += serialData.code;
            controlDisplay.statusTextShow(errMsg);
        }
    
    public:

        void checkReceivedData(SerialCommunication::Data serialData) {
            // Check received serial data and trigger action
            SerialCommunication::SerialCode serialCode = SerialCommunication::SerialCode();
            if (serialData.code == serialCode.Handshake) 
                receivedHandshake();
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
                bikeStatus.indicatorNextBlinkTimestamp = millis() + IND_BLINK_SPEED;
                controlDisplay.refreshStatusPage();                
            }
        }

        // Trigger handshake
        void performHandshake() {
            // Expect handshake response in regular intervals, if not show alert
            unsigned long timestampNow = millis();
            unsigned long handshakeDelayAccepted = 3000; // Number of millliseconds after last confirmed handshake to accept before trigger alert
            if (timestampNow > bikeStatus.handshakeNextTimestamp + handshakeDelayAccepted) {
                bikeStatus.handshakeOK = false;
                Image image = Image();
                image.warning();
                controlDisplay.statusTextShow("HANDSHAKE FAILED");
                delay(2000);
            }
            // In frequent intervals trigger handshake request
            if (!bikeStatus.handshakeOK || timestampNow > bikeStatus.handshakeNextTimestamp) {
                // Send handshake request to relay module
                SerialCommunication serialCommunication = SerialCommunication();
                serialCommunication.sendHandshake();
                // If communication problem, show reconnect icon
                if (!bikeStatus.handshakeOK) {
                    Image image = Image();
                    image.retry();
                    controlDisplay.statusTextShow("RECONNECTING");
                    delay(1000);
                }
            }
        }



};