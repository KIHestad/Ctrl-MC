#include "switch_controller.h"

void switch_controller_init(void) {
    // Turn off all Power (IN / IN0 / IN1 pins)
    HAL_GPIO_WritePin(SW1_IN_GPIO_Port, SW1_IN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW3_IN_GPIO_Port, SW3_IN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin, GPIO_PIN_RESET);

    // Disable all diagnostics (DEN pins) and reset selections (DSEL pins)
    switch_disable_all_diagnostics();
}

void switch_turn_on(uint8_t channel) {
    switch (channel) {
        case 1: HAL_GPIO_WritePin(SW1_IN_GPIO_Port, SW1_IN_Pin, GPIO_PIN_SET); break;
        case 2: HAL_GPIO_WritePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin, GPIO_PIN_SET); break;
        case 3: HAL_GPIO_WritePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin, GPIO_PIN_SET); break;
        case 4: HAL_GPIO_WritePin(SW3_IN_GPIO_Port, SW3_IN_Pin, GPIO_PIN_SET); break;
        case 5: HAL_GPIO_WritePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin, GPIO_PIN_SET); break;
        case 6: HAL_GPIO_WritePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin, GPIO_PIN_SET); break;
    }
}

void switch_turn_off(uint8_t channel) {
    switch (channel) {
        case 1: HAL_GPIO_WritePin(SW1_IN_GPIO_Port, SW1_IN_Pin, GPIO_PIN_RESET); break;
        case 2: HAL_GPIO_WritePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin, GPIO_PIN_RESET); break;
        case 3: HAL_GPIO_WritePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin, GPIO_PIN_RESET); break;
        case 4: HAL_GPIO_WritePin(SW3_IN_GPIO_Port, SW3_IN_Pin, GPIO_PIN_RESET); break;
        case 5: HAL_GPIO_WritePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin, GPIO_PIN_RESET); break;
        case 6: HAL_GPIO_WritePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin, GPIO_PIN_RESET); break;
    }
}

void switch_toggle(uint8_t channel) {
    switch (channel) {
        case 1: HAL_GPIO_TogglePin(SW1_IN_GPIO_Port, SW1_IN_Pin); break;
        case 2: HAL_GPIO_TogglePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin); break;
        case 3: HAL_GPIO_TogglePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin); break;
        case 4: HAL_GPIO_TogglePin(SW3_IN_GPIO_Port, SW3_IN_Pin); break;
        case 5: HAL_GPIO_TogglePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin); break;
        case 6: HAL_GPIO_TogglePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin); break;
    }
}

void switch_enable_diagnostic(uint8_t channel) {
    // Note: To avoid ADC collision or overloading, you usually disable others first
    // when multiplexing the IS pins, but since SW1/SW2/SW3/SW4 have separate IS pins
    // in your setup (PA2, PA3, PB1, PB12), they can technically run in parallel. 
    // However, DSEL must be set correctly for dual channel switches.
    
    switch (channel) {
        case 1:
            HAL_GPIO_WritePin(SW1_DEN_GPIO_Port, SW1_DEN_Pin, GPIO_PIN_SET);
            break;
            
        case 2:
            HAL_GPIO_WritePin(SW2_DSEL_GPIO_Port, SW2_DSEL_Pin, GPIO_PIN_RESET); // DSEL Low = CH0
            HAL_GPIO_WritePin(SW2_DEN_GPIO_Port, SW2_DEN_Pin, GPIO_PIN_SET);
            break;
            
        case 3:
            HAL_GPIO_WritePin(SW2_DSEL_GPIO_Port, SW2_DSEL_Pin, GPIO_PIN_SET);   // DSEL High = CH1
            HAL_GPIO_WritePin(SW2_DEN_GPIO_Port, SW2_DEN_Pin, GPIO_PIN_SET);
            break;
            
        case 4:
            HAL_GPIO_WritePin(SW3_DEN_GPIO_Port, SW3_DEN_Pin, GPIO_PIN_SET);
            break;
            
        case 5:
            HAL_GPIO_WritePin(SW4_DSEL_GPIO_Port, SW4_DSEL_Pin, GPIO_PIN_RESET); // DSEL Low = CH0
            HAL_GPIO_WritePin(SW4_DEN_GPIO_Port, SW4_DEN_Pin, GPIO_PIN_SET);
            break;
            
        case 6:
            HAL_GPIO_WritePin(SW4_DSEL_GPIO_Port, SW4_DSEL_Pin, GPIO_PIN_SET);   // DSEL High = CH1
            HAL_GPIO_WritePin(SW4_DEN_GPIO_Port, SW4_DEN_Pin, GPIO_PIN_SET);
            break;
    }
}

void switch_disable_all_diagnostics(void) {
    HAL_GPIO_WritePin(SW1_DEN_GPIO_Port, SW1_DEN_Pin, GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(SW2_DEN_GPIO_Port, SW2_DEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW2_DSEL_GPIO_Port, SW2_DSEL_Pin, GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(SW3_DEN_GPIO_Port, SW3_DEN_Pin, GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(SW4_DEN_GPIO_Port, SW4_DEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW4_DSEL_GPIO_Port, SW4_DSEL_Pin, GPIO_PIN_RESET);
}