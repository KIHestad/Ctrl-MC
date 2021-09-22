class RelayIgnition {

    public:
        void action(SerialCommunicationDataReceived data) {
            
            // TODO: just turn on / off onboard display to indicate ignition on
            OnBoardLed onBoardLed = OnBoardLed();
            CodeToHandlebarUnit responseCode = CodeToHandlebarUnit();
            CodeToRelayUnit receivedCode = CodeToRelayUnit();
            if (data.code == receivedCode.ignitionTurnOff)
                onBoardLed.off();
            else if (data.code == receivedCode.ignitionTurnOn)
                onBoardLed.on();
            // Send confirmation
            SerialCommunication serialCom = SerialCommunication();
            serialCom.send(responseCode.successGeneric);

            //if (data.code == )
            // RelayStatus currentIgnitionStatus = relay.getStatus(OUTPUT_PIN_MAIN_IGNITION);
            // if (currentIgnitionStatus != relayInactive)
            // {
            //     RelayStatus newIgnitionStatus;
            //     if (data.code == codeReceived.ignitionTurnOn)
            //         newIgnitionStatus = relayOn;
            //     else if (data.code == codeReceived.ignitionTurnOff)
            //         newIgnitionStatus = relayOff;
            //     if (currentIgnitionStatus != newIgnitionStatus)
            //         relay.set(OUTPUT_PIN_MAIN_IGNITION, newIgnitionStatus);
            // }
        }

};