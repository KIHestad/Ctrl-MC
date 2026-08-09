/**
  *********************************************************************************************
  * @file      cmc_util_switch_spoc_driver.c
  * @brief     Infineon SPOC (BTS72220-4ESA) high-side switch channel implementation (SPI daisy chain)
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  *
  * 2x BTS72220-4ESA daisy-chained on SPI1 (shared CSN, shared analog IS pin), 4 channels each.
  * Every SPI access shifts one 8-bit frame per chip (2 bytes total) and the response to a
  * command only arrives with the NEXT transaction (see datasheet Chapter 10.5) — callers below
  * account for this one-transaction pipeline delay explicitly.
  * HWCR/OCR/KRC/RCD configuration registers are left at power-on defaults: IN0-3 are hardwired
  * low on this board, so the default HWCR.COL=0 (OR-combination) lets the SPI OUT bit alone
  * control each channel. Checksum verification (ICS) is not used.
  */

#include "util/cmc_util_switch_spoc_driver.h"
#include "util/cmc_util_mcu_driver.h"
#include "config/cmc_config_hw_mapping.h"
#include "stm32g4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern ADC_HandleTypeDef hadc1;

#define CMC_SPOC_CHIP_COUNT    2U
#define CMC_SPOC_CH_PER_CHIP   4U
#define CMC_SPOC_MUX_DISABLED  0x07U // DCR.MUX = 111B blanks the current-sense mux (Hi-Z on IS)

// Set to true if chip index 0 (global channels 0-3) is the chip whose SO drives MISO directly
// (i.e. is "far" from the MCU in the daisy chain, so its command occupies the FIRST transmitted
// byte). Datasheet Fig. 37/38 confirm the byte-order rule (shift register chains MOSI->dev1->
// dev2->MISO). Per the dev-board schematic: STM32_MOSI->IC1.SI, IC1.SO->IC2.SI, IC2.SO->MISO,
// and IC1 drives J2.OUT1-4 (channels 0-3) while IC2 drives J2.OUT5-8 (channels 4-7) — so chip
// index 0 = IC1 = the near-MOSI chip, NOT the SO->MISO one, confirming false here. Still worth
// a bring-up smoke test (toggle one channel, verify the right physical output reacts).
static const bool s_chip0_is_far = false;

static uint8_t  s_out_mask[CMC_SPOC_CHIP_COUNT];              // shadow of commanded OUT bits per chip
static uint32_t s_is_raw[CMC_CONFIG_HW_OUT_COUNT];            // cached raw IS ADC counts per global channel
static uint32_t s_vdda_mv = 3300U;                            // refreshed once per sample_all() call
static bool     s_fault_latched[CMC_CONFIG_HW_OUT_COUNT];    // per-channel ERRDIAG latch, from last sample_all()
static uint32_t s_csn_high_cycle;                             // DWT->CYCCNT snapshot from CSN's last rising edge

// Returns true if any output channel is configured as SPOC; mirrors the PROFET driver's
// profet_max_rank()==0 guard so sample_all() is a no-op on a hypothetical SPOC-less board.
static bool spoc_any_channel_configured(void) {
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        if (cmc_config_hw_out_channel_mapping[ch].switch_type == CMC_CONFIG_SWITCH_TYPE_SPOC) { return true; }
    }
    return false;
}

/* ---- SPI command byte builders (datasheet Table 32) ------------------------------------- */

static uint8_t build_out_write(uint8_t mask4) {
    return (uint8_t)(0x80U | (mask4 & 0x0FU)); // 100xdddd
}
static uint8_t build_dcr_write(uint8_t mux3) {
    return (uint8_t)(0xF0U | (mux3 & 0x07U)); // 1111 s(0) mmm, SWR bit left 0 (no swap)
}
static uint8_t build_read_wrndiag(void) { return 0x01U; } // 0xxxx001
static uint8_t build_read_errdiag(void) { return 0x03U; } // 0xxxx011
static uint8_t build_read_out(void) { return 0x00U; } // 0xxxaaaa, aaaa=0000 (OUT register address)

// HWCR write: SWR=0, RB=1, ADDR0=10, bit3=0(reserved), COL=0 (keep OR-combination with the
// hardwired-low IN pins), RST=0 (must stay 0 — that bit issues a full device reset), CLC=1
// (clears restart counters AND un-latches every channel on that chip — datasheet Table 39)
static uint8_t build_hwcr_clear_latches(void) { return 0x71U; } // 0111 0001

/* ---- Low-level daisy-chain transfer ------------------------------------------------------ */

// One 2-byte full-duplex transaction; resp0/resp1 are the response to the PREVIOUS transaction
static void spoc_xfer(uint8_t chip0_cmd, uint8_t chip1_cmd, uint8_t *chip0_resp, uint8_t *chip1_resp) {
    // Enforce tCSN(TD) >= 500ns (datasheet P_10.4.0.3) between frames, regardless of how little
    // work the caller does between spoc_xfer() calls or how the compiler optimizes it.
    uint32_t min_cycles = SystemCoreClock / 2000000U;
    while ((DWT->CYCCNT - s_csn_high_cycle) < min_cycles) { }

    uint8_t tx[2];
    uint8_t rx[2] = {0U, 0U};
    if (s_chip0_is_far) { tx[0] = chip0_cmd; tx[1] = chip1_cmd; }
    else                { tx[0] = chip1_cmd; tx[1] = chip0_cmd; }

    HAL_GPIO_WritePin(cmc_config_hw_spoc_cs_pin.port, cmc_config_hw_spoc_cs_pin.pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2U, 10U);
    HAL_GPIO_WritePin(cmc_config_hw_spoc_cs_pin.port, cmc_config_hw_spoc_cs_pin.pin, GPIO_PIN_SET);
    s_csn_high_cycle = DWT->CYCCNT;

    if (s_chip0_is_far) { *chip0_resp = rx[0]; *chip1_resp = rx[1]; }
    else                { *chip0_resp = rx[1]; *chip1_resp = rx[0]; }
}

// Microsecond busy-wait for current-sense mux settling (tsIS(CC), max 60us per datasheet), timed
// against the DWT cycle counter rather than a NOP loop so it's exact regardless of optimization level.
static void spoc_delay_us(uint32_t us) {
    uint32_t start  = DWT->CYCCNT;
    uint32_t cycles = (SystemCoreClock / 1000000U) * us;
    while ((DWT->CYCCNT - start) < cycles) { }
}

// Reads the IS pin (rank from cmc_config_hw_spoc_is_adc_rank), stopping before later ranks convert
static uint32_t spoc_read_is_raw(void) {
    uint32_t raw = 0U;
    if (HAL_ADC_Start(&hadc1) == HAL_OK) {
        for (uint8_t r = 1U; r <= cmc_config_hw_spoc_is_adc_rank; r++) {
            if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK) {
                raw = HAL_ADC_GetValue(&hadc1);
            }
        }
        HAL_ADC_Stop(&hadc1);
    }
    return raw;
}

// Converts raw IS ADC reading to load current in mA using live VDDA (same math as PROFET)
static int32_t spoc_raw_to_ma(uint32_t raw, uint16_t ilis_ratio, uint16_t ris_ohms, uint32_t vdda_mv) {
    if (ris_ohms == 0U) { return 0; }
    return (int32_t)(((uint64_t)raw * vdda_mv * ilis_ratio) / ((uint32_t)4095U * ris_ohms));
}

/* ---- Public API -------------------------------------------------------------------------- */

void cmc_util_switch_spoc_init(void) {
    // Enable the DWT cycle counter once, used by spoc_delay_us() and spoc_xfer()'s tCSN(TD) wait
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0U;
    DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;

    s_out_mask[0] = 0U;
    s_out_mask[1] = 0U;
    uint8_t discard0, discard1;
    // Clear any restart-counter latch left over from a previous session (e.g. a channel that
    // tripped and latched OFF) before commanding outputs, mirroring the PROFET driver's
    // boot-time fault clear. Sent twice: pipeline delay means the first ack only arrives on
    // the second transaction.
    spoc_xfer(build_hwcr_clear_latches(), build_hwcr_clear_latches(), &discard0, &discard1);
    spoc_xfer(build_hwcr_clear_latches(), build_hwcr_clear_latches(), &discard0, &discard1);
    // Send twice: pipeline delay means the first transaction's ack only arrives on the second
    spoc_xfer(build_out_write(0U), build_out_write(0U), &discard0, &discard1);
    spoc_xfer(build_out_write(0U), build_out_write(0U), &discard0, &discard1);
    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        s_is_raw[ch] = 0U;
        s_fault_latched[ch] = false;
    }
}

void cmc_util_switch_spoc_set(uint8_t ch, bool on) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
    uint8_t bit  = sw->spoc_channel % CMC_SPOC_CH_PER_CHIP;
    uint8_t discard0, discard1;

    // Re-arm on every OFF->ON request for a channel last reported latched off (HWCR.CLC=1
    // resets restart counters/latches for all 4 channels on that chip, per datasheet, but only
    // ever un-latches ones actually tripped — harmless to already-healthy channels on the chip).
    // This is what lets the user clear a fault simply by cycling the switch off then on again,
    // e.g. after replacing a shorted bulb, without needing an MCU reboot.
    if (on && s_fault_latched[ch]) {
        uint8_t clc0 = (chip == 0U) ? build_hwcr_clear_latches() : build_read_wrndiag();
        uint8_t clc1 = (chip == 1U) ? build_hwcr_clear_latches() : build_read_wrndiag();
        spoc_xfer(clc0, clc1, &discard0, &discard1);
        s_fault_latched[ch] = false;
    }

    if (on) { s_out_mask[chip] |= (uint8_t)(1U << bit); }
    else    { s_out_mask[chip] &= (uint8_t)~(1U << bit); }

    spoc_xfer(build_out_write(s_out_mask[0]), build_out_write(s_out_mask[1]), &discard0, &discard1);
    // Flush the pending STDDIAG/WRNDIAG ack so it doesn't leak into the next unrelated transfer
    spoc_xfer(build_read_wrndiag(), build_read_wrndiag(), &discard0, &discard1);
}

// Returns the last commanded on/off state, reconciled against real hardware once per
// sample_all() cycle (see there) rather than a live SPI read on every call — unlike PROFET's
// free/instant GPIO readback, an SPI register read costs a transaction plus a one-cycle
// pipeline delay, so it isn't done synchronously on every is_on() call.
bool cmc_util_switch_spoc_is_on(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return false; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
    uint8_t bit  = sw->spoc_channel % CMC_SPOC_CH_PER_CHIP;
    return (s_out_mask[chip] & (uint8_t)(1U << bit)) != 0U;
}

void cmc_util_switch_spoc_sample_all(cmc_switch_status_t *status) {
    if (!spoc_any_channel_configured()) { return; }

    uint8_t wrndiag[CMC_SPOC_CHIP_COUNT];
    uint8_t errdiag[CMC_SPOC_CHIP_COUNT];
    uint8_t discard0, discard1;

    // Fault registers are independent of DCR.MUX — one read pair covers all 4 channels per chip.
    // Response is one transaction behind, so the 3rd transfer below is what returns ERRDIAG.
    spoc_xfer(build_read_wrndiag(), build_read_wrndiag(), &discard0, &discard1); // discard stale ack
    spoc_xfer(build_read_errdiag(), build_read_errdiag(), &wrndiag[0], &wrndiag[1]);
    spoc_xfer(build_dcr_write(0U), build_dcr_write(CMC_SPOC_MUX_DISABLED), &errdiag[0], &errdiag[1]);

    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_SPOC) { continue; }
        uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
        uint8_t bit  = sw->spoc_channel % CMC_SPOC_CH_PER_CHIP;
        bool err_latched = (errdiag[chip] & (uint8_t)(1U << bit)) != 0U;
        bool warn_set    = (wrndiag[chip] & (uint8_t)(1U << bit)) != 0U;
        s_fault_latched[ch] = err_latched;
        // Only a latched ERRDIAG bit is a hard fault; a WRNDIAG-only bit (e.g. inrush) is
        // reported as a non-latched warning rather than discarded.
        status[ch] = err_latched ? CMC_SWITCH_FAULT_OVERCURRENT
                   : warn_set    ? CMC_SWITCH_WARNING_OVERLOAD
                   :               CMC_SWITCH_POWER_GOOD;
    }

    // Round-robin all 8 channels' current-sense mux; each chip gets its target channel or
    // CMC_SPOC_MUX_DISABLED (blanked) so only one channel drives the shared IS pin at a time.
    for (uint8_t g = 0U; g < CMC_CONFIG_HW_OUT_COUNT; g++) {
        uint8_t target_chip = g / CMC_SPOC_CH_PER_CHIP;
        uint8_t target_bit  = g % CMC_SPOC_CH_PER_CHIP;
        uint8_t chip0_mux = (target_chip == 0U) ? target_bit : CMC_SPOC_MUX_DISABLED;
        uint8_t chip1_mux = (target_chip == 1U) ? target_bit : CMC_SPOC_MUX_DISABLED;
        spoc_xfer(build_dcr_write(chip0_mux), build_dcr_write(chip1_mux), &discard0, &discard1);
        spoc_delay_us(60U); // tsIS(CC) max settle time after a mux channel change
        s_is_raw[g] = spoc_read_is_raw();
    }

    // Park the mux disabled (both chips) until the next sample_all() call
    spoc_xfer(build_dcr_write(CMC_SPOC_MUX_DISABLED), build_dcr_write(CMC_SPOC_MUX_DISABLED), &discard0, &discard1);

    // Reconcile our commanded shadow against the actual OUT register: a chip-side reset (e.g. a
    // brief VDD undervoltage event, STDDIAG.VSMON) reverts OUT to defaults without telling the
    // MCU directly, so without this is_on() would keep reporting a channel as "on" after such
    // an event until the next explicit set() call.
    uint8_t out_resp0, out_resp1;
    spoc_xfer(build_read_out(), build_read_out(), &discard0, &discard1);   // discard park's ack
    spoc_xfer(build_read_out(), build_read_out(), &out_resp0, &out_resp1); // = actual OUT register content
    s_out_mask[0] = out_resp0 & 0x0FU;
    s_out_mask[1] = out_resp1 & 0x0FU;

    s_vdda_mv = cmc_util_mcu_read_vdda_mv();
}

int32_t cmc_util_switch_spoc_read_current_ma(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return 0; }
    if (!cmc_util_switch_spoc_is_on(ch)) { return 0; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    return spoc_raw_to_ma(s_is_raw[ch], sw->ilis_ratio, sw->ris_ohms, s_vdda_mv);
}
