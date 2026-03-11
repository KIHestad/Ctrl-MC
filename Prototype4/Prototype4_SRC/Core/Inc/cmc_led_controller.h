#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void led_controller_init(void);
void led_blink_once(uint32_t duration_ms);
void led_blink_multiple(uint32_t numOfBlinks, uint32_t duration_on_ms, uint32_t duration_off_ms);
void led_controller_process(void);

#endif /* LED_CONTROLLER_H */