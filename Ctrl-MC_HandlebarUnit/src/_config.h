/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

/*****************************************************************************
 *   Relay Unit Pins cofiguration settings   
 *****************************************************************************/
const uint8_t RELAY_IND_LEFT = 1;
const uint8_t RELAY_IND_RIGHT = 0;

/*****************************************************************************
 *   Output Pins cofiguration settings   
 *****************************************************************************/
const uint8_t ONBOARD_LED_PIN = LED_BUILTIN;              // The pin number or ref to board variable for the pins controlling onboard led
const uint8_t ONBOARD_LED_ON = LOW;                       // Set HIGH or LOW to determin what sets the onboard led on or off
const uint8_t ONBOARD_LED_OFF = HIGH;                     // Ex: for Arduino Uno/Nano led in on using HIGH, but for NodeMCU led is on using LOW

/*****************************************************************************
 *   Featuere activation and digital input pins cofiguration settings   
 *****************************************************************************/
const Input INPUT_CLUTCH =        { false, 0, pinDigital };   // Clutch lever
const Input INPUT_HORN =          { false, 0, pinDigital };   // Horn, activated using long press
const Input INPUT_HILO =          { true, D4, pinDigital };    // Toggle headlight between High and Low beam
const Input INPUT_IND_LEFT =      { true, D3, pinDigital };    // Indicator (turn signal) Left
const Input INPUT_IND_RIGHT =     { true, D7, pinDigital };    // Indicator (turn signal) Right

const Input INPUT_MENU_SELECT =   { true,  D5, pinDigital };   // Button for Display Menu select/toggle/activate option
const Input INPUT_MENU_NEXT =     { true,  D6, pinDigital };   // Button for Display Mneu for goto next menu/option on display
const Input INPUT_START_STOP =    { false, 0, pinDigital };    // Engine start and ttop
const Input INPUT_BRAKE_FRONT =   { false, 0, pinDigital };    // Front brake Lever

const uint8_t INPUT_ANALOG_DEVIATION_ACCEPTED = 50;            // For analog value read the signal will vary, this set +/- acceptance according to expected value

/*****************************************************************************
 *   OLED Display settings, according to Adafruit library
 *****************************************************************************/
const bool DISPLAY_POWERED_ON = true;                               // Initially the display is powered on
const uint8_t DISPLAY_PIN_SDA = D2;                                 // The Pin attached to the display, for Arduino Nano: A4, for NodeMCU D2
const uint8_t DISPLAY_PIN_SCL = D1;                                 // The Pin attached to the display, for Arduino Nano: A5, for NodeMCU D1
const uint8_t DISPLAY_SCREEN_ADDRESS = 0x3C;                        // See datasheet for Address; normally 0x3D for 128x64, 0x3C for 128x32
const int8_t DISPLAY_OLED_RESET = -1;                               // Reset pin # (or -1 if sharing Arduino reset pin)
const uint8_t DISPLAY_SCREEN_WIDTH = 128;                           // OLED display width, in pixels
const uint8_t DISPLAY_SCREEN_HEIGHT = 64;                           // OLED display height, in pixels
const uint8_t DISPLAY_TEXT_SIZE = 1;                                // Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc these numbers include one extra pixel for space
const uint8_t DISPLAY_TEXT_CHAR_WIDTH = 6 * DISPLAY_TEXT_SIZE;      // Width of text INCLUDING ONE PIXEL FOR SEPARATION BETWEEN CHARS written to display, adjusted according to text size
const uint8_t DISPLAY_TEXT_CHAR_HEIGHT = 7 * DISPLAY_TEXT_SIZE;     // Height of text EXCLUDING PIXEL FOR SEPARATION BETWEEB ROWS written to display, adjusted according to text size


/*****************************************************************************
 *   System Settings
 *****************************************************************************/

const bool SYSTEM_DEBUGMODE_DEFAULT_ON = true;                          // Option from menu to set in debug mode, this is inititally value
const bool SYSTEM_HANDSHAKE_IGNORE_COMM_ERROR = true;                   // For debugging only, should always be set to true. If set false comm errors are ignoerd.
const long SYSTEM_HANDSHAKE_CHECK_INTERVAL = 15;                        // Number of seconds for each ping to relay unit for checking that communication is OK
const TemperatureDefaultType SYSTEM_TEMP_DEFAULT_TYPE = tempCelcius;    // Default temp display type

/*****************************************************************************
 *   Ignition control
 *****************************************************************************/

const bool IGN_PW_ENABLED = true;                       // Enable to turn on ignition using password
const Input IGN_PW_START_BUTTON = INPUT_MENU_NEXT;      // Button to start / reset password input
const uint8_t IGN_PW_LENGTH = 4;                        // Number of button presses for password
const Input IGN_PW[IGN_PW_LENGTH] = {                   // The password as an array of inputs
    INPUT_IND_LEFT,
    INPUT_IND_RIGHT,
    INPUT_MENU_NEXT,
    INPUT_MENU_SELECT
};

/*****************************************************************************
 *   Turn signal settings
 *****************************************************************************/
const unsigned long IND_BLINK_SPEED = 700; // Milliseconds for each blink, should be from 500 (fast) to 1500 (slow)
const uint8_t IND_AUTO_SHUTOFF = 30; // Number of seconds from left/right turn signal shoul be automatically turned off, not for hazard, 0 = not use

/*****************************************************************************
 *   Display Menues
 *****************************************************************************/

// Display settings
const uint8_t MENU_SHUTDOWN_WAIT = 6; // Number of seconds a menu item is shown before automatically shut down and go back to status screen
const unsigned long MENU_STATUS_PAGE_PROGRESSBAR_DURATON = 4000; // Delay time in ms for progressbar to be shown when initiated to switch over to show status page from another page

// List of available menu items, do not remove any or change ID, name can be modified / translated
const MenuItem MENU_IGNITION = { 1, "IGNITION" }; // Show ignition status, possible to turn off
const MenuItem MENU_STOPWATCH = { 2, "STOPWATCH" }; // Built in timer
const MenuItem MENU_TEMP_OUTSIDE = { 3, "TEMPERATURE" }; // Read from handlebar unit
const MenuItem MENU_TEMP_SYSTEM = { 4, "SYSTEM TEMP" }; // Read from relay unit
const MenuItem MENU_LIGHTS = { 5, "LIGHTS" }; // Control Ligths - OFF / PARK / ON

// Selected menu items in the order they will appear
const uint8_t MENUS_AVAILABLE_LENGTH = 4;
const MenuItem MENUS_AVAILABLE[MENUS_AVAILABLE_LENGTH] = {
    MENU_LIGHTS,
    MENU_IGNITION,
    MENU_STOPWATCH,
    MENU_TEMP_SYSTEM
};


