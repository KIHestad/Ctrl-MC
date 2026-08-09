/**
  *********************************************************************************************
  * @file      cmc_util_mcu_driver.c
  * @brief     MCU-level sensor readings (die temperature, VDDA) via internal ADC1 channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_mcu_driver.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"

extern ADC_HandleTypeDef hadc1;

// Samples averaged per temperature/VDDA reading; reduces ADC noise from ±0.5°C to ±0.1°C
#define CMC_ADC_OVERSAMPLE_COUNT    8U
// Empirical calibration offset in tenths of °C applied to every die-temperature reading
#define CMC_MCU_TEMP_OFFSET_DECI_C  50

// Runs one ADC1 regular-sequence scan up to `rank` and returns that rank's value; earlier ranks
// must still be polled in order (hardware sequence), but their values aren't kept
static uint32_t mcu_adc_read_rank(uint8_t rank) {
    uint32_t value = 0U;
    if (HAL_ADC_Start(&hadc1) != HAL_OK) { return 0U; }
    for (uint8_t r = 1U; r <= rank; r++) {
        if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK) {
            value = HAL_ADC_GetValue(&hadc1);
        }
    }
    HAL_ADC_Stop(&hadc1);
    return value;
}

int16_t cmc_util_mcu_read_temp(void) {
    uint32_t ts_acc = 0U;
    uint8_t  rank = cmc_config_hw_tempsensor_adc_rank;
    for (uint8_t i = 0U; i < CMC_ADC_OVERSAMPLE_COUNT; i++) {
        ts_acc += mcu_adc_read_rank(rank);
    }
    uint32_t ts_raw = ts_acc / CMC_ADC_OVERSAMPLE_COUNT;

    int32_t cal_span = (int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR;
    if (cal_span == 0) { return 0; } // guard against corrupted factory calibration
    // Compensate TEMPSENSOR raw to 3.0V-equivalent using live VDDA from the shared MCU driver
    // (equivalent to the standard ts_raw * VREFINT_CAL_ADDR / vref_raw formula, since
    // VDDA = VREFINT_CAL_VREF * VREFINT_CAL_ADDR / vref_raw)
    uint32_t vdda_mv = cmc_util_mcu_read_vdda_mv();
    uint32_t ts_comp = (uint32_t)(((uint64_t)ts_raw * vdda_mv) / VREFINT_CAL_VREF);
    // Multiply by 10 before integer divide to get tenths of °C with reduced truncation error
    int32_t t_deci = ((int32_t)ts_comp - (int32_t)*TEMPSENSOR_CAL1_ADDR)
                     * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP) * 10
                     / cal_span
                     + (int32_t)TEMPSENSOR_CAL1_TEMP * 10;
    return (int16_t)(t_deci + CMC_MCU_TEMP_OFFSET_DECI_C);
}

uint32_t cmc_util_mcu_read_vdda_mv(void) {
    uint32_t vref_acc = 0U;
    uint8_t  rank = cmc_config_hw_vref_adc_rank;
    for (uint8_t i = 0U; i < CMC_ADC_OVERSAMPLE_COUNT; i++) {
        vref_acc += mcu_adc_read_rank(rank);
    }
    uint32_t vref_raw = vref_acc / CMC_ADC_OVERSAMPLE_COUNT;
    if (vref_raw == 0U) { return 3300U; }
    return (uint32_t)(((uint32_t)VREFINT_CAL_VREF * (uint32_t)*VREFINT_CAL_ADDR) / vref_raw);
}
