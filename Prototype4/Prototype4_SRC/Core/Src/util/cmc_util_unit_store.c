/**
  *********************************************************************************************
  * @file      cmc_util_unit_store.c
  * @brief     Unit store — persistent flash storage for static unit-specific data
  *            Simple erase-and-write approach (no rolling log) since data changes very rarely.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_unit_store.h"
#include "stm32g4xx_hal.h"
#include <string.h>

// Compile-time check: struct must be exactly one double-word for a single flash write
_Static_assert(sizeof(cmc_unit_store_t) == sizeof(uint64_t),
    "cmc_unit_store_t must be exactly 8 bytes (one flash double-word)");

// Pointer to the flash page (memory-mapped, read directly)
static const cmc_unit_store_t* flash_unit_store = (const cmc_unit_store_t*)CMC_UNIT_STORE_FLASH_ADDR;

// RAM copy of the current unit store data
static cmc_unit_store_t unit_store_current;
static bool unit_store_valid = false;

// Helper: compute flash page number from address
static uint32_t unit_store_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Helper: erase the unit store flash page
static bool unit_store_erase_page(void) {
    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    FLASH_EraseInitTypeDef erase_init = {0};
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_1;
    erase_init.Page      = unit_store_get_page(CMC_UNIT_STORE_FLASH_ADDR);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Helper: write the struct to the start of the page
static bool unit_store_write(const cmc_unit_store_t* data) {
    uint64_t dword;
    const uint32_t* src = (const uint32_t*)data;
    uint32_t* dst = (uint32_t*)&dword;
    dst[0] = src[0];
    dst[1] = src[1];

    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, CMC_UNIT_STORE_FLASH_ADDR, dword);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Init: read flash and load into RAM if valid
bool cmc_unit_store_init(void) {
    if (flash_unit_store->marker == CMC_UNIT_STORE_MARKER) {
        memcpy(&unit_store_current, (const void*)flash_unit_store, sizeof(cmc_unit_store_t));
        unit_store_valid = true;
    } else {
        memset(&unit_store_current, 0, sizeof(cmc_unit_store_t));
        unit_store_valid = false;
    }
    return unit_store_valid;
}

// Save: erase page then write new data
bool cmc_unit_store_save(const cmc_unit_store_t* data) {
    if (!unit_store_erase_page()) {
        return false;
    }
    if (!unit_store_write(data)) {
        return false;
    }
    // Update RAM copy
    memcpy(&unit_store_current, data, sizeof(cmc_unit_store_t));
    unit_store_valid = (data->marker == CMC_UNIT_STORE_MARKER);
    return true;
}

// Get pointer to RAM copy
const cmc_unit_store_t* cmc_unit_store_get(void) {
    return unit_store_valid ? &unit_store_current : NULL;
}

// Check validity
bool cmc_unit_store_is_valid(void) {
    return unit_store_valid;
}
