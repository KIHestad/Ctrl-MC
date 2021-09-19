/*
 *   Ctrl-MC // Arduino motorcycle controller software made by KI Hestad: https://github.com/KIHestad/Ctrl-MC
 */

/*****************************************************************************
 *   Output Pins cofiguration settings   
 *****************************************************************************/

// Pin to arduino onboard led
int ONBOARD_LED_PIN = 13;

// Pins to OLED Display using I2C interface, SCL and SDA pins
int DISPLAY_SDA_OUTPUT_PIN = A4;
int DISPLAY_SCL_OUTPUT_PIN = A5;

/*****************************************************************************
 *   Digital Input Pins cofiguration settings   
 *****************************************************************************/
Input INPUT_CLUTCH =        { true, 5 };          // Clutch lever
Input INPUT_HORN =          { true, 2, 1500 };    // Horn, activated using long press
Input INPUT_HILO =          { true, 2 };          // Toggle headlight between High and Low beam
Input INPUT_IND_LEFT =      { true, 4 };          // Indicator (turn signal) Left
Input INPUT_IND_RIGHT =     { true, 3 };          // Indicator (turn signal) Right

Input INPUT_DISP_SELECT =   { true, 8 };          // Select option on display
Input INPUT_DISP_NEXT =     { true, 7 };          // Goto next menu/option on display
Input INPUT_START_STOP =    { true, 6 };          // Engine start and ttop
Input INPUT_BRAKE_FRONT =   { true, 9 };           // Front brake Lever


/*****************************************************************************
 *   OLED Display settings, according to Adafruit library
 *****************************************************************************/
bool DISPLAY_POWERED_ON = true;     // Initially the display is powered on
int DISPLAY_PIN_SDA = A4;           // The Pin attached to the display
int DISPLAY_PIN_SCL = A5;           // The Pin attached to the display
int DISPLAY_SCREEN_ADDRESS = 0x3C;  // See datasheet for Address; normally 0x3D for 128x64, 0x3C for 128x32
int DISPLAY_OLED_RESET = -1;        // Reset pin # (or -1 if sharing Arduino reset pin)
int DISPLAY_SCREEN_WIDTH = 128;     // OLED display width, in pixels
int DISPLAY_SCREEN_HEIGHT = 64;     // OLED display height, in pixels
int DISPLAY_TEXT_SIZE = 1;          // Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
int DISPLAY_TEXT_CHAR_WIDTH = 6 * DISPLAY_TEXT_SIZE;    // Width of text written to display, adjusted according to text size
int DISPLAY_TEXT_CHAR_HEIGHT = 8 * DISPLAY_TEXT_SIZE;   // Height of text written to display, adjusted according to text size
long DISPLAY_OFF_WAIT_TIME = 4000;  // Time to auto turn off display

/*****************************************************************************
 *   Ignition control
 *****************************************************************************/

bool IGN_PW_ENABLED = true;                 // Enable to turn on ignition using password
Input IGN_PW_START_BUTTON = INPUT_CLUTCH;   // Button to start / reset password input
const int IGN_PW_LENGTH = 5;                      // Number of button presses for password
Input IGN_PW[IGN_PW_LENGTH] = {             // The password as an array of inputs
    INPUT_IND_LEFT,
    INPUT_IND_RIGHT,
    INPUT_DISP_SELECT,
    INPUT_DISP_NEXT,
    INPUT_HORN 
};