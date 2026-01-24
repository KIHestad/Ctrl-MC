![Ctrl-MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC-LogoText-White_Blue-BG_ver1.png)

# Motorcycle Wiring Simulator

The Motorcycle Wiring Simulator is a PBC that is to be used to development and testing motorcycle wiring. 

The schematics and PCB layout for the custom PCB module can be found in the zipped file in this folder. It's an achived KiCad project (version 9.0.5).

Version 1.0 is shown in the video below. The latest version 1.1 has some minor improvements:

* The resistors to limit the voltage for the LEDs are changed according to version 1.0. The new resisrors reduces and balances the brightness.
* The buzzer is changed to a 12V type instaed of a 5V type with 680 ohm resistor to limit the voltage. The buzzer is also included in the parts list for ordering from JLCPCB.
* The pin headers are moved to the edge of the PCB and the lables are moved to the other side of the pin headers to make it easier to read the labels when working with the module.
* The KiCad project includes part numbers for fabrication and assembly from JLCPCB. Pin headers are marked as excluded so they will by default not be added into the BOM- and placement file. Add part numbers and include them to BOM and placement file if you want JLCPCB to mount them for you.

Check this YouTube video for demo of the system:
* I Turned a Motorcycle Into a Circuit Board - https://youtu.be/JKvbBq6Y1_M?si=p860frQD5cO-tTMq

