#include "Globals.h"

// Define the actual u8g2 object here
// STM32 I2C OLED display (128x64) connected to PB6 (SCL) and PB7 (SDA)

// Test different drivers for Diymore 1.3" OLED:

// Option 1: SH1106 (most common for 1.3" displays)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R1, /* reset=*/ U8X8_PIN_NONE);

// Option 2: Alternative SH1106 variant (uncomment to test)
// U8G2_SH1106_128X64_VCOMH0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Option 3: SSD1306 variant (uncomment to test)
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Option 4: Software I2C (if hardware I2C doesn't work)
// U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ PB6, /* data=*/ PB7, /* reset=*/ U8X8_PIN_NONE);
