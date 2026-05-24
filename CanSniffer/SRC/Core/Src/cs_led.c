#include "cs_led.h"
#include "main.h"

/* --------------------------------------------------------------------------
 * Private state
 * -------------------------------------------------------------------------- */

/** Tick value at which the activity LED should be turned off (0 = inactive). */
static volatile uint32_t cs_led_off_tick = 0U;

/* --------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

void cs_led_init(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}

void cs_led_process(void)
{
    if ((cs_led_off_tick != 0U) && (HAL_GetTick() >= cs_led_off_tick))
    {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        cs_led_off_tick = 0U;
    }
}

void cs_led_startup_blink(void)
{
    for (uint8_t i = 0U; i < 3U; i++)
    {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        HAL_Delay(200U);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        HAL_Delay(200U);
    }
}

void cs_led_rx_activity(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    cs_led_off_tick = HAL_GetTick() + 50U;
}
