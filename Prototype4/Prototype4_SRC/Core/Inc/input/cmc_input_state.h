/**
  **************************************************************************************************************************
  * @file      cmc_input_state.h
  * @brief     Global external struct for holding all input states to be used across the system, also distributed over CAN
  *            Including: physical button and sensor states coming from motorcycle hardware
  *            also virtual inputs from feature on the unit itself, like GPS, IMU or temperature sensors if equipped
  *            and logical inputs that are derived from physical inputs but represent a logical state like "ignition on/off"
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  ***************************************************************************************************************************
  */

#ifndef CMC_INPUT_STATE_H_
#define CMC_INPUT_STATE_H_

#include <stdint.h>
#include "config/cmc_config_type.h"

// virtual input states
typedef struct {
    bool ignition_on;  
    bool engine_running;
    uint32_t speed_kph;
    uint32_t rpm;
} cmc_input_state_virtual_t;



// Light switch buttons
typedef struct {
    bool park_on;  
    bool low_beam_on; 
    bool high_beam_on;
} cmc_input_state_button_light_t;

// Direction turn signal buttons
typedef struct {
    bool left_on;  
    bool right_on; 
    bool hazard_on; 
} cmc_input_state_button_turn_signal_t;

// All input buttons
typedef struct {
    bool clutch_lever_pressed; // True if the clutch lever is currently pressed, false if not pressed
    bool brake_lever_pressed;  // True if the brake lever is currently pressed, false if not pressed
    bool brake_pedal_pressed;  // True if the brake pedal is currently pressed, false if not pressed
    bool horn_button_pressed; // True if the horn button is currently pressed, false if not pressed
    bool starter_button_pressed; // True if the starter button is currently pressed, false if not pressed
    bool kill_switch_on; // True if the kill switch is currently on (cutting ignition), false if off
    cmc_input_state_button_light_t light_switch; // State of the light switch buttons
    cmc_input_state_button_turn_signal_t turn_signal; // State of the turn signal buttons
   
} cmc_input_state_button_t;

// Master struct for holding the state of all inputs, updated by the input scanner and used across the system and sent over CAN
typedef struct {  
  cmc_input_state_virtual_t veichle_state; // Virtual inputs representing logical states of the vehicle, derived from physical inputs
  cmc_input_state_button_t button; // The state of all buttons
} cmc_input_state_t;

// The global input state variable, updated by the input scanner and used across the system and sent over CAN
extern cmc_input_state_t cmc_input_state;

#endif /* CMC_INPUT_STATE_H_ */
