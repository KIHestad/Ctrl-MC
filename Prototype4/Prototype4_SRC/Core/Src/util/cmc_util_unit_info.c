/**
  *********************************************************************************************
  * @file      cmc_util_unit_store.c
  * @brief     Unit store — persistent flash storage for static unit-specific data
  *            Simple erase-and-write approach (no rolling log) since data changes very rarely.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_unit_info.h"
#include "app/cmc_app_state.h"
#include "stm32g4xx_hal.h"

// Compile-time check: struct must be exactly one double-word for a single flash write
_Static_assert(sizeof(cmc_unit_info_t) == sizeof(uint64_t),
    "cmc_unit_info_t must be exactly 8 bytes (one flash double-word)");

// Pointer to the flash page (memory-mapped, read directly)
static const cmc_unit_info_t* flash_unit_info = (const cmc_unit_info_t*)CMC_UNIT_INFO_FLASH_ADDR;

// Helper: compute flash page number from address
static uint32_t unit_info_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Helper: erase the unit store flash page
static bool unit_info_erase_page(void) {
    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    FLASH_EraseInitTypeDef erase_init = {0};
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_1;
    erase_init.Page      = unit_info_get_page(CMC_UNIT_INFO_FLASH_ADDR);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);

    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Helper: write the struct to the start of the page
static bool unit_store_write(const cmc_unit_info_t* data) {
    uint64_t dword;
    const uint32_t* src = (const uint32_t*)data;
    uint32_t* dst = (uint32_t*)&dword;
    dst[0] = src[0];
    dst[1] = src[1];

    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return false;
    }

    // Clear any pending flash error flags before programming
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, CMC_UNIT_INFO_FLASH_ADDR, dword);
    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Init: read flash and load into app_state.unit_info if valid
void cmc_unit_info_init(void) {
    if (flash_unit_info->signature == CMC_UNIT_INFO_SIGNATURE) {
        cmc_app_state.unit_info.signature      = flash_unit_info->signature;
        cmc_app_state.unit_info.unit_id        = flash_unit_info->unit_id;
        cmc_app_state.unit_info._reserved[0]   = 0;
        cmc_app_state.unit_info._reserved[1]   = 0;
        cmc_app_state.unit_info._reserved[2]   = 0;
        cmc_app_state.unit_info_valid = true;
    } else {
        cmc_app_state.unit_info.signature      = 0;
        cmc_app_state.unit_info.unit_id        = 0;
        cmc_app_state.unit_info._reserved[0]   = 0;
        cmc_app_state.unit_info._reserved[1]   = 0;
        cmc_app_state.unit_info._reserved[2]   = 0;
        cmc_app_state.unit_info_valid = false;
    }    
}

// Save: erase page then write new data
void cmc_unit_info_save(const cmc_unit_info_t* data) {
    // Check valid unit_id is set before saving
    if (cmc_app_state.unit_info.unit_id < 1 || cmc_app_state.unit_info.unit_id > CMC_CONFIG_MAX_SUPPORTED_IO_UNITS) {
        cmc_app_state.unit_info.signature = 0;
        cmc_app_state.unit_info_valid = false;
        return; 
    }
    // Try erase flash
    if (!unit_info_erase_page()) {
        cmc_app_state.unit_info.signature = 0;
        cmc_app_state.unit_info_valid = false;
        return;
    }
    // Try write new data to flash
    if (!unit_store_write(data)) {
        cmc_app_state.unit_info.signature = 0;
        cmc_app_state.unit_info_valid = false;
        return;
    }
    // Done
    cmc_app_state.unit_info_valid = true;  
}

