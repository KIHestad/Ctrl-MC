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
#include "config/cmc_config_hw_mapping.h"
#include "config/cmc_config_type_unit.h"
#include "feature/cmc_feature_horn.h"
#include "feature/cmc_feature_ignition.h"
#include "feature/cmc_feature_starter.h"
#include "feature/cmc_feature_direction_indicator.h"
#include "feature/cmc_feature_light.h"
#include "feature/cmc_feature_brake_light.h"
#include "feature/cmc_feature_neutral.h"
#include "feature/cmc_feature_oil_pressure.h"

// The configuration for input buttons and sensors (3 bytes)
typedef struct {
    uint8_t enabled; // Set 1 if to be used, set 0 if not to be used and the system will ignore reading it
    uint8_t device_id; // Maps to cmc_config_in_device_t, what device is connected to (eg: ignition, light switch, turn signal button, etc)
    uint8_t usage_id; // Maps to cmc_config_in_usage_t, how system is to use this button, eg: direct, toggle, ignore
} cmc_config_in_t;

// The configuration for output channels (2 bytes)
typedef struct {
    uint8_t enabled; // Set 1 if to be used, set 0 if not to be used and the system will turn off power from it
    uint8_t device_id; // Maps to cmc_config_out_device_t, what device is connected to (eg: horn, light, turn signal, etc)
} cmc_config_out_t;

// Unit configuration (46 bytes)
typedef struct {
    uint8_t unit_id; // The number of the I/O units configures, (1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS)
    uint8_t unit_name_id; // Maps to cmc_config_unit_name_t, used to identify the unit (eg: rear devices, front devices, instruments, auxiliary)
    uint8_t in_used; // The number of input pins used on this unit, should be less than or equal to CMC_CONFIG_HW_IN_DIGITAL_COUNT
    uint8_t out_used; // The number of output channels used on this unit, should be less than or equal to CMC_CONFIG_HW_OUT_COUNT
    cmc_config_in_t in[CMC_CONFIG_HW_IN_DIGITAL_COUNT]; // 30 bytes - The buttons/sensors connected to each digital input pin, maps to cmc_input_
    cmc_config_out_t out[CMC_CONFIG_HW_OUT_COUNT]; // 12 bytes - The equipment connected to each output channel, maps to cmc_equipment_t
} cmc_config_io_unit_t;


/*********************************************************************************************************************
    Master configuration structure that holds the entire system configuration, including all I/O units and features
**********************************************************************************************************************/
typedef struct {
    
    // Signature and CRC to ensure valid operation 
    uint32_t signature; // Must be CMC_CONFIG_SIGNATURE for the data to be considered valid
    uint32_t crc;       // CRC32 of the entire configuration (except the crc field itself) to verify integrity
    uint32_t version;   // Configuration version number, can be used for migration logic if the config structure changes in future firmware versions

    // IO unit configuration
    uint8_t  units_required; // for notifying if fewer units are found on the bus than anticipated 
    cmc_config_io_unit_t io_unit[CMC_CONFIG_MAX_SUPPORTED_IO_UNITS];
    
    // Feature-specific configuration sections
    cmc_feature_ignition_t feature_ignition;
    cmc_feature_starter_t  feature_starter;
    cmc_feature_horn_t     feature_horn;
    cmc_feature_direction_indicator_t feature_direction_indicator;
    cmc_feature_light_t    feature_light;
    cmc_feature_brake_light_t feature_brake_light;
    cmc_feature_neutral_t      feature_neutral;
    cmc_feature_oil_pressure_t feature_oil_pressure;
    
    // Automatic padding to make the total size of the structure a multiple of 8 bytes for flash storage efficiency
    uint8_t  _padding[(8 - 
        (
            sizeof(uint32_t)*3
            + sizeof(uint8_t)*1
            + sizeof(cmc_config_io_unit_t)*CMC_CONFIG_MAX_SUPPORTED_IO_UNITS
            + sizeof(cmc_feature_ignition_t)
            + sizeof(cmc_feature_starter_t)
            + sizeof(cmc_feature_horn_t)
            + sizeof(cmc_feature_direction_indicator_t)
            + sizeof(cmc_feature_light_t)
            + sizeof(cmc_feature_brake_light_t)
            + sizeof(cmc_feature_neutral_t)
            + sizeof(cmc_feature_oil_pressure_t)
        ) % 8) % 8];
    
} cmc_config_t;

// Compile-time check: struct must be a multiple of 8 bytes for 64-bit flash double-word programming
_Static_assert(sizeof(cmc_config_t) % 8 == 0, "cmc_config_t size must be a multiple of 8 bytes for flash double-word programming");
// Compile-time check: struct must fit within the 2KB flash config page
_Static_assert(sizeof(cmc_config_t) <= 2048U, "cmc_config_t exceeds the 2KB flash config page size");

// The active system configuration, loaded from flash at startup
extern cmc_config_t cmc_config;
extern const cmc_config_io_unit_t* cmc_config_this_unit;

#endif /* CMC_CONFIG_TYPE_H_ */