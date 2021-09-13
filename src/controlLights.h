/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

class ControlLights {

  /*
   *    Controls Hi/Lo light switch, and activates flashing / passing warning lights
   *    Main lights on/off are controlled by menu item on display controlled by controlDisplay / controlComuputer
   */ 

    private:
        Config config = Config();
        ButtonActon buttonAction = ButtonActon();
        bool waitForRelease = false; // flag indicating that indicator switch has been pressed
        bool highbeamFlash = false; // flag indicating to flash with high beam

    public:
        BikeStatus action(BikeStatus bikeStatus) {
            // Check for high beam / low beam toggle
            ButtonStatusRead buttonHiLo = buttonAction.readAnalog(config.inHandlebarButtonArray, config.handlebarButtonSignal_Lights_HiLo);
            if (waitForRelease) {
                if (!buttonHiLo.pressed) {
                    // Released
                    waitForRelease = false;
                }
                else {
                    // Pushed
                    if (bikeStatus.lights == lightsOff || bikeStatus.lights == parkLights) {
                        // main lights are not turned on, send high beam flash signal
                        Serial.println("HIGH BEAM FLASH");
                        highbeamFlash = true;
                    }
                    else if (bikeStatus.lights == lowBeam || bikeStatus.lights == highBeam) {
                        // main lights are on, toggle high/low
                        if (bikeStatus.lights == lowBeam) {

                        }
                    }
                    
                }
            }
            return bikeStatus;
        };
};