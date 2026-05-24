![Ctrl MC logo](https://hestad.no/img/ctrl-mc/Ctrl-MC-LogoText-White_Blue-BG_ver1.png)

# CanSniffer

This is a simple software for sniffing on can bus messages from the Ctrl MC system. It's made so it's possible to connect the system to a computer to inspect canbus messages being transferred on the bus. It's not just sniffing btw, it's also possible to send messages to the can bus, but this is not the main purpose of the software.

The software is made to be used on a WeAct Studio STM32G431 dev board, and a custom power and can bus transceiver PCB module made as part of the Ctrl MC project. 

When using SavvyCan, select connection type "Serial Connection (GVRET) and select highest speed (1000000).

Upload the cmc_can_message.dbc to the DBC File Manager in SavvyCan to get the message names and signals. 

The code is built using VS Code with the STM32 extensions. The setup is explained in the document:

*  [Ctrl MC Software Stack Setup.pdf](https://github.com/KIHestad/Ctrl-MC/blob/main/Documents/Ctrl-MC%20Software%20Stack%20Setup.pdf)

