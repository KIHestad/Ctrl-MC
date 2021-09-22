/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

/*****************************************************************************
 *   Output Pins cofiguration settings   
 *****************************************************************************/

// Pin to arduino onboard led
const uint8_t ONBOARD_LED_PIN = 13;

// Pins to OLED Display using I2C interface, SCL and SDA pins
const uint8_t DISPLAY_SDA_OUTPUT_PIN = A4;
const uint8_t DISPLAY_SCL_OUTPUT_PIN = A5;


/*****************************************************************************
 *   Featuere activation and digital input pins cofiguration settings   
 *****************************************************************************/
const Input INPUT_CLUTCH =        { true, 5 };          // Clutch lever
const Input INPUT_HORN =          { true, 2, 1500 };    // Horn, activated using long press
const Input INPUT_HILO =          { true, 2 };          // Toggle headlight between High and Low beam
const Input INPUT_IND_LEFT =      { true, 4 };          // Indicator (turn signal) Left
const Input INPUT_IND_RIGHT =     { true, 3 };          // Indicator (turn signal) Right

const Input INPUT_DISP_SELECT =   { true, 8 };          // Select option on display
const Input INPUT_DISP_NEXT =     { true, 7 };          // Goto next menu/option on display
const Input INPUT_START_STOP =    { true, 6 };          // Engine start and ttop
const Input INPUT_BRAKE_FRONT =   { true, 9 };           // Front brake Lever


/*****************************************************************************
 *   OLED Display settings, according to Adafruit library
 *****************************************************************************/
const bool DISPLAY_POWERED_ON = true;                             // Initially the display is powered on
const uint8_t DISPLAY_PIN_SDA = A4;                               // The Pin attached to the display
const uint8_t DISPLAY_PIN_SCL = A5;                               // The Pin attached to the display
const uint8_t DISPLAY_SCREEN_ADDRESS = 0x3C;                      // See datasheet for Address; normally 0x3D for 128x64, 0x3C for 128x32
const uint8_t DISPLAY_OLED_RESET = -1;                            // Reset pin # (or -1 if sharing Arduino reset pin)
const uint8_t DISPLAY_SCREEN_WIDTH = 128;                         // OLED display width, in pixels
const uint8_t DISPLAY_SCREEN_HEIGHT = 64;                         // OLED display height, in pixels
const uint8_t DISPLAY_TEXT_SIZE = 1;                              // Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
const uint8_t DISPLAY_TEXT_CHAR_WIDTH = 6 * DISPLAY_TEXT_SIZE;    // Width of text written to display, adjusted according to text size
const uint8_t DISPLAY_TEXT_CHAR_HEIGHT = 8 * DISPLAY_TEXT_SIZE;   // Height of text written to display, adjusted according to text size
const unsigned long DISPLAY_OFF_WAIT_TIME = 4000;                 // Delay time in ms to auto turn off display after initiated, showing progressbar
const unsigned long DISPLAY_STATUSTEXT_OFF_WAIT_TIME = 3000;      // Delay time in ms to remove status text when inititated


/*****************************************************************************
 *   System Settings
 *****************************************************************************/

const bool SYSTEM_DEBUGMODE_DEFAULT_ON = true;                    // Option from menu to set in debug mode, this is inititally value

/*****************************************************************************
 *   Ignition control
 *****************************************************************************/

const bool IGN_PW_ENABLED = true;                 // Enable to turn on ignition using password
const Input IGN_PW_START_BUTTON = INPUT_CLUTCH;   // Button to start / reset password input
const uint8_t IGN_PW_LENGTH = 5;                      // Number of button presses for password
const Input IGN_PW[IGN_PW_LENGTH] = {             // The password as an array of inputs
    INPUT_IND_LEFT,
    INPUT_IND_RIGHT,
    INPUT_DISP_SELECT,
    INPUT_DISP_NEXT,
    INPUT_HORN 
};


/*****************************************************************************
 *   Relay module config
 *****************************************************************************/
 uint8_t RELAY_UNIT_PING_INTERVAL = 20;         // Number of seconds for each ping to relay unit for checking that communication is OK
