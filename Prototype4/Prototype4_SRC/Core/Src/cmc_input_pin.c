#include "cmc_input_pin.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    GPIO_PinState last_read_state;
    bool is_pressed;
    uint32_t last_debounce_time;
    bool click_event_pending;
} button_t;

// Map the buttons 1-10 to array indices 0-9 based on your main.h
static button_t buttons[NUM_BUTTONS] = {
    {BTN_1_GPIO_Port, BTN_1_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_2_GPIO_Port, BTN_2_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_3_GPIO_Port, BTN_3_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_4_GPIO_Port, BTN_4_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_5_GPIO_Port, BTN_5_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_6_GPIO_Port, BTN_6_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_7_GPIO_Port, BTN_7_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_8_GPIO_Port, BTN_8_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_9_GPIO_Port, BTN_9_Pin, GPIO_PIN_SET, false, 0, false},
    {BTN_10_GPIO_Port, BTN_10_Pin, GPIO_PIN_SET, false, 0, false}
};

void cmc_input_pin_init(void) {
    // Initialization handled by struct definition, code for reinitialize button state at runtime can be added here if needed
}

void cmc_input_pin_handler(void) {
    uint32_t current_time = HAL_GetTick();

    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        GPIO_PinState current_read = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

        // If the switch state changed due to noise or pressing
        if (current_read != buttons[i].last_read_state) {
            buttons[i].last_debounce_time = current_time; // Reset debounce timer
        }

        // If the state has been stable for longer than the debounce delay
        if ((current_time - buttons[i].last_debounce_time) > DEBOUNCE_DELAY_MS) {
            
            // Because buttons are PULL-UP, reading RESET means pressed
            bool is_pressed_now = (current_read == GPIO_PIN_RESET);

            if (is_pressed_now && !buttons[i].is_pressed) {
                // Rising edge of the button press detected
                buttons[i].click_event_pending = true; 
            }
            
            buttons[i].is_pressed = is_pressed_now;
        }

        buttons[i].last_read_state = current_read;
    }
}

bool cmc_input_pin_button_clicked(uint8_t button_number) {
    if (button_number < 1 || button_number > NUM_BUTTONS) return false;
    return buttons[button_number - 1].click_event_pending;
}

void cmc_input_pin_click_event_done(uint8_t button_number) {
    if (button_number >= 1 && button_number <= NUM_BUTTONS) {
        buttons[button_number - 1].click_event_pending = false;
    }
}