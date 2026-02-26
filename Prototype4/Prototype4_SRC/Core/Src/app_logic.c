#include "app_logic.h"
#include "button_handler.h"
#include "led_controller.h"
#include "stm32g4xx_hal.h"
#include "switch_controller.h"

void app_init(void) {
    switch_controller_init();
    led_controller_init();
    button_handler_init();

}

void app_process(void) {
    // Get button state
    button_handler_process();
    
    // Update LED state (e.g., turn off after blinking)
    led_controller_process();
    
    // Check for button clicks for button 1 to 6 and toggle corresponding switch
    for (uint8_t button_number = 1; button_number <= 6; button_number++) {
        if (is_button_clicked(button_number)) {
            click_event_done(button_number);
            switch_toggle(button_number);
            led_blink_multiple(button_number, 300, 200);
        }
    }
    
}