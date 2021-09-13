/*
 *   "Ardu MC Controller" is a Open Source Arduino project made by KI Hestad: https://youtube.com/kihestad
 */

class Config {

  /*
   *    Adjust parameters in this file to customize  the Ardu MS Controller
   */ 

  public:

    // Arduino pin settings
    // The digital pins 0 and 1 are not safe to use with relay, first pin that should be mapped as output pin to relay is pin2
    // Normally the analog pins A0-A8 can be used as digital pins, A0 is then numbered as the last digital pin +1
    // Set -1 for input or outputs that are not in use
    
    // Digital output pins for 2 port realy module
    int outMainIgnintionPositive = -1; // Activates main power, normally to main fuse
    int outMainIgningtonNegative = -1; // Cuts ground to EDI / Coils to enable engine to run (stop switch)
    // Digital output pins for 8 port realy module
    int outStartMotor = -1;
    int outHorn = 2;
    int outIndicatorLeft = 3;
    int outIndicatorRight = 4;
    int outLightsPark = -1;
    int outLightsLow = -1;
    int outLightsHigh = -1;
    int outLightsBrake = -1;
    // Onboard led pin
    int onBoardLed = 13;
    
    // Because of limited numbers on pins on most Arduino boards, the handlebar controls are connected in series controlled by one analog pin 
    // A 2K resistor is put in between of each button, reading the analog signal from the pushed buttons return different signals
    int inHandlebarButtonArray = 14; // same as pin A0
    // The return signal indentifies what button is pushed, the signa can vary so this is min - max return value
    // The varables below indicate what function is to be triggered, same return values can be used on multiple funtions
    // Same return values  inputs can be mapped to same pin, typically for multifuctional buttons where short press and long press trigges differen functions
    int handlebarButtonSignal_Horn[2] = { 200, 400};
    int handlebarButtonSignal_Lights_Main[2] = { -1, -1};
    int handlebarButtonSignal_Lights_HiLo[2] = { 200, 400};
    int handlebarButtonSignal_Indicator_Left[2] = { 200, 400};
    int handlebarButtonSignal_Indicator_Right[2] = { 200, 400};
    int handlebarButtonSignal_StartStop_Engine[2] = { 200, 400};
    int handlebarButtonSignal_Display_NextMenu[2] = { 200, 400};
    int handlebarButtonSignal_Display_SelectOption[2] = { 200, 400};

    // Levers / Pedals / Sensors
    int inClutch = -1;
    int inBreakLeverAndPedal = -1;
    int inOilSensor = -1;
    int inNeutralSensor = -1;
        
    // Lights settings
    bool lightsCombineHiWithLo = true; // Keep on low beam when high beam is triggered, set false to turn off low beam and only send power to high beam light bulb
    int lightsHiFlashCount = 3; // Number of flashes for the headlight high beam when flashing is triggered from button used as "passing switch"

    // Horn settings
    int hornLongPressDelay = 500; // Number of milliseconds (1000 = 1 second) for delay from pressing horn button to horn activates

    // Indicators (turn signals) settings
    int indicatorsBlinkIntervalSpeed = 750; // Number of milliseconds (1000 = 1 second) for the blinking speed on turn signals. 500 = fast, 750 = normal, 1000 = slow.
    int indicatorsAutoShutOff = 30; // Number of seconds before turn signals automatically are turned off. Set to 0 to disable it.
    int hazardActivateLongPressDelay = 1500; // Number of milliseconds (1000 = 1 second) for activating hazard when both L & R turn signal buttons are pressed, -1 to disable

};