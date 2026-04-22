#ifndef cmc_onboard_LED_H
#define cmc_onboard_LED_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void cmc_onboard_led_init(void);
void cmc_onboard_led_blink_once(uint32_t duration_ms);
void cmc_onboard_led_blink_multiple(uint32_t numOfBlinks, uint32_t duration_on_ms, uint32_t duration_off_ms);
void cmc_onboard_led_process(void);

#endif /* cmc_onboard_LED_H */