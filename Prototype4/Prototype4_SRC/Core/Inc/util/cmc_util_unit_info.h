/**
  *********************************************************************************************
  * @file      cmc_util_unit_store.h
  * @brief     Unit store — persistent flash storage for static unit-specific data
  *            Occupies a dedicated 2KB flash page that survives firmware re-flashing.
  *            Data is written as a single struct, page is erased only when saving new data.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_UNIT_STORE_H_
#define CMC_UTIL_UNIT_STORE_H_

#include <stdint.h>
#include <stdbool.h>

// Flash page configuration for unit store
#define CMC_UNIT_INFO_FLASH_ADDR   0x0801E800U  // Page before RUNTIME page
#define CMC_UNIT_INFO_PAGE_SIZE    0x800U       // 2KB page

// Marker to identify a valid unit store entry (ASCII "UNID")
#define CMC_UNIT_INFO_SIGNATURE       0x554E4944U

// Unit store data, padded to 8 bytes (one flash double-word) per field group
// Add future static fields here, keeping the struct size a multiple of 8 bytes
typedef struct {
    uint32_t signature;     // Must be CMC_UNIT_INFO_SIGNATURE for the data to be considered valid
    uint8_t  unit_id;       // Unit ID (1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS)
    uint8_t  _reserved[3];  // Reserved for future use, pad to 8-byte boundary
} cmc_unit_info_t;

// Init: read flash page, load data into RAM if valid. Returns true if a valid entry was found.
void cmc_unit_info_init(void);

// Save unit store data to flash (erases page, then writes). Returns true on success.
bool cmc_unit_info_save(const cmc_unit_info_t* data);

#endif /* CMC_UTIL_UNIT_STORE_H_ */
