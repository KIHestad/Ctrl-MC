# Introduction

The documents in this folder a high-level overview of the code and its structure. The code is primarily commented inline. 

## The Ctrl MC system
Goto [KI Hestad's homepage](https://hestad.no) or the [Ctrl MC GitHub repository](https://github.com/KIHestad/Ctrl-MC) for more information about the Ctrl MC system.

## About Prototype 4
Prototype 4 is a prototype of the Ctrl MC system, primarely for testing out a fully working prototype of the I/O units based on STM32 microcontoller, Inifion PROFET high-side smart switches and canbus communication for connecting multiple I/O units.

## User Manual

As the system boots up the unit flashes very fast (50ms/150ms = 5 blinks per sec). This is normally such a short time it's not noticable. If this is observed it is most likely a startup issue where the system has crashed before any error handling has been invoked. 

When the unit starts up successfully after memory is cleared, the unit goes into a configuration mode for setting unit id. The onboard LED is flashing medium fast (50ms/950ms = 1 blink per sec) and waits for a button press, when button 1-4 is pressed (short to GND) this will be the unit id.

When unit id is set and the system starts successfully, the unit goes into normal operation mode. 
The onboard LED is flashing every 5th second with number of blinks idincating the unit id.

If an startup error occurs, the unit onboard LED flashes fast the number of blinks representing the error code, repeated every second. The error codes are as the number for the enum: `cmc_app_state_status_t`