#include "Display.h"

// Constructor, initialize display properties
void Display::init(int rpmGaugeMax, int rpmGaugeDanger, int rpmGaugeWarning, float fuelTankCapacity, float fuelAvgConsumption) {
    // Initialize display
    u8g2.begin();
    // Get display dimensions
    displayWidth = u8g2.getDisplayWidth();
    displayHeight = u8g2.getDisplayHeight();
    // Set constant display properties
    this->rpmGaugeMax = rpmGaugeMax;
    this->rpmGaugeWarning = rpmGaugeWarning;
    this->rpmGaugeDanger = rpmGaugeDanger;
    this->fuelTankCapacity = fuelTankCapacity;
    this->fuelAvgConsumption = fuelAvgConsumption;
    // Clear display
    clearDisplay();
    // Splash screen
    splash();
}

void Display::splash() {
    // Draw splash text
    u8g2.setFont(u8g2_font_tenthinnerguys_tf); 
    int yPos = (displayHeight + textStandardHeight) / 2; // display text centered vertically
    textCentered(yPos - 20, "Cagiva");
    outputNow();
    delay(200);
    textCentered(yPos - 00, "Elefant");
    outputNow();
    delay(200);
    textCentered(yPos + 20, "750");
    outputNow();
    // Output to display
    delay(1000); // Show splash for 2 seconds
    // Clear display after splash
    clearDisplay();
}

void Display::outputNow() {
    u8g2.sendBuffer();
}

void Display::clearDisplay() {    
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    u8g2.setDrawColor(1);
}

void Display::startupAnimation(float fuelLevel) {
    // Setup background
    background();
    backgroundRpm();
    backgroundFuel();
    speed(0); // Start with 0 speed
    fuel(0); // Start with empty fuel tank
    //backgroundMenuCheckboxes();
    //menu(0, false); // Menu page 0, no auto pager
    //menuName("Welcome");
    outputNow();

    // Rpm area animation, loop over rpm step by 250 from o to max rpm
    int rpmStep = 500;
    int rpmAnimationDelay = 50;
    for (int animatedRpm = 0; animatedRpm <= rpmGaugeMax; animatedRpm += rpmStep) {
        if (animatedRpm > rpmGaugeMax) animatedRpm = rpmGaugeMax; // Cap to max
        rpm(animatedRpm);
        outputNow();
        delay(rpmAnimationDelay);
    }
    for (int animatedRpm = rpmGaugeMax; animatedRpm >= 0; animatedRpm -= rpmStep) {
        if (animatedRpm < 0) animatedRpm = 0; // Cap to min
        rpm(animatedRpm);
        outputNow();
        delay(rpmAnimationDelay);
    }

    // Fuel area animation, loop over fuel level by 1/8 tank steps
    float fuelStep = fuelTankCapacity / 20.0;
    int fuelAnimationDelay = 50;
    for (float animatedFuel = 0; animatedFuel <= fuelTankCapacity; animatedFuel += fuelStep) {
        if (animatedFuel > fuelTankCapacity) animatedFuel = fuelTankCapacity; // Cap to max
        fuel(animatedFuel);
        outputNow();
        delay(fuelAnimationDelay);
    }
    for (float animatedFuel = fuelTankCapacity; animatedFuel >= fuelLevel; animatedFuel -= fuelStep) {
        if (animatedFuel < fuelLevel) animatedFuel = fuelLevel; // Cap to actual fuel level
        fuel(animatedFuel);
        outputNow();
        delay(fuelAnimationDelay);
    }

}