#Getting Started with Ardu MC Controller

_document is currently in progress_

## Electronics

Supported Arduino boards and other HW recommadations are not yet decided upon. HW used during initial dev stages are:
* Arduino board: Arduino Nano (ATmega328PB)
  * Other Arduino boards will be considered later, this board has not built in bluetooth support
  * The board "Arduino Nano 33 BLE" looks interesting for a compact bord with bluetooth
  * NodeMCU also looks interesting, but seems to have to few input/output pins
  * Bigger boards seems more capable, but size matter... do not want a to bulky solution
* Relay module: 12V 8 channel + 2 channel controlled by digital pins from the Arduino
  * Mosfet switches would have been better, but not found any with many ports yet for an acceptable price
* Display: 0.96" I2C IIC SPI Serial 128X64 OLED LCD LED Display Module for Arduino

## MC Controller Case

A case for the controller will be 3D printed. 

## Handlebar Control Switches

Handlebar control swithes will be made using water proof buttons and 3D printed case
* [Waterproof Momentary ON-OFF Push Button Round SPST Switch]https://www.ebay.com/itm/401560101338

Here some options for prebuilt Handlebar control swithes:
* [Motorcycle 3-Button 1" Handlebar Control Momentary Switch]https://www.ebay.com/itm/284179253202
* [motogadget mo.switch basic]https://www.motogadget.com/shop/en/mo-switch-basic.html

To avoid using to many pins on the Arduino, the buttons will have to be wired in series with a resistor in between.
Using an analog input port on the Arduiono can detect what switch is pressed. 
This will not make it possible to detect if multiple switches are pressed simoultaniosly, 
in that case the button should be mapped to a digital pin with separate wiring.
A combination of this can be selected.

## Assembly

Time will show ^_^


