/**
  *********************************************************************************************
  * @file      cmc_config_unit_info.h
  * @brief     Unit info — persistent flash storage for static unit-specific data
  *            Occupies a dedicated 2KB flash page that survives firmware re-flashing.
  *            Data is written as a single struct, page is erased only when saving new data.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_CONFIG_UNIT_INFO_H_
#define CMC_CONFIG_UNIT_INFO_H_

#include <stdint.h>
#include <stdbool.h>

// Flash page configuration for unit info
#define CMC_CONFIG_UNIT_INFO_FLASH_ADDR   0x0801E800U  // Page before RUNTIME page
#define CMC_CONFIG_UNIT_INFO_PAGE_SIZE    0x800U       // 2KB page

// Marker to identify a valid unit store entry (ASCII "UNID")
#define CMC_CONFIG_UNIT_INFO_SIGNATURE    0x554E4944U

// Unit store data, padded to 8 bytes (one flash double-word) per field group
// Add future static fields here, keeping the struct size a multiple of 8 bytes
typedef struct {
    uint32_t signature;  // Must be CMC_CONFIG_UNIT_INFO_SIGNATURE for the data to be considered valid
    uint32_t crc;      // CRC of all subsequent data for integrity verification
    uint32_t unit_id;    // Unit ID (1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS)
    uint32_t _pad;       // Pad to 16 bytes (2 dwords)
} cmc_config_unit_info_t;

// Compile-time check: struct must be exactly one double-word for a single flash write
_Static_assert(sizeof(cmc_config_unit_info_t) % 8 == 0, "cmc_config_unit_info_t size must be a multiple of 8 bytes for flash double-word programming");

// Init: read flash page, load data into RAM if valid. 
void cmc_config_unit_info_init(void);

#endif /* CMC_CONFIG_UNIT_INFO_H_ */
