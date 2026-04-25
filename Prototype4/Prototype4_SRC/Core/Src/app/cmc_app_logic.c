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
    cmc_onboard_led_blink_multiple(5,400,600); // LED on for 5 seconds, blinking to indicate startup
    // Check and read configuration
    cmc_config_manager_init();


    // HAL_StatusTypeDef can_status = cmc_can_manager_init(); // Initialize CAN manager
    // if (can_status != HAL_OK) {
    //     cmc_onboard_led_blink(100, 100); // CAN initialization failed, indicate error fast blinking
    // }
}

// Main processing loop, called repeatedly from main.c
void cmc_app_process(void) {
    cmc_onboard_led_process(); // Update onboard LED state (e.g., turn off after blinking)
}