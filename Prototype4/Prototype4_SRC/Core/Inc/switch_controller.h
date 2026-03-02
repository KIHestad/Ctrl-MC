#ifndef SWITCH_CONTROLLER_H
#define SWITCH_CONTROLLER_H

#include "main.h"
#include <stdbool.h>

// Initialization (Turns off all switches and diagnostics)
void switch_controller_init(void);

// Power Control
void switch_turn_on(uint8_t channel);
void switch_turn_on_blink(uint8_t channel);
void switch_turn_off(uint8_t channel);
void switch_toggle(uint8_t channel);
bool is_button_off(uint8_t channel);
void switch_controller_process(void);

// Diagnostic Control (Current Sense via IS pin)
// Handles the DEN (Diagnostic Enable) and DSEL (Diagnostic Select) pins
void switch_enable_diagnostic(uint8_t channel);
void switch_disable_all_diagnostics(void);

#endif /* SWITCH_CONTROLLER_H */