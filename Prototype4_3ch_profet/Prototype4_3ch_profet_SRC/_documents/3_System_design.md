# System Design Principles

The system is designed to be modular, with clear separation between hardware abstraction and core application logic. Data structs and functions are separated into separate files, and each is responsible for a specific aspect of the system, such as sensor input processing, actuator control, and CANBUS communication.

The code aligns with the Sense-Compute-Actuate pattern, decoupled by a central app state: `cmc_app_state` that is the single source of truth. The app state is not just a global data store — it also acts as an event bus where changes trigger reactions from features across units. This allows for a reactive and flexible design where different units can respond to state changes without being tightly coupled to each other.

CAN bus messages are used for communication between units. Interrupts should only fetch data and set flags, these are written to app state. The main loop handles all processing and state management.

For data coming from the unit itself, like buttons and sensors, this is managed by the `cmc_app_state_updater`. 

The enabled features are responsible for reading the app state and driving outputs or performing actions based on that state. This separation allows for a clean and maintainable codebase where each component has a clear responsibility. The features are also where CAN messages are generated and transmitted to other units.

# System Logic Processing Flow
The following illustration shows the high-level system logic processing flows.

![System Logic Processing Flow](.\img\Ctrl_MC-System_Logic_Processing_Flow.png)

