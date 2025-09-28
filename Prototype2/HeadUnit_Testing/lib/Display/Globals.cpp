#include "Globals.h"

// Define the actual u8g2 object here
// 1.3" OLED display
// U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R1, /* reset=*/ U8X8_PIN_NONE);
// 2.4" OLED display
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R1, 5, 3, 1); // Using SPI, parameters: portrait rotation, pins for cs, dc and reset