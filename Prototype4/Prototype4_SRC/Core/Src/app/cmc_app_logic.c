/**
  *********************************************************************************************
  * @file      cmc_app_logic.c
  * @brief     Application logic for initialization and processing loop
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "app/cmc_app_logic.h"
#include "util/cmc_util_onboard_led.h"
#include "config/cmc_config_manager.h"

// The active system configuration, loaded from flash at startup
cmc_config_t cmc_config;

// App initialization, called once at startup
void cmc_app_init(void) {
    
    // Show startup is running by inititate 5 blinks of the onboard LED
    cmc_onboard_led_init();    
    
    // Check and read configuration
    cmc_config_status_t cmc_config_status = cmc_config_manager_init();
    if (cmc_config_status == CMC_CONFIG_STATUS_SUCCESS) {
        cmc_onboard_led_blink_multiple(5, 400, 600); // Config load successful, indicate with 5 blinks
    } else {
        cmc_onboard_led_blink(125, 125); // Config load failed, indicate error with fast blinking 
    }
    
    // Inititate CAN manager, set up interrupts to update state machine when relevant incoming messages happens (not implemented yet)

}

// Main processing, called repeatedly from main.c loop
void cmc_app_process(void) {
    
    // Update onboard LED state on this unit (e.g., turn off after blinking)
    cmc_onboard_led_process(); 

    // No need to read CAN messages on the unit, they will be handled by interrupts enabled by the CAN manager
    // Read inputs for all relevant pins for this unit, buttons and sensors, and update the system state accordingly (e.g., set horn active if horn button is pressed, etc.)

    // Send CAN messages to other units based on the current state and configuration (e.g., if horn is active, send horn CAN message, etc.)

    // Process features for this unit (e.g., if horn is active, check if system state indicates button hold or release check or if auto shut-off timer has expired and turn off if needed, etc.)


}