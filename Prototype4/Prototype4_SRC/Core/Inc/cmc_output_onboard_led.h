#ifndef CMC_OUTPUT_ONBOARD_LED_H
#define CMC_OUTPUT_ONBOARD_LED_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void cmc_output_onboard_led_init(void);
void cmc_output_onboard_led_blink_once(uint32_t duration_ms);
void cmc_output_onboard_led_blink_multiple(uint32_t numOfBlinks, uint32_t duration_on_ms, uint32_t duration_off_ms);
void cmc_output_onboard_led_process(void);

#endif /* CMC_OUTPUT_ONBOARD_LED_H */