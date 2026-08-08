/**
  *********************************************************************************************
  * @file      cmc_util_switch_driver.c
  * @brief     Hardware abstraction for Infineon PROFET and SPOC high-side switch channels
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_switch_driver.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"

extern ADC_HandleTypeDef hadc1;

// IS reading below which the PROFET is considered in genuine protection (IIS_FAULT ~5mA → HIGH counts)
// Left for reference; driver no longer uses threshold-based fault inference — see sample_all()
#define PROFET_FAULT_ADC_THRESHOLD  10U

static uint32_t       s_adc_raw[CMC_CONFIG_HW_OUT_COUNT];
static cmc_switch_status_t s_status[CMC_CONFIG_HW_OUT_COUNT];

/* ---- Internal helpers ------------------------------------------------------------------- */

// Returns the highest is_adc_rank across all PROFET channels
static uint8_t profet_max_rank(void) {
    uint8_t max = 0U;
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET && sw->is_adc_rank > max) {
            max = sw->is_adc_rank;
        }
    }
    return max;
}

// Runs one ADC1 scan collecting ranks 1..max_rank into out_ranks[1..max_rank]
static void profet_adc_scan(uint32_t *out_ranks, uint8_t max_rank) {
    if (HAL_ADC_Start(&hadc1) != HAL_OK) { return; }
    for (uint8_t r = 1U; r <= max_rank; r++) {
        if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK) {
            out_ranks[r] = HAL_ADC_GetValue(&hadc1);
        }
    }
    HAL_ADC_Stop(&hadc1);
}

// Converts raw ADC IS reading to load current in mA
static int32_t profet_raw_to_ma(uint32_t raw, uint16_t ilis_ratio, uint16_t ris_ohms) {
    if (ris_ohms == 0U) { return 0; }
    // I_load [mA] = (raw × 3300mV × K_ILIS) / (4095 × R_IS)
    return (int32_t)(((uint64_t)raw * 3300U * ilis_ratio) / ((uint32_t)4095U * ris_ohms));
}

/* ---- Public API -------------------------------------------------------------------------- */

void cmc_util_switch_init(void) {
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
            // Pulse IN low then DEN low→high to clear any latched PROFET fault
            HAL_GPIO_WritePin(sw->in_pin.port,  sw->in_pin.pin,  GPIO_PIN_RESET);
            HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_SET);
        }
        s_adc_raw[ch] = 0U;
        s_status[ch]  = CMC_SWITCH_POWER_GOOD;
    }
}

void cmc_util_switch_set(uint8_t ch, bool on) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
        HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(sw->in_pin.port,  sw->in_pin.pin,  on ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    // SPOC: not yet implemented
}

int8_t cmc_util_switch_set_pwm(uint8_t ch, uint8_t duty_pct) {
    (void)ch; (void)duty_pct;
    return (int8_t)CMC_SWITCH_NOT_SUPPORTED;
}

bool cmc_util_switch_is_on(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return false; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type == CMC_CONFIG_SWITCH_TYPE_PROFET) {
        return HAL_GPIO_ReadPin(sw->in_pin.port, sw->in_pin.pin) == GPIO_PIN_SET;
    }
    return false;
}

void cmc_util_switch_sample_all(void) {
    uint32_t rank_vals[5] = {0U}; // index 1..4 maps to ADC1 scan ranks
    uint8_t  max_rank = profet_max_rank();
    if (max_rank == 0U) { return; }

    bool sampled[CMC_CONFIG_HW_OUT_COUNT] = {false};

    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_PROFET || sampled[ch]) { continue; }

        if (sw->dual_channel) {
            HAL_GPIO_WritePin(sw->dsel_pin.port, sw->dsel_pin.pin, (GPIO_PinState)sw->dsel_value);
        }
        profet_adc_scan(rank_vals, max_rank);

        // Assign this scan's rank results to every channel sharing the same DSEL state
        for (uint8_t j = ch; j < CMC_CONFIG_HW_OUT_COUNT; j++) {
            const cmc_config_switch_t *swj = &cmc_config_hw_out_channel_mapping[j];
            if (swj->switch_type != CMC_CONFIG_SWITCH_TYPE_PROFET || sampled[j]) { continue; }

            // Single-channel entries (no DSEL) are readable from any scan pass
            bool same_state = !swj->dual_channel ||
                              (swj->dsel_pin.port == sw->dsel_pin.port &&
                               swj->dsel_pin.pin  == sw->dsel_pin.pin  &&
                               swj->dsel_value    == sw->dsel_value);
            if (same_state) {
                s_adc_raw[j] = rank_vals[swj->is_adc_rank];
                sampled[j]   = true;
            }
        }
    }

    // Infer fault state from cached IS readings
    // Note: genuine PROFET protection outputs IIS(FAULT) ~5mA (HIGH IS), not zero.
    // Low IS simply means low load (LED etc.) — handled by feature-level open_load_ma.
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_PROFET) { continue; }
        s_status[ch] = CMC_SWITCH_POWER_GOOD;
    }
}

int32_t cmc_util_switch_read_current_ma(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return 0; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_PROFET) {
        return CMC_SWITCH_NOT_SUPPORTED;
    }
    if (!cmc_util_switch_is_on(ch)) { return 0; }
    return profet_raw_to_ma(s_adc_raw[ch], sw->ilis_ratio, sw->ris_ohms);
}

int16_t cmc_util_switch_read_mcu_temp_c(void) {
    uint32_t rank_vals[5] = {0U};
    profet_adc_scan(rank_vals, 4U);  // rank 3 = TEMPSENSOR, rank 4 = VREFINT
    int32_t cal_span = (int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR;
    if (cal_span == 0) { return 0; } // guard against corrupted factory calibration
    // Compensate TEMPSENSOR raw to 3.0V-equivalent using live VDDA measurement
    uint32_t vref_raw = rank_vals[4];
    uint32_t ts_comp  = (vref_raw > 0U)
                        ? (uint32_t)(((uint64_t)rank_vals[3] * *VREFINT_CAL_ADDR) / vref_raw)
                        : ((uint32_t)rank_vals[3] * 33U + 15U) / 30U;
    int32_t t = ((int32_t)ts_comp - (int32_t)*TEMPSENSOR_CAL1_ADDR)
                * (TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)
                / cal_span
                + TEMPSENSOR_CAL1_TEMP;
    return (int16_t)t;
}

cmc_switch_status_t cmc_util_switch_get_status(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return CMC_SWITCH_FAULT_OVERCURRENT; }
    return s_status[ch];
}
