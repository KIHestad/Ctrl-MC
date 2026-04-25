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

}

// Main processing loop, called repeatedly from main.c
void cmc_app_process(void) {
    cmc_onboard_led_process(); // Update onboard LED state (e.g., turn off after blinking)
}