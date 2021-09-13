/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

class ControlIgnition {

    /*
    *    Detect if ignition switch is turned on and enables the controller
    *    Also controls engine start and stop
    */

    private:
        PinSetup pin = PinSetup();
        ButtonActon buttonAction = ButtonActon();
        OnBoardLed onBoardLed = OnBoardLed();
        long longPressTimestamp = 0;
    
    public:
        BikeStatus action(BikeStatus bikeStatus) {
            
            // TODO
            return bikeStatus;
        };
};