/**
 *********************************************************************************************
 * @file      cmc_util_usage_journal.h
 * @brief     Usage journal — rolling flash log for frequently updated values (odometer, trip counter)
 *            Uses a rolling flash log to minimize page erases and extend flash endurance.
 * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
 * @copyright KI Hestad, Complicated Productions
 *********************************************************************************************
 */

#ifndef CMC_UTIL_USAGE_JOURNAL_H_
#define CMC_UTIL_USAGE_JOURNAL_H_

#include <stdint.h>
#include "config/cmc_config_manager.h" // For cmc_config_status_t

// Usage journal data entry, exactly 8 bytes = one flash double-word
typedef struct {
    uint32_t crc;       // CRC of all subsequent data for integrity verification
    uint32_t total_km;  // Total odometer in meters, never resets
    uint32_t trip_km;   // Trip counter in meters, user-resettable
    uint32_t _pad;      // Pad to 16 bytes (2 dwords)
} cmc_usage_journal_data_t;

// Compile-time check: entry must be exactly one double-word for single flash write
_Static_assert(sizeof(cmc_usage_journal_data_t) % 8 == 0, "cmc_usage_journal_data_t size must be a multiple of 8 bytes for flash double-word programming");

// Flash page configuration for usage journal storage
#define CMC_USAGE_JOURNAL_FLASH_ADDR    0x0801F000U                                                      // Page just before CONFIG page
#define CMC_USAGE_JOURNAL_PAGE_SIZE     0x800U                                                           // 2KB page
#define CMC_USAGE_JOURNAL_MAX_ENTRIES   (CMC_USAGE_JOURNAL_PAGE_SIZE / sizeof(cmc_usage_journal_data_t)) // 128 entries per page

// Init: scans flash page and loads the latest entry into RAM, call at startup
bool cmc_usage_journal_init(void);

// Save current usage journal data to the next available flash slot (call every km and before shutdown)
bool cmc_usage_journal_save(uint32_t total_km, uint32_t trip_km);

// Get the current usage journal data loaded into RAM at init
const cmc_usage_journal_data_t* cmc_usage_journal_get(void);

// Reset the trip counter to zero and save immediately
bool cmc_usage_journal_reset_trip(void);

#endif /* CMC_UTIL_USAGE_JOURNAL_H_ */
