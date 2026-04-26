/**
 *********************************************************************************************
 * @file      cmc_util_onboard_led.h
 * @brief     Onboard LED control for status indication
 * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
 * @copyright KI Hestad, Complicated Productions
 *********************************************************************************************
 */

#ifndef CMC_UTIL_ONBOARD_LED_H_
#define CMC_UTIL_ONBOARD_LED_H_

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void cmc_onboard_led_init(void);
void cmc_onboard_led_startup(void);
void cmc_onboard_led_normal_operation(void);
void cmc_onboard_led_blink(uint32_t duration_on_ms, uint32_t duration_off_ms);
void cmc_onboard_led_blink_once(uint32_t duration_ms);
void cmc_onboard_led_blink_multiple(uint32_t num_of_blinks, uint32_t duration_on_ms, uint32_t duration_off_ms);
void cmc_onboard_led_blink_error(uint32_t num_of_error_blinks);
void cmc_onboard_led_process(void);

#endif /* CMC_UTIL_ONBOARD_LED_H_ */