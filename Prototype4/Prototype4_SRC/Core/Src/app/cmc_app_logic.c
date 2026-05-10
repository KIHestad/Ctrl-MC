/**
  *********************************************************************************************
  * @file      cmc_app_logic.c
  * @brief     Application logic for initialization and processing loop
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */
  
#include "config/cmc_config_manager.h"
#include "app/cmc_app_logic.h"
#include "app/cmc_app_state.h"
#include "util/cmc_util_onboard_led.h"
#include "input/cmc_input.h"
#include "feature/cmc_features_manager.h"

// App initialization, called once at startup
void cmc_app_init(void) {
    
    // Show startup is running by inititate onboard LED blinking pattern that will change according to final results of initialization steps
    cmc_onboard_led_init();    

    // Check and read configuration
    cmc_config_manager_init();
    
    // Prepare app state machine
    cmc_app_state_init();
}

// Main processing, called repeatedly from main.c loop
void cmc_app_process(void) {

    // Only run system logic if app_state.system is success
    if (cmc_app_state.system.status == CMC_APP_STATE_STATUS_SUCCESS) {

        // No need to read CAN messages in this processing loop, they will be handled by interrupts enabled by the CAN manager
        // Scan all button inputs: debounce and detect click/hold events
        cmc_input_scannner_execute();
    
        // Send CAN messages to other units based on the current state and configuration (e.g., if horn is active, send horn CAN message, etc.)
    
        // Process features for this unit (e.g., if horn is active, check if system state indicates button hold or release check or if auto shut-off timer has expired and turn off if needed, etc.)
        cmc_features_process();

    }
    
    // Update onboard LED state on this unit, is done regardless of system state to ensure proper LED behavior with error indication as well
    cmc_onboard_led_process(); 

}