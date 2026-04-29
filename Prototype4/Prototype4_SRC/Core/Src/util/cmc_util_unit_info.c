/**
  *********************************************************************************************
  * @file      cmc_util_unit_info.c
  * @brief     Unit info — persistent flash storage for static unit-specific data
  *            Simple erase-and-write approach (no rolling log) since data changes very rarely.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_unit_info.h"
#include "util/cmc_util_crc.h"
#include "app/cmc_app_state.h"
#include "stm32g4xx_hal.h"

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
static bool unit_info_write(const cmc_unit_info_t* data) {
    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) return false;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    const uint64_t* src = (const uint64_t*)data;
    const size_t dwords = sizeof(cmc_unit_info_t) / 8U;

    for (size_t i = 0; i < dwords; i++) {
        hal_status = HAL_FLASH_Program(
            FLASH_TYPEPROGRAM_DOUBLEWORD,
            CMC_UNIT_INFO_FLASH_ADDR + (i * 8U),
            src[i]);
        if (hal_status != HAL_OK) break;
    }

    HAL_FLASH_Lock();
    return (hal_status == HAL_OK);
}

// Init: read flash and load into app_state.unit_info if valid
void cmc_unit_info_init(void) {
    cmc_app_state.system.unit_info_valid = false;

    // Check signature
    if (flash_unit_info->signature != CMC_UNIT_INFO_SIGNATURE) {
        cmc_app_state.system.unit_info = (cmc_unit_info_t){0};
        return;
    }

    // Copy whole struct (including _pad, so CRC verify is consistent)
    cmc_app_state.system.unit_info = *flash_unit_info;

    // Verify CRC over payload (everything after the crc field)
    if (CMC_UTIL_CRC_CALCULATE_PAYLOAD(&cmc_app_state.system.unit_info) != cmc_app_state.system.unit_info.crc) {
        cmc_app_state.system.unit_info = (cmc_unit_info_t){0};
        return;
    }

    cmc_app_state.system.unit_info_valid = true;
}

// Save: erase page then write new data
void cmc_unit_info_save(void) {
    // Full page save since this is to be updated very rare, minimal flash wear, no need for a rolling log or multiple slots
    // Check valid unit_id is set before saving
    if (cmc_app_state.system.unit_info.unit_id < 1 || cmc_app_state.system.unit_info.unit_id > CMC_CONFIG_MAX_SUPPORTED_IO_UNITS) {
        cmc_app_state.system.unit_info = (cmc_unit_info_t){0};
        cmc_app_state.system.unit_info_valid = false;
        return; 
    }
    // Try erase flash
    if (!unit_info_erase_page()) {
        cmc_app_state.system.unit_info = (cmc_unit_info_t){0};
        cmc_app_state.system.unit_info_valid = false;
        return;
    }
    // Try write new data to flash
    cmc_unit_info_t data_to_write = cmc_app_state.system.unit_info;
    data_to_write.signature = CMC_UNIT_INFO_SIGNATURE;
    data_to_write.crc       = CMC_UTIL_CRC_CALCULATE_PAYLOAD(&data_to_write);   // covers subsequent data after signature and crc fields = unit_id and more if added
    if (!unit_info_write(&data_to_write)) {
        cmc_app_state.system.unit_info = (cmc_unit_info_t){0};
        cmc_app_state.system.unit_info_valid = false;
        return;
    }
    // Done
    cmc_app_state.system.unit_info = data_to_write;   // sync RAM with flash
    cmc_app_state.system.unit_info_valid = true;  
}


