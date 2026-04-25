/**
  *********************************************************************************************
  * @file      cmc_config_type.h
  * @brief     Configuration types and structures
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_TYPE_H_
#define CMC_CONFIG_TYPE_H_

#include <stm32g4xx.h>
#include <stdint.h>
#include <stdbool.h>
#include "config/cmc_config_type_def.h"

// The configuration for input buttons and sensors (3 bytes)
typedef struct {
    uint8_t enabled; // Set 1 if to be used, set 0 if not to be used and the system will ignore reading it
    uint8_t device_id; // Maps to cmc_in_t, what device is connected to (eg: ignition, light switch, turn signal button, etc)
    uint8_t btn_type_id; // Maps to cmc_in_btn_type_t, how should the system interpret the button presses? (eg: direct, toggle, ignore)
} cmc_config_in_t;

// The configuration for output channels (2 bytes)
typedef struct {
    uint8_t enabled; // Set 1 if to be used, set 0 if not to be used and the system will turn off power from it
    uint8_t device_id; // Maps to cmc_out_t, what device is connected to (eg: horn, light, turn signal, etc)
} cmc_config_out_t;

// Unit configuration (46 bytes)
typedef struct {
    uint8_t unit_id; // The number of the I/O units configures, (1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS)
    uint8_t unit_name_id; // Maps to cmc_unit_name_t, used to identify the unit (eg: rear devices, front devices, instruments, auxiliary)
    uint8_t in_used; // The number of input pins used on this unit, should be less than or equal to 10
    uint8_t out_used; // The number of output channels used on this unit, should be less than or equal to 6
    cmc_config_in_t in[10]; // 30 bytes - The buttons/sensors connected to each digital input pin, maps to cmc_input_
    cmc_config_out_t out[6]; // 12 bytes - The equipment connected to each output channel, maps to cmc_equipment_t
} cmc_io_unit_config_t;

// Feature configuration (2 bytes)
typedef struct {
    uint8_t enabled; // Set 1 if to be used, set 0 if not to be used and the system will ignore it
    uint8_t feature_id; // Maps to cmc_feature_type_t, what feature is this configuration for (eg: horn signalling, auto headlight, etc)
} cmc_feature_t;

// Master configuration structure that holds the entire system configuration, including all I/O units and features
typedef struct {
    uint32_t signature;       // 4 bytes - To check if config is valid for the unit. It should be set to CMC_CONFIG_SIGNATURE if valid, if reset/newly flashed, it will be 0xFFFFFFFF or 0x00000000)
    uint32_t config_hash;     // 4 bytes - Hash of the systems global configuration, to be compared between units at startup by doing a canbus handshake to verify same global config across all units
    uint8_t  units_required;  // 1 byte - The number of I/O units required for the system, startup checks verifies or send alert, should be less than or equal to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS
    uint8_t  features_used;   // 1 byte - The number of features used in the system, should be less than or equal to CMC_CONFIG_MAX_SUPPORTED_FEATURES
    uint8_t  reserved[6];     // 6 bytes - Total bytes without padding = 234 bytes, with padding = 240 bytes
    cmc_io_unit_config_t io_unit[CMC_CONFIG_MAX_SUPPORTED_IO_UNITS];  // 4 * 46 bytes = 184 bytes - Configuration for each I/O unit in the system
    cmc_feature_t feature[CMC_CONFIG_MAX_SUPPORTED_FEATURES];         // 20 * 2 bytes = 40 bytes - Configuration for features enabled in the system
} cmc_config_t;

#endif /* CMC_CONFIG_TYPE_H_ */