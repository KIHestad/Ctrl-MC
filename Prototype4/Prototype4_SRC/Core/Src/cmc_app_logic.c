#include "stm32g4xx_hal.h"
#include "cmc_app_logic.h"
#include "cmc_onboard_led.h"

void cmc_app_init(void) {
    cmc_onboard_led_init();
    cmc_onboard_led_blink_multiple(5,400,600); // LED on for 5 seconds, blinking to indicate startup
}

void cmc_app_process(void) {
    cmc_onboard_led_process(); // Update onboard LED state (e.g., turn off after blinking)
}