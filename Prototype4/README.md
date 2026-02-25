![Ctrl MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC-LogoText-White_Blue-BG_ver1.png)

# PROTOTYPE 4 - STM32 with Infineon Profet +12V Smart Switch modules

The prototype 4 is a simple software for testing Infineon Profet +12V Smart Switches. This code is not to be directly used in further development, but elements from it can be relevant. 

The software is made to be used on a WeAct Studio STM32G431 dev board, and two custom PCB modules with each a 15Amp switch and 2 x 5Amp swithc. Input GPIO's are also configuret to be able to test turning the switches on and off. It's tested with the MC Wiring Simulator.

The code is built using VS Code with the STM32 extensions. The setup is explained in the document:

*  [Ctrl MC Software Stack Setup.pdf](https://github.com/KIHestad/Ctrl-MC/blob/main/Documents/Ctrl-MC%20Software%20Stack%20Setup.pdf)

The schematics and PCB layout for the custom PCB module can be found in the zipped file `KiCad_Schematics_SmartSwitchesModule.zip`, this is a achived KiCad project (version 9.0.5).

A YouTube video for demo of the system is in the making.

