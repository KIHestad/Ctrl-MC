#include "cmc_app_logic.h"
#include "cmc_button_handler.h"
#include "cmc_led_controller.h"
#include "cmc_switch_controller.h"
#include "stm32g4xx_hal.h"

void app_init(void) {
    switch_controller_init();
    led_controller_init();
    button_handler_init();

}

void app_process(void) {
    switch_controller_process();

    // Get button state
    button_handler_process();
    
    // Update LED state (e.g., turn off after blinking)
    led_controller_process();
    
    // Check for button clicks for button 1 to 6 and toggle corresponding switch
    for (uint8_t button_number = 1; button_number <= 6; button_number++) {
        if (is_button_clicked(button_number)) {
            click_event_done(button_number);
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
            led_blink_multiple(button_number, 300, 200);
        }
    }
    
}