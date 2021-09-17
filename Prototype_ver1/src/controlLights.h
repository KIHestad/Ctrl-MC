/*
 *   Ctrl-MC // An open source Arduino project made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

class ControlLights {

  /*
   *    Controls Hi/Lo light switch, and activates flashing / passing warning lights
   *    Main lights on/off are controlled by menu item on display controlled by controlDisplay / controlComuputer
   */ 

    private:
        Button button = Button();
        bool waitForRelease = false; // flag indicating that indicator switch has been pressed
        bool highbeamFlash = false; // flag indicating to flash with high beam

    public:
        BikeStatus action(BikeStatus bikeStatus) {
            // Check for high beam / low beam toggle
            ButtonStatus buttonHiLo = button.read(LIGHTS_LOW_HIGHT_SWITCH_INPUT);
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