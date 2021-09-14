/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlIgnition {

    /*
    *    Detect if ignition switch is turned on and enables the controller
    *    Also controls engine start and stop
    */

    private:
        PinSetup pin = PinSetup();
        Button button = Button();
        OnBoardLed onBoardLed = OnBoardLed();
        long longPressTimestamp = 0;
    
    public:
        BikeStatus action(BikeStatus bikeStatus) {
            
            // TODO
            return bikeStatus;
        };
};