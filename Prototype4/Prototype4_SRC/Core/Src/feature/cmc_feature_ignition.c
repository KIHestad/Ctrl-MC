/**
  *********************************************************************************************
  * @file      cmc_feature_ignition.c
  * @brief     Ignition feature control logic
  * @details   Controls cmc_app_state.veichle_state.ignition_on based on configuration:
  *            - Disabled (enabled=0): ignition_on is forced to true unconditionally.
  *              Use when no ignition sensor is wired or during bench testing.
  *            - Enabled (enabled=1): ignition_on starts false, then follows the
  *              CMC_CONFIG_IN_DEVICE_IGNITION input pin (active-low: LOW = ignition on)
  *              via cmc_app_state_update() on this unit, and is broadcast over CAN on change.
  *              Other units receive the state via CMC_CAN_MESSAGE_FEATURE_IGNITION_FRAME_ID.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "config/cmc_config_type.h"
#include "app/cmc_app_state.h"
#include "feature/cmc_feature_ignition.h"

static bool cmc_feature_ignition_enabled = false; // Cached from config in init to avoid repeated reads

void cmc_feature_ignition_init(void) {
    cmc_feature_ignition_enabled = (cmc_config.feature_ignition.enabled == 1);
    if (!cmc_feature_ignition_enabled) {
        // Disabled: force ignition on — no hardware dependency required
        cmc_app_state.veichle_state.ignition_on = true;
    } else {
        // Enabled: start as off; the scanner will drive it on via cmc_app_state_update
        // when CMC_CONFIG_IN_DEVICE_IGNITION is configured and the pin is active (LOW)
        cmc_app_state.veichle_state.ignition_on = false;
    }
}

void cmc_feature_ignition_process(void) {
    if (!cmc_feature_ignition_enabled) {
        // Disabled: keep forcing ignition on each loop so no other source can override
        cmc_app_state.veichle_state.ignition_on = true;
    }
    // Enabled: nothing to do here — ignition_on is maintained by:
    //   - Local input:  cmc_app_state_update (CMC_CONFIG_IN_DEVICE_IGNITION, TX path)
    //   - Remote CAN:   on_can_receive (CMC_CAN_MESSAGE_FEATURE_IGNITION_FRAME_ID, RX path)
}
