#ifndef CMC_INPUT_PIN_H
#define CMC_INPUT_PIN_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#define NUM_BUTTONS 10
#define DEBOUNCE_DELAY_MS 50

void cmc_input_pin_init(void);
void cmc_input_pin_handler(void);

// Returns true if the button has a pending click event
bool cmc_input_pin_button_clicked(uint8_t button_number);

// Clears the pending click event
void cmc_input_pin_click_event_done(uint8_t button_number);

#endif /* CMC_INPUT_PIN_H */