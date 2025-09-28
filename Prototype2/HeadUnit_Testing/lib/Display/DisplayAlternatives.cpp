// These are not in use, but kept for reference in case needed later
void background_gauges_vertical_rpm_tank()
{
    // Fuel gauge to right

    // Constants for drawing gauges
    // const int gaugeProgressbarFromCenter = 4;
    // const int gaugeProgressbarWidth = 11;
    // const int gaugeMarkerSize = 1;
    // const unsigned int gaugeTop = 40;
    // const unsigned int gaugeHeight = 50;

    // The backgorund for the gauges
    // u8g2.drawFrame((displayWidth/2) + gaugeProgressbarFromCenter, gaugeTop, gaugeProgressbarWidth, gaugeHeight);
    // // Draw checkmarks for 1/4, 1/2, 3/4 and full for fuel gauge to right
    // float checkmarkSpacing = gaugeHeight / 4.0;
    // float xPos = (displayWidth/2) + gaugeProgressbarFromCenter + gaugeProgressbarWidth;
    // float yPos = gaugeTop;
    // for (int i = 0; i < 4; i++) {
    //     u8g2.drawLine(xPos, yPos, xPos + gaugeMarkerSize, yPos);
    //     yPos += checkmarkSpacing;
    // }
    // yPos = gaugeTop + gaugeHeight - 1;
    // u8g2.drawLine(xPos, yPos, xPos + gaugeMarkerSize, yPos); // last checkmark manually to avoid float precision issues
    // // RPM gauge to left
    // u8g2.drawFrame((displayWidth/2) - gaugeProgressbarFromCenter - gaugeProgressbarWidth, gaugeTop, gaugeProgressbarWidth, gaugeHeight);
    // // Draw checkmarks per 1000 RPM up until max RPM gauge to left
    // int numberOfCheckmarks = (rpmGaugeMax + 999) / 1000; // Round up to nearest 1000
    // checkmarkSpacing = gaugeHeight / (float)numberOfCheckmarks;
    // xPos = (displayWidth/2) - gaugeProgressbarFromCenter - gaugeProgressbarWidth - 1;
    // yPos = gaugeTop;
    // for (int i = 0; i < numberOfCheckmarks; i++) {
    //     u8g2.drawLine(xPos, yPos, xPos - gaugeMarkerSize, yPos);
    //     yPos += checkmarkSpacing;
    // }
    // yPos = gaugeTop + gaugeHeight - 1;
    // u8g2.drawLine(xPos, yPos, xPos - gaugeMarkerSize, yPos); // last checkmark manually to avoid float precision issues
    // // Icons
    // u8g2.setFont(u8g2_font_speed_small);
    // u8g2.drawStr(0, gaugeTop + textStandardHeight, "<"); // Fuel icon from custom font
    // u8g2.drawStr(displayWidth - 9, gaugeTop + textStandardHeight, ">"); // Rpm icon from custom font
    
}

void gaugeFuel_vertical(float fuelLevel) {
    // // Calculate remaining distance based on current fuel level and average consumption
    // float fuelLevelPercentage = fuelLevel / fuelTankCapacity;
    // int fuelBarProgress = round((gaugeHeight - 2) * fuelLevelPercentage);
    // // Clear previous fuel bar and text area
    // int xPosBar = (displayWidth/2) + gaugeProgressbarFromCenter + 1;
    // clearArea(xPosBar, gaugeTop + 1, gaugeProgressbarWidth - 2, gaugeHeight -2); // progressbar
    // int xPosText = xPosBar + gaugeProgressbarWidth + gaugeMarkerSize + 1; 
    // clearArea(xPosText, gaugeTop + gaugeHeight - textStandardHeight - 2, displayWidth - xPosBar - 1 - gaugeMarkerSize, textStandardHeight); // text area
    // // Update fuel bar
    // int yPos = gaugeTop + 1 + (gaugeHeight - 2 - fuelBarProgress);
    // u8g2.drawBox(xPosBar, yPos, gaugeProgressbarWidth - 2, fuelBarProgress);
    // // Draw fuel text
    // u8g2.setFont(u8g2_font_speed_narrow); 
    // char txt[10];
    // sprintf(txt, "%.1f", fuelLevel);
    // int stringWidth = u8g2.getStrWidth(txt);
    // u8g2.drawStr(displayWidth - stringWidth -1, gaugeTop + gaugeHeight - 1, txt); // added fuel icon as character
}

void gaugeRpm_vertical(float rpm) {
    // // Calculate remaining distance based on current fuel level and average consumption
    // float rpmPercentage = rpm / rpmGaugeMax;
    // int rpmBarProgress = round((gaugeHeight - 2) * rpmPercentage);
    // // Clear previous rpm bar and text area
    // int xPosBar = (displayWidth/2) - gaugeProgressbarFromCenter - gaugeProgressbarWidth + 1;
    // clearArea(xPosBar, gaugeTop + 1, gaugeProgressbarWidth - 2, gaugeHeight -2); // progressbar
    // //clearArea(0, gaugeTop + gaugeHeight - textStandardHeight - 2, displayWidth - xPosBar - 1 - gaugeMarkerSize, textStandardHeight); // text area
    // // Update rpm bar
    // int yPos = gaugeTop + 1 + (gaugeHeight - 2 - rpmBarProgress);
    // u8g2.drawBox(xPosBar, yPos, gaugeProgressbarWidth - 2, rpmBarProgress);
    // // Draw rpm text
    // u8g2.setFont(u8g2_font_speed_narrow); 
    // char txt[10];
    // sprintf(txt, "%.1f", rpm / 1000.0);
    // u8g2.drawStr(0, gaugeTop + gaugeHeight -1, txt); // added fuel icon as character
}
