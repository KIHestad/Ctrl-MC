/**
  *********************************************************************************************
  * @file      cmc_app_logic.c
  * @brief     Application logic for initialization and processing loop
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */
  
#include "app/cmc_app_logic.h"
#include "app/cmc_app_state.h"
#include "config/cmc_config_manager.h"
#include "util/cmc_util_onboard_led.h"

// App initialization, called once at startup
void cmc_app_init(void) {
    
    // Show startup is running by inititate onboard LED blinking pattern that will change according to final results of initialization steps
    cmc_onboard_led_init();    
    cmc_onboard_led_blink(100, 400); // Startup initiated, indicate with slow tiny blinking

    // Check and read configuration
    cmc_config_status_t cmc_config_status = cmc_config_manager_init();
    if (cmc_config_status == CMC_CONFIG_STATUS_SUCCESS) {
        cmc_onboard_led_blink_multiple(5, 400, 600); // Config load successful, indicate with 5 blinks
    } else {
        cmc_onboard_led_blink(100, 100); // Config load failed, indicate error with fast blinking
    }
    
    // Prepare app state machine
    cmc_app_state_init();


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