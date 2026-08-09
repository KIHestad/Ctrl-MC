/**
  *********************************************************************************************
  * @file      cmc_util_switch_driver.h
  * @brief     Hardware abstraction for Infineon PROFET and SPOC high-side switch channels.
  *            Separates hardware protocol (GPIO+ADC for PROFET, SPI for SPOC) from feature logic.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_SWITCH_DRIVER_H_
#define CMC_UTIL_SWITCH_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

// Returned by set_pwm when the channel type does not support PWM
#define CMC_SWITCH_NOT_SUPPORTED   (-1)

typedef enum {
    CMC_SWITCH_POWER_GOOD        = 0, // Normal operation
    CMC_SWITCH_FAULT_OPEN_LOAD   = 1, // Open circuit
    CMC_SWITCH_FAULT_OVERCURRENT = 2, // Overload or hard short to GND (channel tripped/latched)
    CMC_SWITCH_FAULT_OVERTEMP    = 3, // Thermal protection triggered
    CMC_SWITCH_FAULT_SHORT_VS    = 4  // Output shorted to +12V battery rail
} cmc_switch_status_t;

// Initialises all switch channels; clears PROFET fault latches via DEN pulse
void               cmc_util_switch_init(void);

// Drives a logical output channel on or off
void               cmc_util_switch_set(uint8_t ch, bool on);

// Sets PWM duty 0–100 % on channels that support it; returns CMC_SWITCH_NOT_SUPPORTED for PROFET
int8_t             cmc_util_switch_set_pwm(uint8_t ch, uint8_t duty_pct);

// Returns true if the channel is currently driven on
bool               cmc_util_switch_is_on(uint8_t ch);

// Samples all PROFET IS pins in two ADC passes (DSEL low then high) and caches results.
// Call once per measurement cycle before calling read_current_ma or get_status.
void               cmc_util_switch_sample_all(void);

// Returns cached load current in mA from the last sample_all() call; 0 when switch is off
int32_t            cmc_util_switch_read_current_ma(uint8_t ch);

// Triggers a fresh ADC1 scan (ranks 1-4), returns MCU die temperature in tenths of °C (e.g. 286 = 28.6°C)
int16_t            cmc_util_switch_read_mcu_temp_c(void);

// Triggers a fresh ADC1 scan (rank 4), returns VDDA in mV computed via VREFINT calibration
uint32_t           cmc_util_switch_read_vdda_mv(void);

// Returns the channel status inferred during the last sample_all() call
cmc_switch_status_t cmc_util_switch_get_status(uint8_t ch);

#endif /* CMC_UTIL_SWITCH_DRIVER_H_ */
