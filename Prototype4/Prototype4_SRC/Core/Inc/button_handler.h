#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#define NUM_BUTTONS 10
#define DEBOUNCE_DELAY_MS 50

void button_handler_init(void);
void button_handler_process(void);

// Returns true if the button has a pending click event
bool is_button_clicked(uint8_t button_number);

// Clears the pending click event
void click_event_done(uint8_t button_number);

#endif /* BUTTON_HANDLER_H */