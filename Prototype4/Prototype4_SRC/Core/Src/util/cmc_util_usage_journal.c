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
#include "stm32g4xx_hal.h"
#include <stdbool.h>

// Compile-time check: entry must be exactly one double-word for single flash write
_Static_assert(sizeof(cmc_usage_journal_data_t) == sizeof(uint64_t), "cmc_usage_journal_data_t must be exactly 8 bytes (one flash double-word)");

// Pointer to the usage journal flash page (memory-mapped, read directly)
static const cmc_usage_journal_data_t* journal_page = (const cmc_usage_journal_data_t*)CMC_USAGE_JOURNAL_FLASH_ADDR;

// RAM copy of the current usage journal data
static cmc_usage_journal_data_t journal_current = {0};

// Index of the next free slot in the flash page (0 to CMC_USAGE_JOURNAL_MAX_ENTRIES)
static uint32_t next_free_slot = 0;

// Erased flash reads as 0xFFFFFFFF, so an erased entry has total_km == 0xFFFFFFFF
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

// Helper: write one entry to a specific slot
static bool journal_write_slot(uint32_t slot, const cmc_usage_journal_data_t* data) {
    HAL_StatusTypeDef hal_status;

    uint32_t dest_addr = CMC_USAGE_JOURNAL_FLASH_ADDR + (slot * sizeof(cmc_usage_journal_data_t));
    uint64_t dword;
    // Copy the struct into a uint64_t for the double-word flash write
    const uint32_t* src = (const uint32_t*)data;
    uint32_t* dst = (uint32_t*)&dword;
    dst[0] = src[0];
    dst[1] = src[1];

    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, dest_addr, dword);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Init: scan flash page to find the latest valid entry and the next free slot
bool cmc_usage_journal_init(void) {

    // Scan forward to find the first erased slot
    next_free_slot = 0;
    for (uint32_t i = 0; i < CMC_USAGE_JOURNAL_MAX_ENTRIES; i++) {
        if (journal_page[i].total_km == CMC_USAGE_JOURNAL_ERASED_MARKER) {
            break;
        }
        next_free_slot = i + 1;
    }

    if (next_free_slot > 0) {
        // Load the last written entry into RAM
        journal_current.total_km = journal_page[next_free_slot - 1].total_km;
        journal_current.trip_km  = journal_page[next_free_slot - 1].trip_km;
    } else {
        // Page is fully erased (fresh chip or after reset), start at zero
        journal_current.total_km = 0;
        journal_current.trip_km  = 0;
    }

    return true;
}

// Save usage journal data to the next available flash slot
bool cmc_usage_journal_save(const cmc_usage_journal_data_t* data) {
    if (data == NULL) {
        return false;
    }

    // If the page is full, erase it and start from slot 0
    if (next_free_slot >= CMC_USAGE_JOURNAL_MAX_ENTRIES) {
        bool erase_status = journal_erase_page();
        if (!erase_status) {
            return false;
        }
        next_free_slot = 0;
    }

    // Write the entry to the next free slot
    bool write_status = journal_write_slot(next_free_slot, data);
    if (!write_status) {
        return false;
    }

    // Update RAM copy and advance the slot pointer
    journal_current.total_km = data->total_km;
    journal_current.trip_km  = data->trip_km;
    next_free_slot++;

    return true;
}

// Get pointer to the current usage journal data in RAM
const cmc_usage_journal_data_t* cmc_usage_journal_get(void) {
    return &journal_current;
}

// Reset trip counter and save immediately
bool cmc_usage_journal_reset_trip(void) {
    cmc_usage_journal_data_t updated = {
        .total_km = journal_current.total_km,
        .trip_km  = 0
    };
    return cmc_usage_journal_save(&updated);
}
