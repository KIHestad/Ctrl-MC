/**
  *********************************************************************************************
  * @file      cmc_util_switch_profet_driver.c
  * @brief     Infineon PROFET high-side switch channel implementation (GPIO + ADC IS pin)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_switch_profet_driver.h"
#include "util/cmc_util_mcu_driver.h"
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"

extern ADC_HandleTypeDef hadc1;

// IS reading below which the PROFET is considered in genuine protection (IIS_FAULT ~5mA → HIGH counts)
// Left for reference; driver no longer uses threshold-based fault inference — see sample_all()
#define PROFET_FAULT_ADC_THRESHOLD  10U

static uint32_t s_adc_raw[CMC_CONFIG_HW_OUT_COUNT];
static uint32_t s_vdda_mv = 3300U; // updated each sample_all() from VREFINT for accurate current calc

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

// Converts raw ADC IS reading to load current in mA using live VDDA
static int32_t profet_raw_to_ma(uint32_t raw, uint16_t ilis_ratio, uint16_t ris_ohms, uint32_t vdda_mv) {
    if (ris_ohms == 0U) { return 0; }
    // I_load [mA] = (raw × VDDA[mV] × K_ILIS) / (4095 × R_IS)
    return (int32_t)(((uint64_t)raw * vdda_mv * ilis_ratio) / ((uint32_t)4095U * ris_ohms));
}

// One calibration point: below current_ma, factor_x1000/1000 scales the raw reading up
typedef struct {
    uint16_t current_ma;
    uint16_t factor_x1000;
} profet_comp_point_t;

// BTS7020-2EPA (5A dual channel) current-sense reads increasingly low across the whole range;
// measured vs PSU-ammeter-true current with 5W/21W bulbs and a power resistor load, 2026-08-08.
static const profet_comp_point_t s_profet5a_comp_table[] = {
    {  302, 1524 },
    {  738, 1193 },
    { 1576, 1072 },
    { 2010, 1039 },
    { 2871, 1038 }, // approx 50% load
    { 4000, 1000 }  // approx 80% load
};

// BTS7004-1EPP (15A single channel) current-sense reads increasingly low below ~2A raw; measured
// vs PSU-ammeter-true current with bulb/resistor loads, 2026-08-08. Below 335 mA raw (~1.3A true)
// the reading is buried in noise (same range flagged by open_load_ma), so no point is calibrated there.
static const profet_comp_point_t s_profet15a_comp_table[] = {
    {  335, 4000 },
    {  738, 2332 },
    { 1173, 1790 },
    { 2096, 1413 },
    { 5000, 1200 }, // approx 33% load
    { 10000, 1000 } // approx 66% load
    
};

#define PROFET_COMP_TABLE_COUNT(table) (uint8_t)(sizeof(table) / sizeof((table)[0]))

// Piecewise-linear interpolation over a calibration table; extrapolates using the nearest end point's factor
static int32_t compensate_profet_ma(int32_t raw_ma, const profet_comp_point_t *table, uint8_t count) {
    if (raw_ma <= 0 || count == 0U) { return raw_ma; }
    if (raw_ma <= (int32_t)table[0].current_ma) {
        return (int32_t)(((int64_t)raw_ma * table[0].factor_x1000) / 1000);
    }
    for (uint8_t i = 1U; i < count; i++) {
        if (raw_ma <= (int32_t)table[i].current_ma) {
            int32_t i0 = table[i - 1U].current_ma;
            int32_t i1 = table[i].current_ma;
            int32_t f0 = table[i - 1U].factor_x1000;
            int32_t f1 = table[i].factor_x1000;
            int32_t factor = f0 + (int32_t)(((int64_t)(f1 - f0) * (raw_ma - i0)) / (i1 - i0));
            return (int32_t)(((int64_t)raw_ma * factor) / 1000);
        }
    }
    // above highest calibrated point: extrapolate using its factor
    return (int32_t)(((int64_t)raw_ma * table[count - 1U].factor_x1000) / 1000);
}

/* ---- Internal API (called only from cmc_util_switch_driver.c) --------------------------- */

void cmc_util_switch_profet_init(void) {
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_PROFET) { continue; }
        // Pulse IN low then DEN low→high to clear any latched PROFET fault
        HAL_GPIO_WritePin(sw->in_pin.port,  sw->in_pin.pin,  GPIO_PIN_RESET);
        HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_SET);
        s_adc_raw[ch] = 0U;
    }
}

void cmc_util_switch_profet_set(uint8_t ch, bool on) {
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    HAL_GPIO_WritePin(sw->den_pin.port, sw->den_pin.pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(sw->in_pin.port,  sw->in_pin.pin,  on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

bool cmc_util_switch_profet_is_on(uint8_t ch) {
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    return HAL_GPIO_ReadPin(sw->in_pin.port, sw->in_pin.pin) == GPIO_PIN_SET;
}

void cmc_util_switch_profet_sample_all(cmc_switch_status_t *status) {
    uint32_t rank_vals[5] = {0U}; // index 1..max_rank maps to ADC1 scan ranks
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
        status[ch] = CMC_SWITCH_POWER_GOOD;
    }

    // VDDA comes from the shared MCU driver rather than a hardcoded rank here — the ADC1 scan
    // layout (which rank is VREFINT) is board-specific and not a PROFET driver concern.
    s_vdda_mv = cmc_util_mcu_read_vdda_mv();
}

int32_t cmc_util_switch_profet_read_current_ma(uint8_t ch) {
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    if (!cmc_util_switch_profet_is_on(ch)) { return 0; }
    int32_t raw_ma = profet_raw_to_ma(s_adc_raw[ch], sw->ilis_ratio, sw->ris_ohms, s_vdda_mv);
    if (!cmc_config.feature_channel_info.compensation_enabled) { return raw_ma; }
    return sw->dual_channel
        ? compensate_profet_ma(raw_ma, s_profet5a_comp_table, PROFET_COMP_TABLE_COUNT(s_profet5a_comp_table))
        : compensate_profet_ma(raw_ma, s_profet15a_comp_table, PROFET_COMP_TABLE_COUNT(s_profet15a_comp_table));
}
