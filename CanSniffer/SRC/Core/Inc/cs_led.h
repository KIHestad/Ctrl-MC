#ifndef CS_LED_H
#define CS_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Initialise the LED: ensure it is off at startup.
 *         Call from main.c within the USER CODE BEGIN 2 section.
 */
void cs_led_init(void);

/**
 * @brief  Main-loop LED handler: turns the LED off once the activity
 *         window expires.
 *         Call from main.c within the USER CODE BEGIN 3 section.
 */
void cs_led_process(void);

/**
 * @brief  Blocking startup indicator: blinks the onboard LED three times
 *         (200 ms on / 200 ms off) using HAL_Delay.
 *         Call once from main.c after cs_led_init(), before the main loop.
 */
void cs_led_startup_blink(void);

/**
 * @brief  Signal CAN RX activity: turns the LED on and (re)starts the
 *         50 ms off-timer.
 *         Safe to call from ISR context.
 */
void cs_led_rx_activity(void);

#ifdef __cplusplus
}
#endif

#endif /* CS_LED_H */
