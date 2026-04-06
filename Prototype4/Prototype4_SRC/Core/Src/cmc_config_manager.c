#include "cmc_config_manager.h"
#include "cmc_config_defaults.h" // Your hardcoded fallback
#include "stm32g4xx_hal.h"       // For Flash and CRC access
#include <string.h> // Included for memcpy

// Define the global variable from the extern declaration in cmc_config_type.h
cmc_global_config_t cmc_global_config;

// Define where the Flash storage starts (The "Archive")
static const cmc_global_config_t* flash_config = (cmc_global_config_t*)0x0801F800; // Last 2KB of Flash for config storage

bool cmc_config_manager_init(void) {
    bool is_valid = false;
    
    // 1. Look at the Flash memory...
    if (cmc_global_config.signature == CMC_CONFIG_SIGNATURE) {
        is_valid = cmc_config_manager_validate(&cmc_global_config);
    }
    
    // 2. Make the decision
    if (is_valid) {
        // Safe! Copy from Flash to active RAM
        memcpy(&cmc_global_config, flash_config, sizeof(cmc_global_config_t));
        return true;
    } else {
        // DANGER! Memory is corrupt or brand new.
        // The Manager tells the Defaults file to do its job:
        cmc_configdefaults_load(); 
        
        return false; // Returns false so the system knows it's using factory settings
    }
};

bool cmc_config_manager_validate(cmc_global_config_t* target_config) {
    // For now, we don't have any specific validation steps, but this is where you would add them if needed in the future.
    return true; // Return true to indicate successful validation
};

bool cmc_config_manager_save_to_flash(cmc_global_config_t* new_config) {
    // For now, we don't have any specific flash writing steps, but this is where you would add them if needed in the future.
    return true; // Return true to indicate successful save
};

