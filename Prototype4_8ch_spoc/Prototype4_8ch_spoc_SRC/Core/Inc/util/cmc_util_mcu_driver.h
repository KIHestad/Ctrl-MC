/**
  *********************************************************************************************
  * @file      cmc_util_mcu_driver.h
  * @brief     MCU-level sensor readings (die temperature, VDDA) via internal ADC1 channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_MCU_DRIVER_H_
#define CMC_UTIL_MCU_DRIVER_H_

#include <stdint.h>

// Triggers a fresh ADC1 scan (TEMPSENSOR + VREFINT), returns MCU die temperature in tenths of °C (e.g. 286 = 28.6°C)
int16_t  cmc_util_mcu_read_temp(void);

// Triggers a fresh ADC1 scan (VREFINT), returns VDDA in mV computed via VREFINT calibration
uint32_t cmc_util_mcu_read_vdda_mv(void);

#endif /* CMC_UTIL_MCU_DRIVER_H_ */
