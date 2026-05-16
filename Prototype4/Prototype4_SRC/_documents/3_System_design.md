# System Design

The following illustration shows the high-level system design of the Ctrl-MC firmware. The system is designed to be modular, with clear separation between hardware abstraction and core application logic. Each module is responsible for a specific aspect of the system, such as sensor input processing, actuator control, and CANBUS communication.

The code should follow the aligns with the Sense-Compute-Actuate pattern, decoupled by a central "App-State". This keeps the hardware drivers ignorant of business logic.

Canbus messages are used for communication between different units, and the system is designed to handle multiple units in a networked environment. Interrups should only fetch data and set flags, while the main loop with business logic should handle the processing of data and state management.

![System Design Illustration](.\img\Ctrl_MC-System_Design_Illustration.png)

