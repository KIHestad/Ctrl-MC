![Ctrl MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC-LogoText-White_Blue-BG_ver1.png)

# Arduino Motorcycle Controller Software - PROTOTYPE 3

The prototype 3 is just a simple software for testing canbus communication. This code is not to be used in further development. 

The software is made to be used on a WeAct Studio STM32G431 dev board, and a custom PCB module with power management and canbus tranciever. The STM32 dev board has a built in button, when this is pressed a canbus message (a integer) is sent, if a canbus message is received a LED on the board is toggled (number of blinks = the number received).

The code assumes the is built using VS Code with the STM32 extensions. The setup is explained in the document:

*  [Ctrl MC Software Stack Setup.pdf](https://github.com/KIHestad/Ctrl-MC/blob/main/Documents/Ctrl-MC%20Software%20Stack%20Setup.pdf)

The schematics and PCB layout for the custom PCB module can be found in the zipped file `KiCad_Schematics.zip`, this is a achived KiCad project (version 9.0.5).

Check this YouTube video for demo of the system:
* Building a MC Wiring System with CANBUS - https://youtu.be/ZHVgKvK5CPY?si=S1eG1M-LmAs4Nri0

