#include "switch_controller.h"

#define SWITCH_CHANNEL_MIN         1U
#define SWITCH_CHANNEL_MAX         6U
#define SWITCH_BLINK_INTERVAL_MS   500U

static bool g_blink_running[SWITCH_CHANNEL_MAX + 1U] = { false };

static bool is_valid_channel(uint8_t channel) {
    return (channel >= SWITCH_CHANNEL_MIN) && (channel <= SWITCH_CHANNEL_MAX);
}

static void set_switch_output(uint8_t channel, GPIO_PinState state) {
    switch (channel) {
        case 1: HAL_GPIO_WritePin(SW1_IN_GPIO_Port, SW1_IN_Pin, state); break;
        case 2: HAL_GPIO_WritePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin, state); break;
        case 3: HAL_GPIO_WritePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin, state); break;
        case 4: HAL_GPIO_WritePin(SW3_IN_GPIO_Port, SW3_IN_Pin, state); break;
        case 5: HAL_GPIO_WritePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin, state); break;
        case 6: HAL_GPIO_WritePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin, state); break;
        default: break;
    }
}

static GPIO_PinState get_switch_output(uint8_t channel) {
    switch (channel) {
        case 1: return HAL_GPIO_ReadPin(SW1_IN_GPIO_Port, SW1_IN_Pin);
        case 2: return HAL_GPIO_ReadPin(SW2_IN0_GPIO_Port, SW2_IN0_Pin);
        case 3: return HAL_GPIO_ReadPin(SW2_IN1_GPIO_Port, SW2_IN1_Pin);
        case 4: return HAL_GPIO_ReadPin(SW3_IN_GPIO_Port, SW3_IN_Pin);
        case 5: return HAL_GPIO_ReadPin(SW4_IN0_GPIO_Port, SW4_IN0_Pin);
        case 6: return HAL_GPIO_ReadPin(SW4_IN1_GPIO_Port, SW4_IN1_Pin);
        default: return GPIO_PIN_RESET;
    }
}

void switch_controller_init(void) {
    // Turn off all Power (IN / IN0 / IN1 pins)
    HAL_GPIO_WritePin(SW1_IN_GPIO_Port, SW1_IN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW3_IN_GPIO_Port, SW3_IN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin, GPIO_PIN_RESET);

    for (uint8_t channel = SWITCH_CHANNEL_MIN; channel <= SWITCH_CHANNEL_MAX; channel++) {
        g_blink_running[channel] = false;
    }

    // Disable all diagnostics (DEN pins) and reset selections (DSEL pins)
    switch_disable_all_diagnostics();
}

void switch_turn_on(uint8_t channel) {
    if (!is_valid_channel(channel)) {
        return;
    }

    g_blink_running[channel] = false;
    set_switch_output(channel, GPIO_PIN_SET);
}

void switch_turn_on_blink(uint8_t channel) {
    if (!is_valid_channel(channel)) {
        return;
    }

    g_blink_running[channel] = true;
    set_switch_output(channel, GPIO_PIN_SET);
}

void switch_turn_off(uint8_t channel) {
    if (!is_valid_channel(channel)) {
        return;
    }

    g_blink_running[channel] = false;
    set_switch_output(channel, GPIO_PIN_RESET);
}

void switch_toggle(uint8_t channel) {
    if (!is_valid_channel(channel)) {
        return;
    }

    g_blink_running[channel] = false;

    switch (channel) {
        case 1: HAL_GPIO_TogglePin(SW1_IN_GPIO_Port, SW1_IN_Pin); break;
        case 2: HAL_GPIO_TogglePin(SW2_IN0_GPIO_Port, SW2_IN0_Pin); break;
        case 3: HAL_GPIO_TogglePin(SW2_IN1_GPIO_Port, SW2_IN1_Pin); break;
        case 4: HAL_GPIO_TogglePin(SW3_IN_GPIO_Port, SW3_IN_Pin); break;
        case 5: HAL_GPIO_TogglePin(SW4_IN0_GPIO_Port, SW4_IN0_Pin); break;
        case 6: HAL_GPIO_TogglePin(SW4_IN1_GPIO_Port, SW4_IN1_Pin); break;
    }
}

bool is_button_off(uint8_t channel) {
    if (!is_valid_channel(channel)) {
        return false;
    }

    return get_switch_output(channel) == GPIO_PIN_RESET;
}

void switch_controller_process(void) {
    const uint32_t tick = HAL_GetTick();
    const GPIO_PinState blink_state = ((tick / SWITCH_BLINK_INTERVAL_MS) % 2U == 0U)
        ? GPIO_PIN_SET
        : GPIO_PIN_RESET;

    for (uint8_t channel = SWITCH_CHANNEL_MIN; channel <= SWITCH_CHANNEL_MAX; channel++) {
        if (g_blink_running[channel]) {
            set_switch_output(channel, blink_state);
        }
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