#Development Log 2021

_This document is some kind of journal, I'm not really sure yet what it is._
_It will randomly be updated by me as the project evolves._
_I do not expect anyone to be bothered reading this,_
_it is more or less written by me to myself..._
_...but if you accidentally end up here - feel free to take a look :-)_

_Best regards_
_KI Hestad_

##How it all began - September 2021
The beginning of it all is more or less summarized in my YouTube video: [Motorcycle Wiring done differently - this can be BIG!](https://youtu.be/3W9Y04q-X2k)

What I did not include in the video was a couple of failed attempts, version 1 and 2:

##Version 0.1 - September 2021
I started the project trying to use only one Arduino Nano. It was supposed to be located under the seat tray near the battery and the relays. This required long cables to the handlebar for attaching to buttons and the display. There were not enough pins on the board for individual input and outputs, so I tested using multiple buttons with resistors in between and read signals from the buttons using analogRead.
 
It worked with short cables, but there were not reliable signals when using a long cable (around 1.5m). 
Another problem occured when I got the OLED display, it did not work at all using long cables. The I2C communication framework used for the display does not work over long cables.

##Version 0.2 - September 2021
After some research I found the serial communication option using the RX/TX pins and switched over to using two Arduino Nanos. That worked great! It solved multiple problems, now I put the arduinos close to the display/relay unit, and I got twice as many pins to use for input/outputs. 

Because of this I could change from using a single pin for multiple buttons to using a separate input pin per button and changed to digitalRead. This makes it possible to read input signals when several buttons are pressed simultaneously, and the readings are more reliable and easier to set up.

This configuration worked for a while, until the c++ code became bigger and there was not enough memory on the Arduino Nano for the handlebar unit. The Adafruit OLED library needs about 1K SRAM just for driving the display, the total of 2K on the Arduino Nano board was not enough.

##Version 0.3 = September 2021
I had a NodeMCU / esp8266 laying around. It has a lot more memory and is much faster. It required just some minor code changes and I could continue the development. However this board has only 5 usable input pins available for buttons after the OLED display and the serial communication has occupied the pins they need.
The NodeMCU board is also a bit big, I would like to have a small form factor to make the handlebar unit compact. 

I started to check out different Arduino boards that could be better suitable for the handlebar unit, but I managed to use the NodeMCU with limited number
of buttons to at least create the first usable version of the system.

##From private project to Open Source
When I started the job on this project in the beginning of September 2021, the plan was to make a solution for my bike only, and create a video of it to share on YouTube. I have always been a fan of open source projects. I have used a lot of free software from open source projects. Some examples: I have been using several Linux distros, and my 3D-printer is running on software from open source projects (Marlin, OctoPrint). 

As the project went along, and I finally started to get it to work, I thought this project could be my chance to contribute to the "Open Source World". If the solution I have started on can be of use for others, why not. As I have not much experience with electronics and Arduino development it might also help the project
going forward if others would like to contribute. 

I have gained quite some experience with programming and software development in general over the years, mostly on Windows and web. The languages I know best is C#, but I have been using a lot of languages: Basic, Java, JavaScript, Pascal, Perl, Python, Visual Basic, and probably more. C++is a programming language I have not used before, but learning a new programming language is not that hard  :-) Each language has its tricks and quirks though, it takes time to master it fully.

##Publishing the first YouTube video about the project - October 2021
I decided to create a video of what I have done so far, and at the same time check if there was any interest from others to participate. No need to say more - it is all covered in the YouTube video: [Motorcycle Wiring done differently - this can be BIG!](https://youtu.be/3W9Y04q-X2k)

I also posted a link to the video on a couple of Facebook Arduino groups, and hoped someone would find the project interesting. The feedback on the video and the project was very positive, a lot of comments both on FB and on the YouTube channel. That is great! @Ramjet from Australia reached out and offered his help, he also set up the [Discord Channel: Ctrl-MC](https://discord.gg/ccT6R4EF)

##Preparing Version 0.4 - October 2021
Several viewers have suggested using solid state relays instead for the traditional relay module I have planned for. @Ramjet has suggested creating a custom one designed as a perfect fit for the relay unit. This is a much better solution, more compact and energy efficient, and with no moving parts hopefully also more durable. Lets see how this goes :-)

In the serch for finding a better Arduino board for the handlebar unit, a couple of STM32 boards was aqured. I thought could be the right solution for the handlebar unit. It is quite powerful, has a lot of pins and it is very small. The boards use a 32bit ARM based CPU, quite a beast, but after some more research it seems to be a bit complex to set up. It needs a USB 2.0 to TTL Serial Adapter for flashing code to it as there is no built in bootloader. Seems like not all Arduino libraries supports this bord either. 

I ended up buying a 30 pins ESP32 (ESP32 NodeMCU Module Board WiFi Bluetooth CP2102 ESP-32S 2.4GHZ). This board is flexible when it comes to pin usage, most can be used for both input and output. It has WiFi & BT as well, this can be useful for future upgrades like: turn on/off ignintion or configure settings from smartphone. The board worked perfectly, and will be the one to use for the next version.

A 8 channel relay unit has also been bought and will be used in addition to the 2 channel relay used for demoing version 0.3. A slightly bigger 1.3" OLED display will replace the first 0.96" display.

Some 3D-printed enclosures will also be made.





