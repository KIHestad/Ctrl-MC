![Ctrl-MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC-LogoText-White_Blue-BG_ver1.png)

# Motorcycle Control System

Ctrl MC (pronounced: "Control MC") is a system currently in development for simplifying and modernizing the wiring for motorcycles.

The project is being devloped by Ki Hestad: https://youtube.com/kihestad.
For updated information about the project check the YouTube channel and feel free to participate with idead or feedback for the projects Discord channel: [https://discord.gg/p5pfdZxfS8](https://discord.gg/p5pfdZxfS8)

Do you want to support this project? It's easy, just [click here to subscribe to the YouTube channel](https://youtube.com/kihestad/?sub_confirmation=1)!!!

## Project Description

This project is still in early stages, the idea is to:

* Create a motorcycle control system based on microcontrollers and canbus to simplify and improve the wiring harness with possibility to add modern features for 'classic' (=older) motorcycles
  * The main goal is to make an intuitive and reliable system for wiring up a motorcycles lights and instruments 
  * The project does not in the first phases aim to replace or modify the motorcycle engine ignition system, but maybe later?
* Provide software, schematics and instructions free of charge
* Create a community for motorcycle- and Arduino enthusiasts that want to contribute
* Make the solution universal and configurable, it should be suitable for as many motorcycle brands and models as possible

Long term goals, depending on the success of the project:
* Provide a DIY kit with all parts needed
* Provide a completely built solution ready to be installed on the bike

Some of the benefits the system (hopefully) will give:

* Reliability: Individual solid state relays with inbuilt automatic fuses controls 12V to the bikes electrical components
* Simplify wiring: Single cable per component, separat wiring for input controls on handlebar and output power to components
* Providing customization: Setting parameters to enable features and how they should work
* Gives posibility to improve or add new features to the motorcycle (optional): 
  * Touch buttons instead of traditional handlebar switches
  * Keyless ignition using bluetooth, RF-ID or "password" using input buttons
  * OLED display instead of traditional speedometer, tachometer and warning lights
  * Smart functions, ex: auto turn off indicator lights, not possible to trigger start motor when engine is running
  * Alarm if bike is moved
* Use standard components
* Provide a budget friendly solution as an alternative to expensive commercial products

## Development information

The software is developed using Visual Studio Code. The first prototypes where using are using Platform IO, Arduino framework and C++ language. The latest prototype is using STM32CubeIDE and C language. The software is open source and available in this GitHub repository.
* Prototype 1 was a first attempt having a display unit and a relay unit using serial communication to send data in between
* Prototype 2 was a standalone display unit for testing use of hall sensor for speedometer and IT sensor for rpm meter, one version using ESP32 was made for KI Hestad's Cagiva 750 Elefant, a second version was ported to STM32 microcontroller
* Prototype 3 is a simple canbus communication test using STM32 microcontroller, this is not to be used in further development but just for testing the canbus communication
* MC Wiring Simulator is a PCB designed as a supportng tool for testing and developing purposes. 

## Other info

Let me know if anything is missing, just go to the project [Discord channel](https://discord.gg/p5pfdZxfS8) ^_^

![Ctrl-MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC_Keyboard.png)
