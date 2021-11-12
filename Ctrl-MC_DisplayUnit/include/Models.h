/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

// System enums
enum TemperatureDefaultType { tempCelcius, tempFarenheit };
enum PinType {pinDigital, pinAnalog };
enum ChecBoxSelected { checkBoxLeft, checkBoxMid, checkBoxRight};
enum ImagePosition {imgPosMenuCenter, imgPosCenter, imgPos2Left, imgPos2Right, imgPos3Left, imgPos3RightTop, imgPos3RightBottom};



// Model for menu items
class MenuItem {
    public:
        uint8_t id; // Identifier used by code to know what to do
        String displayName; // Name of menu item to show on display
};

// Model for input pins
class Input {
    public:
        uint8_t pin; // pin number
        bool enabled; // enabled
};

