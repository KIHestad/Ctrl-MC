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
#define CMC_SPOC_STALE_MS      5000U // max time a reading may go unrefreshed before forcing a sample anyway
// tsIS(CC) datasheet max is 60us (small load), but that assumes the board's external IS-pin RC
// filter (datasheet SS9.3.1) has only the bare-minimum 1us time constant; a filter chosen for
// better noise rejection needs several time constants to settle to <1% error, so an early ADC
// sample can land mid-transition and read a plausible-but-wrong partial value. Confirmed via live
// testing (2026-08): occasional readings around half the expected wattage, on both incandescent
// and LED loads, went away with this larger margin.
#define CMC_SPOC_IS_SETTLE_US  200U
// An incandescent bulb's cold filament draws several times its steady-state current for tens of
// milliseconds after turn-on (confirmed live 2026-08: ~50W inrush settling to 19.5W steady-state
// on a hi-beam bulb; 50ms still read ~25W, so the thermal tail is longer than first assumed) —
// sampling immediately at turn-on captures that spike, not the representative operating wattage.
// This is a much longer timescale than CMC_SPOC_IS_SETTLE_US (RC-filter settle, microseconds)
// and can't be waited out with a blocking delay without stalling the main loop, so the first
// sample after turn-on is deferred by this long instead.
// NOTE: cmc_feature_direction_indicator.c clamps blink_interval_x10ms to 10-200 (100ms-2000ms
// per phase) — this settle time must stay comfortably below the fastest configured blink phase,
// or a channel blinking at/near that minimum would never get sampled at all. 500ms+ (the
// realistic expected usage) leaves ample margin; a 100ms configured blink would not.
#define CMC_SPOC_INRUSH_SETTLE_MS  250U
// Rolling-average window for IS readings while a channel is ON, smoothing genuine sensor/load
// noise (confirmed live 2026-08: an LED bulb's own switching driver made raw readings fluctuate
// 1-8W even at steady state; averaging confirmed to help there). Deliberately NOT a plain moving
// average across on/off history — that would dilute a blinking channel's reported wattage by its
// duty cycle and could false-trigger the open-load fault check in cmc_feature_channel_info.c,
// which compares the reported current against open_load_ma whenever is_on() is true. The average
// is reset to empty on every OFF->ON transition instead, so it only ever blends samples from the
// CURRENT on-period.
#define CMC_SPOC_AVG_SAMPLES  8U
// Minimum time between two IS samples of the SAME channel in the round-robin (not the
// transition-triggered priority pass, which always fires once regardless). Without this, the
// round-robin's independent ~800ms rotation could occasionally land on a channel again within
// the remaining ~150-250ms of the SAME brief blink ON window right after its transition sample
// already fired — blending in a second, less-settled reading and making blinker wattage swing
// unpredictably (confirmed live 2026-08: sometimes 30W, varying 18-21W, for a steady 20W bulb).
#define CMC_SPOC_MIN_RESAMPLE_MS  400U
// The OUT-register reconciliation (see its comment in sample_all()) only overrides s_out_mask for
// a chip that's gone at least this long without an explicit set() call. A channel under active
// control (e.g. a blinker, whose feature calls set() every process() tick during both blink
// phases) already self-corrects any real hardware-side change on its own very next set() call
// (which unconditionally rewrites OUT via SPI) — so reconciling against a live readback there adds
// no benefit but risks a misread (more likely amid a blinker's much higher SPI/bus activity,
// worse under hazard's simultaneous higher current draw) wrongly clearing a bit that's actually
// still commanded on. Confirmed live 2026-08: this was corrupting s_out_mask for blinkers, making
// is_on() report OFF while genuinely blinking ON, which also fooled set()'s was_on edge-detection
// into treating the next call as a fresh transition and resetting the wattage average.
#define CMC_SPOC_RECONCILE_QUIET_MS  300U

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
static uint8_t  s_scan_index;                                 // next global channel for the current-sense round-robin
static uint32_t s_last_update_ms[CMC_CONFIG_HW_OUT_COUNT];    // HAL_GetTick() of each channel's last real IS sample
static bool     s_needs_sample[CMC_CONFIG_HW_OUT_COUNT];      // set on OFF->ON transition, sampled once due
static uint32_t s_sample_due_ms[CMC_CONFIG_HW_OUT_COUNT];     // HAL_GetTick() a pending sample becomes due (inrush settle)
static uint32_t s_is_raw_history[CMC_CONFIG_HW_OUT_COUNT][CMC_SPOC_AVG_SAMPLES]; // per-channel on-period sample ring buffer
static uint8_t  s_is_raw_count[CMC_CONFIG_HW_OUT_COUNT];      // valid samples in the ring buffer so far (caps at CMC_SPOC_AVG_SAMPLES)
static uint8_t  s_is_raw_idx[CMC_CONFIG_HW_OUT_COUNT];        // next ring buffer slot to write
static uint8_t  s_out_readback_prev[CMC_SPOC_CHIP_COUNT];     // previous tick's OUT-register reconciliation read, per chip
static uint32_t s_chip_last_set_ms[CMC_SPOC_CHIP_COUNT];      // HAL_GetTick() of the last cmc_util_switch_spoc_set() call touching this chip

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

// DCR.MUX=111B blanks that chip's ENTIRE OUT register, not just the IS mux (datasheet SS6.1.5
// Ready mode) — a chip with any channel commanded ON must park at a real channel select (0)
// instead, so its outputs stay live between/after current-sense reads; only a fully-idle chip is
// safe to leave at MUX_DISABLED.
static uint8_t spoc_idle_mux(uint8_t chip) {
    return (s_out_mask[chip] != 0U) ? 0U : CMC_SPOC_MUX_DISABLED;
}

// Physical OUTn bit position within a chip's nibble is mirrored (0<->3, 1<->2) versus the naive
// channel-within-chip index on this board — confirmed by live hardware testing (2026-08); applies
// equally to the OUT register bit and the DCR.MUX channel-select field (same "channel n" numbering).
static uint8_t spoc_bit_of(uint8_t spoc_channel) {
    return (uint8_t)(3U - (spoc_channel % CMC_SPOC_CH_PER_CHIP));
}

// Pushes a fresh raw IS sample into channel ch's ring buffer and recomputes s_is_raw[ch] as a
// TRIMMED mean of the buffer: the highest 0-2 values are excluded first (scaled by how many
// samples are actually available, so a short blink with only 1-2 samples still gets a plain
// average rather than being left with nothing). An incandescent bulb's inrush decay only ever
// taints the first sample or two of an on-period, so discarding the highest readings removes that
// bias without needing to precisely time sampling around the decay curve. Only ever discards the
// HIGHEST readings, so it can't mask a genuine open-load (LOW current) condition, and it has no
// effect on overcurrent/short-circuit fault detection, which comes from the SPOC's own
// hardware-latched ERRDIAG/WRNDIAG registers, not this software average — reporting-only fix.
static void spoc_push_sample(uint8_t ch, uint32_t raw) {
    s_is_raw_history[ch][s_is_raw_idx[ch]] = raw;
    s_is_raw_idx[ch] = (uint8_t)((s_is_raw_idx[ch] + 1U) % CMC_SPOC_AVG_SAMPLES);
    if (s_is_raw_count[ch] < CMC_SPOC_AVG_SAMPLES) { s_is_raw_count[ch]++; }
    uint8_t count = s_is_raw_count[ch];

    // Work on a scratch copy so trimming never corrupts the persistent ring buffer.
    uint32_t scratch[CMC_SPOC_AVG_SAMPLES];
    uint32_t sum = 0U;
    for (uint8_t i = 0U; i < count; i++) {
        scratch[i] = s_is_raw_history[ch][i];
        sum += scratch[i];
    }

    uint8_t trim = (count >= 5U) ? 2U : (count >= 3U) ? 1U : 0U;
    for (uint8_t t = 0U; t < trim; t++) {
        uint32_t max_val = 0U;
        uint8_t  max_idx  = 0U;
        for (uint8_t i = 0U; i < count; i++) {
            if (scratch[i] >= max_val) { max_val = scratch[i]; max_idx = i; }
        }
        sum -= max_val;
        scratch[max_idx] = 0U; // exclude from the next round of trimming (values can tie)
    }
    s_is_raw[ch] = sum / (count - trim);
}

/* ---- Public API -------------------------------------------------------------------------- */

void cmc_util_switch_spoc_init(void) {
    // Enable the DWT cycle counter once, used by spoc_delay_us() and spoc_xfer()'s tCSN(TD) wait
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0U;
    DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;

    s_out_mask[0] = 0U;
    s_out_mask[1] = 0U;
    s_scan_index  = 0U;
    s_chip_last_set_ms[0] = HAL_GetTick();
    s_chip_last_set_ms[1] = HAL_GetTick();
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
        s_last_update_ms[ch] = HAL_GetTick();
        s_needs_sample[ch] = false;
        s_is_raw_count[ch] = 0U;
        s_is_raw_idx[ch] = 0U;
    }
}

void cmc_util_switch_spoc_set(uint8_t ch, bool on) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
    uint8_t bit  = spoc_bit_of(sw->spoc_channel);
    uint8_t discard0, discard1;

    s_chip_last_set_ms[chip] = HAL_GetTick(); // see CMC_SPOC_RECONCILE_QUIET_MS

    // Callers like cmc_feature_direction_indicator.c call this every process() tick for the
    // entire ON phase (not just once at the transition) — capture the PREVIOUS state here so the
    // sample-timer arming below only fires on a genuine OFF->ON edge, not on every redundant
    // "still on" call, which would otherwise keep pushing s_sample_due_ms into the future forever
    // and the channel would never actually become due.
    bool was_on = (s_out_mask[chip] & (uint8_t)(1U << bit)) != 0U;

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

    // Only a genuine OFF->ON EDGE (was_on captured above) needs a fresh current reading — many
    // callers (e.g. cmc_feature_direction_indicator.c) call this every process() tick for the
    // whole ON phase, not just once at the transition; arming on every such redundant call would
    // keep resetting s_sample_due_ms into the future forever, so the channel would never actually
    // become due (this was a real bug: confirmed live as the cause of persistent random 0W misses
    // on blinkers). Not sampled RIGHT this instant either way — sampling immediately would
    // capture a cold incandescent filament's inrush current, not its steady-state draw (confirmed
    // live: ~50W inrush settling to 19.5W). Flag it for sample_all() to pick up once
    // CMC_SPOC_INRUSH_SETTLE_MS has elapsed, which stays well within even a brief 500ms
    // direction-indicator blink window.
    if (on && !was_on) {
        s_needs_sample[ch] = true;
        s_sample_due_ms[ch] = HAL_GetTick() + CMC_SPOC_INRUSH_SETTLE_MS;
        // Start a fresh average for this new on-period rather than blending in the previous
        // (now-stale) on-period's samples.
        s_is_raw_count[ch] = 0U;
        s_is_raw_idx[ch] = 0U;
    }
}

// Returns the last commanded on/off state, reconciled against real hardware once per
// sample_all() cycle (see there) rather than a live SPI read on every call — unlike PROFET's
// free/instant GPIO readback, an SPI register read costs a transaction plus a one-cycle
// pipeline delay, so it isn't done synchronously on every is_on() call.
bool cmc_util_switch_spoc_is_on(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return false; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
    uint8_t bit  = spoc_bit_of(sw->spoc_channel);
    return (s_out_mask[chip] & (uint8_t)(1U << bit)) != 0U;
}

void cmc_util_switch_spoc_sample_all(cmc_switch_status_t *status) {
    if (!spoc_any_channel_configured()) { return; }

    uint8_t wrndiag[CMC_SPOC_CHIP_COUNT];
    uint8_t errdiag[CMC_SPOC_CHIP_COUNT];
    uint8_t discard0, discard1;

    // Fault registers are independent of DCR.MUX — one read pair covers all 4 channels per chip.
    // Response is one transaction behind, so the 3rd transfer below is what returns ERRDIAG.
    // Uses spoc_idle_mux() rather than a hardcoded value so this never disturbs an active chip's
    // outputs — it just re-asserts whatever the last park step already left in place.
    spoc_xfer(build_read_wrndiag(), build_read_wrndiag(), &discard0, &discard1); // discard stale ack
    spoc_xfer(build_read_errdiag(), build_read_errdiag(), &wrndiag[0], &wrndiag[1]);
    spoc_xfer(build_dcr_write(spoc_idle_mux(0U)), build_dcr_write(spoc_idle_mux(1U)), &errdiag[0], &errdiag[1]);

    for (uint8_t ch = 0U; ch < CMC_CONFIG_HW_OUT_COUNT; ch++) {
        const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
        if (sw->switch_type != CMC_CONFIG_SWITCH_TYPE_SPOC) { continue; }
        uint8_t chip = sw->spoc_channel / CMC_SPOC_CH_PER_CHIP;
        uint8_t bit  = spoc_bit_of(sw->spoc_channel);
        bool err_latched = (errdiag[chip] & (uint8_t)(1U << bit)) != 0U;
        bool warn_set    = (wrndiag[chip] & (uint8_t)(1U << bit)) != 0U;
        s_fault_latched[ch] = err_latched;
        // Only a latched ERRDIAG bit is a hard fault; a WRNDIAG-only bit (e.g. inrush) is
        // reported as a non-latched warning rather than discarded.
        status[ch] = err_latched ? CMC_SWITCH_FAULT_OVERCURRENT
                   : warn_set    ? CMC_SWITCH_WARNING_OVERLOAD
                   :               CMC_SWITCH_POWER_GOOD;
    }

    // Priority pass: a channel flagged by cmc_util_switch_spoc_set() on a fresh OFF->ON
    // transition is serviced once its inrush-settle deadline (s_sample_due_ms) has passed —
    // gating on ELAPSED TIME rather than rotation position or bus-safety conditions, so it's not
    // subject to the earlier failure modes (competing channels stealing a single per-tick slot,
    // main-loop jitter pushing past a brief ON window). ALL due channels are serviced in the same
    // tick; a channel that's turned back off before becoming due just has its flag cleared with
    // no SPI transaction, since read_current_ma() already reports 0 for it regardless.
    for (uint8_t i = 0U; i < CMC_CONFIG_HW_OUT_COUNT; i++) {
        if (!s_needs_sample[i]) { continue; }
        uint8_t chip_i = i / CMC_SPOC_CH_PER_CHIP;
        uint8_t bit_i  = spoc_bit_of(i);
        bool i_is_on = (s_out_mask[chip_i] & (uint8_t)(1U << bit_i)) != 0U;
        if (!i_is_on) { s_needs_sample[i] = false; continue; } // off again already, nothing to sample
        if ((int32_t)(HAL_GetTick() - s_sample_due_ms[i]) < 0) { continue; } // still settling, check again next tick
        s_needs_sample[i] = false;
        uint8_t chip0_mux = (chip_i == 0U) ? bit_i : CMC_SPOC_MUX_DISABLED;
        uint8_t chip1_mux = (chip_i == 1U) ? bit_i : CMC_SPOC_MUX_DISABLED;
        spoc_xfer(build_dcr_write(chip0_mux), build_dcr_write(chip1_mux), &discard0, &discard1);
        spoc_delay_us(CMC_SPOC_IS_SETTLE_US); // let the IS-pin RC filter fully settle before sampling
        spoc_push_sample(i, spoc_read_is_raw());
        s_last_update_ms[i] = HAL_GetTick();
    }

    // Sample ONE global channel's current-sense per call, but ONLY when it's safe to do so: a
    // chip only contaminates the shared IS pin if it has an ACTIVE channel selected via its own
    // DCR.MUX at that moment (datasheet SS9.3.2) — if the other chip currently has zero channels
    // commanded on, its mux value is irrelevant (nothing to contribute), so no blanking is needed
    // and its (already-off) outputs are never disturbed. If the other chip DOES have something on
    // AND this channel's reading is still fresh enough, it's simply left stale rather than forcing
    // that chip into Ready mode (datasheet SS6.1.5) to blank its outputs. If it's been stale for
    // too long (CMC_SPOC_STALE_MS), sample anyway despite the disruption — at that rate (at most
    // once per several seconds per channel) the repetition is far below the perceptible-flicker
    // range confirmed during bring-up, so this bounds staleness without reintroducing visible
    // flicker. ERRDIAG/WRNDIAG-based fault detection above is unaffected either way.
    // A channel that's currently OFF is skipped entirely: read_current_ma() already reports 0
    // for an off channel regardless of s_is_raw, and sampling it anyway would risk overwriting a
    // good cached ON reading with a meaningless near-zero one.
    {
        uint8_t g = s_scan_index;
        uint8_t target_chip = g / CMC_SPOC_CH_PER_CHIP;
        uint8_t target_bit  = spoc_bit_of(g);
        bool channel_is_on = (s_out_mask[target_chip] & (uint8_t)(1U << target_bit)) != 0U;
        if (channel_is_on) {
            uint8_t other_chip = (uint8_t)(1U - target_chip);
            uint32_t now = HAL_GetTick();
            bool safe   = (s_out_mask[other_chip] == 0U);
            bool stale  = (now - s_last_update_ms[g]) >= CMC_SPOC_STALE_MS;
            bool cooled = (now - s_last_update_ms[g]) >= CMC_SPOC_MIN_RESAMPLE_MS;
            if (cooled && (safe || stale)) {
                uint8_t chip0_mux = (target_chip == 0U) ? target_bit : 0U;
                uint8_t chip1_mux = (target_chip == 1U) ? target_bit : 0U;
                spoc_xfer(build_dcr_write(chip0_mux), build_dcr_write(chip1_mux), &discard0, &discard1);
                spoc_delay_us(CMC_SPOC_IS_SETTLE_US); // let the IS-pin RC filter fully settle before sampling
                spoc_push_sample(g, spoc_read_is_raw());
                s_last_update_ms[g] = now;
            }
        }
        s_scan_index = (uint8_t)((g + 1U) % CMC_CONFIG_HW_OUT_COUNT);
    }

    // Park each chip's mux until the next sample_all() call — spoc_idle_mux() avoids leaving an
    // active chip blanked for the ~100ms until the next cycle (see its comment).
    spoc_xfer(build_dcr_write(spoc_idle_mux(0U)), build_dcr_write(spoc_idle_mux(1U)), &discard0, &discard1);

    // Reconcile our commanded shadow against the actual OUT register: a chip-side reset (e.g. a
    // brief VDD undervoltage event, STDDIAG.VSMON) reverts OUT to defaults without telling the
    // MCU directly, so without this is_on() would keep reporting a channel as "on" after such
    // an event until the next explicit set() call. Only accepted if CONFIRMED by two consecutive
    // identical reads (~200ms apart): a single one-off mismatch is more likely SPI noise/timing
    // (e.g. hazard mode's higher simultaneous current draw increasing bus noise) than a genuine
    // hardware-side change, and blindly trusting a single noisy read was clobbering s_out_mask
    // mid-blink — confirmed live 2026-08 as a cause of persistent random 0W misses, worst on hazard.
    uint8_t out_resp0, out_resp1;
    spoc_xfer(build_read_out(), build_read_out(), &discard0, &discard1);   // discard park's ack
    spoc_xfer(build_read_out(), build_read_out(), &out_resp0, &out_resp1); // = actual OUT register content
    uint8_t new0 = out_resp0 & 0x0FU;
    uint8_t new1 = out_resp1 & 0x0FU;
    uint32_t reconcile_now = HAL_GetTick();
    bool quiet0 = (reconcile_now - s_chip_last_set_ms[0]) >= CMC_SPOC_RECONCILE_QUIET_MS;
    bool quiet1 = (reconcile_now - s_chip_last_set_ms[1]) >= CMC_SPOC_RECONCILE_QUIET_MS;
    if (quiet0 && new0 == s_out_readback_prev[0]) { s_out_mask[0] = new0; }
    if (quiet1 && new1 == s_out_readback_prev[1]) { s_out_mask[1] = new1; }
    s_out_readback_prev[0] = new0;
    s_out_readback_prev[1] = new1;

    s_vdda_mv = cmc_util_mcu_read_vdda_mv();
}

int32_t cmc_util_switch_spoc_read_current_ma(uint8_t ch) {
    if (ch >= CMC_CONFIG_HW_OUT_COUNT) { return 0; }
    if (!cmc_util_switch_spoc_is_on(ch)) { return 0; }
    const cmc_config_switch_t *sw = &cmc_config_hw_out_channel_mapping[ch];
    return spoc_raw_to_ma(s_is_raw[ch], sw->ilis_ratio, sw->ris_ohms, s_vdda_mv);
}
