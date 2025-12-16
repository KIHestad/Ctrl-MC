/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

#include <OnBoardLed.h>
#include <Config.h>

// Constructor
OnBoardLed::OnBoardLed() {}

// Initialize onboard led
void OnBoardLed::init(Settings settings) {
    this->settings = settings;
    if (settings.enabled) {
        pinMode(settings.pin, OUTPUT);
        digitalWrite(settings.pin, settings.offValue);
    } 
}

// Actions
void OnBoardLed::on() {
    if (this->settings.enabled)
        digitalWrite(this->settings.pin, this->settings.onValue);
}

void OnBoardLed::off() {
    if (this->settings.enabled)
        digitalWrite(this->settings.pin, this->settings.offValue);
}

void OnBoardLed::set(int value) {
    if (this->settings.enabled)
        digitalWrite(this->settings.pin, value);
}

void OnBoardLed::blink(size_t blinkCount, unsigned long delayInMilliseconds) {
    if (this->settings.enabled) {
        for (size_t i = 0; i < blinkCount; i++)
        {
            digitalWrite(this->settings.pin, this->settings.onValue);
            delay(delayInMilliseconds);
            digitalWrite(this->settings.pin, this->settings.offValue);
            delay(delayInMilliseconds);
        }
    }
}