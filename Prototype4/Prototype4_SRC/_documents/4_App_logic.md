# Application logic

This explains the application logic.

## Global configuration

The system is controlled by a global configuration, this is to be set by the user and contains all the settings for the system. The configuration is stored in a struct called `cmc_config_t` and is defined in `cmc_config_type.h`. The configuration is stored in flash memory and is loaded at startup. The configuration can be updated by the user and is saved to flash memory when the system is shut down.

