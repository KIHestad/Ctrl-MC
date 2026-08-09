/**
  *********************************************************************************************
  * @file      cmc_util_mcu_driver.c
  * @brief     MCU-level sensor readings (die temperature, VDDA) via internal ADC1 channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_mcu_driver.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"

extern ADC_HandleTypeDef hadc1;

// Samples averaged per temperature/VDDA reading; reduces ADC noise from ±0.5°C to ±0.1°C
#define CMC_ADC_OVERSAMPLE_COUNT    8U
// Empirical calibration offset in tenths of °C applied to every die-temperature reading
#define CMC_MCU_TEMP_OFFSET_DECI_C  50

// Runs one ADC1 scan collecting ranks 1..max_rank into out_ranks[1..max_rank]
static void mcu_adc_scan(uint32_t *out_ranks, uint8_t max_rank) {
    if (HAL_ADC_Start(&hadc1) != HAL_OK) { return; }
    for (uint8_t r = 1U; r <= max_rank; r++) {
        if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK) {
            out_ranks[r] = HAL_ADC_GetValue(&hadc1);
        }
    }
    HAL_ADC_Stop(&hadc1);
}

int16_t cmc_util_mcu_read_temp(void) {
    uint32_t ts_acc = 0U, vref_acc = 0U;
    for (uint8_t i = 0U; i < CMC_ADC_OVERSAMPLE_COUNT; i++) {
        uint32_t rank_vals[5] = {0U};
        mcu_adc_scan(rank_vals, 4U);  // rank 3 = TEMPSENSOR, rank 4 = VREFINT
        ts_acc   += rank_vals[3];
        vref_acc += rank_vals[4];
    }
    uint32_t ts_raw   = ts_acc   / CMC_ADC_OVERSAMPLE_COUNT;
    uint32_t vref_raw = vref_acc / CMC_ADC_OVERSAMPLE_COUNT;

    int32_t cal_span = (int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR;
    if (cal_span == 0) { return 0; } // guard against corrupted factory calibration
    // Compensate TEMPSENSOR raw to 3.0V-equivalent using live VDDA measurement
    uint32_t ts_comp  = (vref_raw > 0U)
                        ? (uint32_t)(((uint64_t)ts_raw * *VREFINT_CAL_ADDR) / vref_raw)
                        : ((uint32_t)ts_raw * 33U + 15U) / 30U;
    // Multiply by 10 before integer divide to get tenths of °C with reduced truncation error
    int32_t t_deci = ((int32_t)ts_comp - (int32_t)*TEMPSENSOR_CAL1_ADDR)
                     * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP) * 10
                     / cal_span
                     + (int32_t)TEMPSENSOR_CAL1_TEMP * 10;
    return (int16_t)(t_deci + CMC_MCU_TEMP_OFFSET_DECI_C);
}

uint32_t cmc_util_mcu_read_vdda_mv(void) {
    uint32_t vref_acc = 0U;
    for (uint8_t i = 0U; i < CMC_ADC_OVERSAMPLE_COUNT; i++) {
        uint32_t rank_vals[5] = {0U};
        mcu_adc_scan(rank_vals, 4U);  // rank 4 = VREFINT
        vref_acc += rank_vals[4];
    }
    uint32_t vref_raw = vref_acc / CMC_ADC_OVERSAMPLE_COUNT;
    if (vref_raw == 0U) { return 3300U; }
    return (uint32_t)(((uint32_t)VREFINT_CAL_VREF * (uint32_t)*VREFINT_CAL_ADDR) / vref_raw);
}
