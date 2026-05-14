# Application logic

This explains the application logic.

## Global configuration: cmc_config - flash region: CONFIG (r)

The system is controlled by a global configuration, this is to be set by the user and contains all the settings for the system. All units on the system must have the exact same configuration. A CRC checksum is compared across units to ensure there is no misconfiguration.

The configuration is stored in a struct called `cmc_config_t` and is defined in `cmc_config_type.h`. The configuration is stored in flash memory and is loaded at startup. 

A new unit might be loaded with a new config, when this happens other units will be updated to use the new configuration. A new unit could be "empty", it will then request a valid using canbus and be updated with what is in use on other units. A new config can also be inserted by a dedicated programming unit. 

For the prototype the config is hardcoded by the user by editing the `cmc_config_default`. This is loaded on startup if config is not present in flash. When flashing a unit a complete erase of flash must be done to force the default config to be loaded on first startup after flashing. 

## Unit info: cmc_unit_info - flash region: UNIT_INFO (r)

The unit info is a struct that contains information about the individual unit. The unit id is very important, there can not be two units on the system with the same id. This ensures that each unit can be uniquely identified and addressed on the canbus, and when troubleshooting the user can easily identify the unit.

The unit info is stored in flash memory and is loaded at startup. For a new unit with flash erased, the unit info can be updated by the user by pressing a button during startup. 

## Usage Journal: cmc_usage_journal - flash region: USAGE_JOURNAL (r)

The usage journal is a struct that contains information about the usage of the system. Typical data to be stored is distance ridden (total and trip counter), max speed, average speed, ride time, etc. The usage journal is stored in flash memory by rotating what byte position the storage happens to not wear out the flash memory, and is updated during runtime in suitable intervals.

## Startup sequence: cmc_app_logic.cmc_app_init

The startup sequence reads alle the necessary data from flash (listed above), checks if it is valid, and triggers initialization routines or warnings if needed. The cmc_app_state.system.status is set accoring to the startup result. If error the system will inititate a blink pattern on the onboard LED to indicate the error. 

If startup is successful the system will proceed to normal operation and the unit will blink every 5 seconds to indicate success and number of rapid blinks tells the unit id.

The startup sequence will also set canbus interrupts according to what features are enabled and active on the unit.

## Normal operation: cmc_app_logic.cmc_app_execute

During normal operation the system will continuously scan for input, update the state of the system, and execute features based on the state and input. The system will also periodically save the usage journal to flash.

Units are handled by interrupts and not shown as a separate function as part of the main loop.

