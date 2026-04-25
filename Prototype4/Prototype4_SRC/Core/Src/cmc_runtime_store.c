/**
  *********************************************************************************************
  * @file      cmc_runtime_store.c
  * @brief     Runtime data storage using rolling flash log for frequently updated values
  *            Appends 8-byte entries sequentially within a 2KB flash page (256 slots).
  *            Only erases the page when all slots are used, extending flash endurance to ~2.56M writes.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "cmc_runtime_store.h"
#include "stm32g4xx_hal.h"

// Compile-time check: entry must be exactly one double-word for single flash write
_Static_assert(sizeof(cmc_runtime_data_t) == sizeof(uint64_t), "cmc_runtime_data_t must be exactly 8 bytes (one flash double-word)");

// Pointer to the runtime flash page (memory-mapped, read directly)
static const cmc_runtime_data_t* runtime_page = (const cmc_runtime_data_t*)CMC_RUNTIME_FLASH_ADDR;

// RAM copy of the current runtime data
static cmc_runtime_data_t cmc_runtime_current = {0};

// Index of the next free slot in the flash page (0 to CMC_RUNTIME_MAX_ENTRIES)
static uint32_t next_free_slot = 0;

// Erased flash reads as 0xFFFFFFFF, so an erased entry has total_km == 0xFFFFFFFF
#define CMC_RUNTIME_ERASED_MARKER  0xFFFFFFFFU

// Helper: compute flash page number from address
static uint32_t runtime_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Helper: erase the runtime flash page
static cmc_config_status_t runtime_erase_page(void) {
    HAL_StatusTypeDef hal_status;

    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    FLASH_EraseInitTypeDef erase_init = {0};
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_1;
    erase_init.Page      = runtime_get_page(CMC_RUNTIME_FLASH_ADDR);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK) ? CMC_CONFIG_STATUS_SUCCESS : CMC_CONFIG_STATUS_ERROR;
}

// Helper: write one entry to a specific slot
static cmc_config_status_t runtime_write_slot(uint32_t slot, const cmc_runtime_data_t* data) {
    HAL_StatusTypeDef hal_status;

    uint32_t dest_addr = CMC_RUNTIME_FLASH_ADDR + (slot * sizeof(cmc_runtime_data_t));
    uint64_t dword;
    // Copy the struct into a uint64_t for the double-word flash write
    const uint32_t* src = (const uint32_t*)data;
    uint32_t* dst = (uint32_t*)&dword;
    dst[0] = src[0];
    dst[1] = src[1];

    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, dest_addr, dword);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK) ? CMC_CONFIG_STATUS_SUCCESS : CMC_CONFIG_STATUS_ERROR;
}

// Init: scan flash page to find the latest valid entry and the next free slot
cmc_config_status_t cmc_runtime_store_init(void) {

    // Scan forward to find the first erased slot
    next_free_slot = 0;
    for (uint32_t i = 0; i < CMC_RUNTIME_MAX_ENTRIES; i++) {
        if (runtime_page[i].total_km == CMC_RUNTIME_ERASED_MARKER) {
            break;
        }
        next_free_slot = i + 1;
    }

    if (next_free_slot > 0) {
        // Load the last written entry into RAM
        cmc_runtime_current.total_km = runtime_page[next_free_slot - 1].total_km;
        cmc_runtime_current.trip_km  = runtime_page[next_free_slot - 1].trip_km;
    } else {
        // Page is fully erased (fresh chip or after reset), start at zero
        cmc_runtime_current.total_km = 0;
        cmc_runtime_current.trip_km  = 0;
    }

    return CMC_CONFIG_STATUS_SUCCESS;
}

// Save runtime data to the next available flash slot
cmc_config_status_t cmc_runtime_store_save(const cmc_runtime_data_t* data) {
    if (data == NULL) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    // If the page is full, erase it and start from slot 0
    if (next_free_slot >= CMC_RUNTIME_MAX_ENTRIES) {
        cmc_config_status_t erase_status = runtime_erase_page();
        if (erase_status != CMC_CONFIG_STATUS_SUCCESS) {
            return CMC_CONFIG_STATUS_ERROR;
        }
        next_free_slot = 0;
    }

    // Write the entry to the next free slot
    cmc_config_status_t write_status = runtime_write_slot(next_free_slot, data);
    if (write_status != CMC_CONFIG_STATUS_SUCCESS) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    // Update RAM copy and advance the slot pointer
    cmc_runtime_current.total_km = data->total_km;
    cmc_runtime_current.trip_km  = data->trip_km;
    next_free_slot++;

    return CMC_CONFIG_STATUS_SUCCESS;
}

// Get pointer to the current runtime data in RAM
const cmc_runtime_data_t* cmc_runtime_store_get(void) {
    return &cmc_runtime_current;
}

// Reset trip counter and save immediately
cmc_config_status_t cmc_runtime_store_reset_trip(void) {
    cmc_runtime_data_t updated = {
        .total_km = cmc_runtime_current.total_km,
        .trip_km  = 0
    };
    return cmc_runtime_store_save(&updated);
}
