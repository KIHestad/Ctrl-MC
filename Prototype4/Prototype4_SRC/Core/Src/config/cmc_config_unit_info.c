/**
  *********************************************************************************************
  * @file      cmc_config_unit_info.c
  * @brief     Unit info — persistent flash storage for static unit-specific data
  *            Simple erase-and-write approach (no rolling log) since data changes very rarely.
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_unit_info.h"
#include "app/cmc_app_state.h"
#include "util/cmc_util_onboard_led.h"
#include "util/cmc_util_crc.h"
#include "stm32g4xx_hal.h"
#include <stdbool.h>

// The global active unit info, loaded from flash at startup
cmc_config_unit_info_t cmc_config_unit_info; 

// Pointer to the flash page (memory-mapped, read directly)
static const cmc_config_unit_info_t* flash_unit_info = (const cmc_config_unit_info_t*)CMC_CONFIG_UNIT_INFO_FLASH_ADDR;

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
    erase_init.Page      = unit_info_get_page(CMC_CONFIG_UNIT_INFO_FLASH_ADDR);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);

    HAL_FLASH_Lock();

    return (hal_status == HAL_OK);
}

// Helper: write the struct to the start of the page
static bool unit_info_write(const cmc_config_unit_info_t* data) {
    HAL_StatusTypeDef hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) return false;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    const uint64_t* src = (const uint64_t*)data;
    const size_t dwords = sizeof(cmc_config_unit_info_t) / 8U;

    for (size_t i = 0; i < dwords; i++) {
        hal_status = HAL_FLASH_Program(
            FLASH_TYPEPROGRAM_DOUBLEWORD,
            CMC_CONFIG_UNIT_INFO_FLASH_ADDR + (i * 8U),
            src[i]);
        if (hal_status != HAL_OK) break;
    }

    HAL_FLASH_Lock();
    return (hal_status == HAL_OK);
}


// Helper: erase page then write new data
static bool cmc_config_unit_info_save(void) {
    // Full page save since this is to be updated very rare, minimal flash wear, no need for a rolling log or multiple slots
    // Check valid unit_id is set before saving
    if (cmc_config_unit_info.unit_id < 1 || cmc_config_unit_info.unit_id > CMC_CONFIG_MAX_SUPPORTED_IO_UNITS) {
        cmc_config_unit_info = (cmc_config_unit_info_t){0};
        return false; 
    }
    // Try erase flash
    if (!unit_info_erase_page()) {
        cmc_config_unit_info = (cmc_config_unit_info_t){0};
        return false;
    }
    // Try write new data to flash
    cmc_config_unit_info_t data_to_write = cmc_config_unit_info;
    data_to_write.signature = CMC_CONFIG_UNIT_INFO_SIGNATURE;
    data_to_write.crc       = CMC_CRC_CALCULATE_PAYLOAD(&data_to_write);   // covers subsequent data after signature and crc fields = unit_id and more if added
    if (!unit_info_write(&data_to_write)) {
        cmc_config_unit_info = (cmc_config_unit_info_t){0};
        return false;
    }
    // Done
    return true;   
}

// Init: read flash and load into app_state.unit_info if valid
void cmc_config_unit_info_init(void) {

    // Check signature in flash portion where unit info is stored, if not valid, wait for user to set it via button press before proceeding with the rest of initialization
    if (flash_unit_info->signature != CMC_CONFIG_UNIT_INFO_SIGNATURE) {
        // Not found valid CRC, blink LED and wait for user to set it via button presse before proceeding with the rest of initialization
        cmc_onboard_led_blink(50, 950); 
        cmc_config_unit_info = (cmc_config_unit_info_t){0};
        bool unit_id_set = false;
        while (!unit_id_set) {
            // The input number (input[0] = input nr 1) will be taken as unit id, so user can set unit id by pressing the corresponding button during startup
            // Check buttons 1 to CMC_CONFIG_MAX_SUPPORTED_IO_UNITS to allow user to set unit id via button presses
            for (uint8_t i = 0; i < CMC_CONFIG_MAX_SUPPORTED_IO_UNITS; i++) {
                if (!unit_id_set && HAL_GPIO_ReadPin(cmc_config_hw_digital_in_mapping[i].port,cmc_config_hw_digital_in_mapping[i].pin) == GPIO_PIN_RESET) {
                    // If button is pressed, set unit id to button index + 1 (to make it 1-based)
                    cmc_config_unit_info.unit_id = i + 1;
                    // Add correct signature to indicated valid unit info and save to flash
                    cmc_config_unit_info.signature = CMC_CONFIG_UNIT_INFO_SIGNATURE;
                    // save to flash now
                    bool save_success = cmc_config_unit_info_save();
                    if (!save_success) {
                        cmc_app_state.system.status = CMC_APP_STATE_STATUS_UNIT_INFO_SAVE_ERROR;
                    }
                    unit_id_set = true;
                    break;                    
                }
            }
            // Update LED state to keep blinking while waiting for user input
            cmc_onboard_led_process(); 
        }
    }
        
    // Go back to standard init led blinking pattern after unit info is valid
    cmc_onboard_led_startup(); 

    // If save new unit info to flash failed, the state will be set to an error state
    if (cmc_app_state.system.status != CMC_APP_STATE_STATUS_SUCCESS) {
        return;
    }
    
    // Read unit info from flash and load into RAM including _pad, so CRC verify is consistent
    cmc_config_unit_info = *flash_unit_info;

    // Verify CRC over payload (everything after the crc field)
    if (CMC_CRC_CALCULATE_PAYLOAD(&cmc_config_unit_info) != cmc_config_unit_info.crc) {
        cmc_app_state.system.status = CMC_APP_STATE_STATUS_UNIT_INFO_CRC_INVALID;
        return;
    }
    
}



