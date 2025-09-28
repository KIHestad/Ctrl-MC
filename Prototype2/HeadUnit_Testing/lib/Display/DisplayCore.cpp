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