/**
  *********************************************************************************************
  * @file      cmc_util_usage_journal.c
  * @brief     Usage journal — rolling flash log for frequently updated values
  *            Appends 8-byte entries sequentially within a 2KB flash page (256 slots).
  *            Only erases the page when all slots are used, extending flash endurance to ~2.56M writes.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_usage_journal.h"
#include "util/cmc_util_crc.h"
#include "stm32g4xx_hal.h"
#include <stdbool.h>

// Pointer to the usage journal flash page (memory-mapped, read directly)
static const cmc_usage_journal_data_t* journal_page = (const cmc_usage_journal_data_t*)CMC_USAGE_JOURNAL_FLASH_ADDR;

// RAM copy of the current usage journal data
static cmc_usage_journal_data_t journal_current = {0};

// Index of the next free slot in the flash page (0 to CMC_USAGE_JOURNAL_MAX_ENTRIES)
static uint32_t next_free_slot = 0;

// Erased flash reads as 0xFFFFFFFF — detect end-of-log via the (now first) crc field
#define CMC_USAGE_JOURNAL_ERASED_MARKER  0xFFFFFFFFU

// Helper: compute flash page number from address
static uint32_t journal_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Helper: erase the usage journal flash page
static bool journal_erase_page(void) {
    HAL_StatusTypeDef hal_status;

    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }
    
    FLASH_EraseInitTypeDef erase_init = {0};
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_1;
    erase_init.Page      = journal_get_page(CMC_USAGE_JOURNAL_FLASH_ADDR);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Helper: write one entry to a specific slot (writes ALL double-words of the struct)
static bool journal_write_slot(uint32_t slot, const cmc_usage_journal_data_t* data) {
    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    const uint32_t base_addr = CMC_USAGE_JOURNAL_FLASH_ADDR + (slot * sizeof(cmc_usage_journal_data_t));
    const uint64_t* src = (const uint64_t*)data;
    const size_t dwords = sizeof(cmc_usage_journal_data_t) / 8U;

    for (size_t i = 0; i < dwords; i++) {
        hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, base_addr + (i * 8U), src[i]);
        if (hal_status != HAL_OK) {
            break;
        }
    }

    HAL_FLASH_Lock();
    return (hal_status == HAL_OK);
}

// Init: scan flash page to find the latest valid entry and the next free slot
bool cmc_usage_journal_init(void) {
    next_free_slot = 0;
    journal_current = (cmc_usage_journal_data_t){0};

    for (uint32_t i = 0; i < CMC_USAGE_JOURNAL_MAX_ENTRIES; i++) {
        // End-of-log: erased slot
        if (journal_page[i].crc == CMC_USAGE_JOURNAL_ERASED_MARKER) {
            break;
        }

        // Verify CRC; corrupted entries are skipped (do not advance journal_current)
        cmc_usage_journal_data_t entry = journal_page[i];
        if (CMC_CRC_CALCULATE_PAYLOAD(&entry) == entry.crc) {
            journal_current = entry;
        }
        next_free_slot = i + 1;
    }

    return true;
}

// Save usage journal data to the next available flash slot
bool cmc_usage_journal_save(uint32_t total_km, uint32_t trip_km) {
    // If the page is full, erase it and start from slot 0
    if (next_free_slot >= CMC_USAGE_JOURNAL_MAX_ENTRIES) {
        if (!journal_erase_page()) {
            return false;
        }
        next_free_slot = 0;
    }

    // Build entry, compute CRC over payload (total_km + trip_km + _pad)
    cmc_usage_journal_data_t entry = {
        .crc      = 0,
        .total_km = total_km,
        .trip_km  = trip_km,
        ._pad     = 0,
    };
    entry.crc = CMC_CRC_CALCULATE_PAYLOAD(&entry);

    if (!journal_write_slot(next_free_slot, &entry)) {
        return false;
    }

    // Update RAM copy and advance the slot pointer
    journal_current = entry;
    next_free_slot++;

    return true;
}

// Get pointer to the current usage journal data in RAM
const cmc_usage_journal_data_t* cmc_usage_journal_get(void) {
    return &journal_current;
}

// Reset trip counter and save immediately
bool cmc_usage_journal_reset_trip(void) {
    return cmc_usage_journal_save(journal_current.total_km, 0);
}
