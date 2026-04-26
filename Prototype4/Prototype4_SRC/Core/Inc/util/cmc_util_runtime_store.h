/**
 *********************************************************************************************
 * @file      cmc_util_runtime_store.h
 * @brief     Runtime data storage for frequently updated values (odometer, trip counter)
 *            Uses a rolling flash log to minimize page erases and extend flash endurance.
 * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
 * @copyright KI Hestad, Complicated Productions
 *********************************************************************************************
 */

#ifndef CMC_UTIL_RUNTIME_STORE_H_
#define CMC_UTIL_RUNTIME_STORE_H_

#include <stdint.h>
#include "config/cmc_config_manager.h" // For cmc_config_status_t

// Runtime data entry, exactly 8 bytes = one flash double-word
typedef struct {
    uint32_t total_km;  // Total odometer in km, never resets
    uint32_t trip_km;   // Trip counter in km, user-resettable
} cmc_runtime_data_t;

// Flash page configuration for runtime storage
#define CMC_RUNTIME_FLASH_ADDR    0x0801F000U                                          // Page just before CONFIG page
#define CMC_RUNTIME_PAGE_SIZE     0x800U                                               // 2KB page
#define CMC_RUNTIME_MAX_ENTRIES   (CMC_RUNTIME_PAGE_SIZE / sizeof(cmc_runtime_data_t)) // 256 entries per page

// Init: scans flash page and loads the latest entry into RAM, call at startup
bool cmc_runtime_store_init(void);

// Save current runtime data to the next available flash slot (call every km and before shutdown)
bool cmc_runtime_store_save(const cmc_runtime_data_t* data);

// Get the current runtime data loaded into RAM at init
const cmc_runtime_data_t* cmc_runtime_store_get(void);

// Reset the trip counter to zero and save immediately
bool cmc_runtime_store_reset_trip(void);

#endif /* CMC_UTIL_RUNTIME_STORE_H_ */
