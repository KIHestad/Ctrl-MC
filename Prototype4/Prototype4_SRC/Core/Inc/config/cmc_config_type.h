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
#include "config/cmc_config_type_unit.h"
#include "feature/cmc_feature_horn.h"

typedef enum {
    CMC_CONFIG_STATUS_SUCCESS = 0,
    CMC_CONFIG_STATUS_ERROR   = 1,
    CMC_CONFIG_STATUS_INVALID_FLASH_SIGNATURE = 2,
    CMC_CONFIG_STATUS_INVALID_RAM_SIGNATURE = 3,    
} cmc_config_status_t;

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

// Master configuration structure that holds the entire system configuration, including all I/O units and features
typedef struct {
    uint32_t signature;                                                
    uint32_t config_hash;                                              
    uint8_t  units_required;                                           
    uint8_t  features_used;                                            
    cmc_io_unit_config_t io_unit[CMC_CONFIG_MAX_SUPPORTED_IO_UNITS];   
    cmc_feature_horn_t feature_horn;                                   
    // Add automatic padding to make the total size of the structure a multiple of 8 bytes for flash storage efficiency
    uint8_t  _padding[((
        sizeof(uint32_t)*2 
        + sizeof(uint8_t)*2 
        + sizeof(cmc_io_unit_config_t)*CMC_CONFIG_MAX_SUPPORTED_IO_UNITS 
        + sizeof(cmc_feature_horn_t)
    ) % 8) % 8];                                   
    
} cmc_config_t;

// The active system configuration, loaded from flash at startup
extern cmc_config_t cmc_config; 

#endif /* CMC_CONFIG_TYPE_H_ */