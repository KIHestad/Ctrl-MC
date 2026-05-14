/**
  *********************************************************************************************
  * @file      cmc_app_logic.c
  * @brief     Application logic for initialization and processing loop
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */
  
#include "util/cmc_util_onboard_led.h"
#include "config/cmc_config_manager.h"
#include "config/cmc_config_unit_info.h"
#include "app/cmc_app_logic.h"
#include "input/cmc_input.h"
#include "feature/cmc_features_manager.h"

// App initialization, called once at startup
void cmc_app_init(void) {
    
    // Show startup is running by inititate onboard LED blinking pattern
    cmc_onboard_led_init();    

    // Check and read configuration from flash to ram
    cmc_config_manager_init();
    
    // Check and read unit info from flash, if config is valid
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {
        cmc_config_unit_info_init();
    }

    // Continue if configuration and unit info is valid and status set to success
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {

        // Config and unit info should be valid at this point, set cmc_config_this_unit
        cmc_config_this_unit = &cmc_config.io_unit[cmc_app_state.system.unit_info.unit_id - 1];
        
        // Init app state machine with default values and from flash
        cmc_app_state_init();
        
        // Initialize button reading, sample initial GPIO states
        cmc_input_scanner_init();

        // Now initiate all features for this unit
        cmc_features_init();
    
    }
}

// Main processing, called repeatedly from main.c loop
void cmc_app_process(void) {

    // Only run system logic if app_state.system is success
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {

        // No need to read CAN messages in this processing loop, they will be handled by interrupts enabled by the CAN manager
        // Scan all button inputs: debounce and detect click/hold events
        cmc_input_scanner_execute();
    
        // Process features for this unit (e.g., if horn is active, check if system state indicates button hold or release check or if auto shut-off timer has expired and turn off if needed, etc.)
        cmc_features_process();

    }
    
    // Update onboard LED state on this unit, is done regardless of system state to ensure proper LED behavior with error indication as well
    cmc_onboard_led_process(); 

}