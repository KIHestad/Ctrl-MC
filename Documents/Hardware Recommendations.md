# Ctrl-MC // Hardware Recommendations

_The project is still in development phase, this list is will be changed as the project evolves_

## Electronics

Supported Arduino boards and other HW recommadations are not yet decided upon. HW used during initial dev stages are:

* Relay Unit:
  * Arduino board: Arduino Nano (ATmega328PB)
  * Relay module: 8 channel + 2 channel (12V) controlled by digital pins from the Arduino
    * Mosfet switches instead of relay module might have been better, but not found any suitable board yet
  
* Handlebar Unit:
  * NodeMCU / espressif8266: Curretly used but has not enough pins, considering EPS32 / STM32
  * Display: 0.96" I2C IIC SPI Serial 128X64 OLED LCD LED Display Module for Arduino or other 128x64 displays
    * 1.8" Color OLED displays looks interesting

* Power Supply / DC-DC stepdown 12V -> 5V
  * Motorcycles has normally 12V battery, ned reliable DC-DC step down
    * if lead acid battery on bike: voltage can vary depending on charge from 0-15V
    * if lithium battery: voltage can vary depending on charge from 9-13V
  * Need to figure out if possible to have one common power supply unit with long cabels, or if best having 2 separate close to unit
  * Product suggestion:
    * [DC-DC Auto Converter 2A 18W Full Range Regulator Step-up Step-down Power Module](https://www.ebay.com/itm/353687714361)

## Enclosure / Housing

Create 3D models in Fusion 360 for 3D printing

## Handlebar Control Switches

Handlebar control swithes will be made using water proof buttons and 3D printed case
* [Waterproof Momentary ON-OFF Push Button Round SPST Switch](https://www.ebay.com/itm/401560101338)

Here some options for prebuilt handlebar control swithes:
* [Motorcycle 3-Button 1" Handlebar Control Momentary Switch](https://www.ebay.com/itm/284179253202)
* [motogadget mo.switch basic](https://www.motogadget.com/shop/en/mo-switch-basic.html)



