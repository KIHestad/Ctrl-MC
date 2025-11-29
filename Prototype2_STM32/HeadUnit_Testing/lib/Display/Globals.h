#ifndef DisplayGlobals_h
#define DisplayGlobals_h

#include <U8g2lib.h>

// Global u8g2 object declaration - actual definition is in DisplayGlobals.cpp
// STM32 I2C OLED display (128x64) connected to PB6 (SCL) and PB7 (SDA)
// Use SSD1306 for most common 0.96" OLED displays, or SH1106 for 1.3" displays
// extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
// For SH1106 1.3" displays:
extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

#endif