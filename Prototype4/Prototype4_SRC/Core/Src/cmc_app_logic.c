#include "cmc_app_logic.h"
#include "cmc_input_pin.h"
#include "cmc_output_onboard_led.h"
#include "cmc_output_switch.h"
#include "stm32g4xx_hal.h"

void cmc_app_init(void) {
    switch_controller_init();
    cmc_output_onboard_led_init();
    cmc_input_pin_init();
}

void cmc_app_process(void) {

    switch_controller_process();

    // Get button state
    cmc_input_pin_handler();
    
    // Update LED state (e.g., turn off after blinking)
    cmc_output_onboard_led_process();
    
    // Check for button clicks for button 1 to 6 and toggle corresponding switch
    for (uint8_t button_number = 1; button_number <= 6; button_number++) {
        if (cmc_input_pin_button_clicked(button_number)) {
            cmc_input_pin_click_event_done(button_number);
            if (button_number == 5 || button_number == 6) {
                // Turn signals check for turn on or off based on current state, if off then blink, if on then turn off
                if (is_button_off(button_number)) {
                    switch_turn_on_blink(button_number);
                }
                else {
                    switch_turn_off(button_number);
                }
            }
            else {
                // Regular on/off switches
                switch_toggle(button_number);
            }
            cmc_output_onboard_led_blink_multiple(button_number, 300, 200);
        }
    }

    // Enable, disable or blink the onboard LED 
    cmc_output_onboard_led_process();
    
}