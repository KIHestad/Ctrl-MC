/**
  **************************************************************************************************************************
  * @file      cmc_app_state.h
  * @brief     Global external struct for holding the application state, used across the system and distributed over CAN
  *            Including: physical button and sensor states coming from motorcycle hardware
  *            also virtual inputs from features on the unit itself, like GPS, IMU or temperature sensors if equipped
  *            and logical inputs that are derived from physical inputs but represent a logical state like "ignition on/off"
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  ***************************************************************************************************************************
  */

#ifndef CMC_APP_STATE_H_
#define CMC_APP_STATE_H_

#include <stdint.h>
#include "config/cmc_config_type.h"

// Vehicle state
typedef struct {
    bool ignition_on;
    bool ignition_on_pending_broadcast;
    bool engine_running;
    uint32_t speed_kph;
    uint32_t rpm;
} cmc_app_state_vehicle_t;

// General simple button
typedef struct {
    bool on;
    bool pending_broadcast;
} cmc_app_state_button_t;

// Light state
typedef struct {
    bool park_on;  
    bool low_beam_on; 
    bool high_beam_on;
    bool pending_broadcast;
} cmc_app_state_light_t;

// Directional turn signal state
typedef struct {
    bool left_on;
    bool right_on;
    bool hazard_on;
    bool pending_broadcast;
    bool pending_resync;   // Set by CAN RX when a direction indicator message arrives while active; cleared by feature process()
} cmc_app_state_directional_indicator_t;

// All input buttons — written by cmc_app_state_updater (raw input scanner + CAN RX)
typedef struct {
    cmc_app_state_button_t clutch_lever;
    cmc_app_state_button_t brake_lever;
    cmc_app_state_button_t brake_pedal;
    cmc_app_state_button_t brake_light;  // Resolved brake active state (lever OR pedal, OR CAN RX)
    cmc_app_state_button_t neutral;       // Neutral gear sensor state (active-low sensor, OR CAN RX)
    cmc_app_state_button_t oil_pressure;  // Oil pressure low warning (active-low sensor, OR CAN RX)
    cmc_app_state_button_t horn;
    cmc_app_state_button_t starter;
    cmc_app_state_button_t kill_switch;
    cmc_app_state_directional_indicator_t directional_indicator;
    cmc_app_state_light_t light;
} cmc_app_state_feature_t;

// Master application state struct
typedef struct {  
    cmc_app_state_vehicle_t vehicle;
    cmc_app_state_feature_t feature;                     
} cmc_app_state_t;

// Global application state — read by all modules, written only by the owning module per field group
extern cmc_app_state_t cmc_app_state;

#endif /* CMC_APP_STATE_H_ */
