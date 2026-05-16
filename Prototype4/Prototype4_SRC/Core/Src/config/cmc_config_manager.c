/**
  *********************************************************************************************
  * @file      cmc_config_manager.c
  * @brief     Configuration manager for handling loading, validating, and saving system configuration
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_manager.h"
#include "config/cmc_config_defaults.h" 
#include "app/cmc_app_logic.h"
#include "config/cmc_config_type.h"
#include "util/cmc_util_onboard_led.h"
#include "util/cmc_util_crc.h"
#include "stm32g4xx_hal.h"              
#include <string.h>                     

// The global configuration variable that holds the active configuration for the system, loaded at startup from flash or defaults
cmc_config_t cmc_config;
// Pointer to the config for this unit, set at init based on unit id to point to the correct section of the config.io_unit array
const cmc_config_io_unit_t* cmc_config_this_unit = NULL;

// Define where the Flash storage starts (The "Archive")
static const cmc_config_t* flash_config = (cmc_config_t*)0x0801F800; // Last 2KB of Flash for config storage

// Helper: compute flash page number from address
static uint32_t flash_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Helper: check that flash holds a valid signature AND a matching CRC
static cmc_app_state_status_t check_flash_config(void) {
    if (flash_config->signature != CMC_CONFIG_SIGNATURE) {
        return CMC_APP_STATE_STATUS_CONFIG_FLASH_SIGNATURE_INVALID;
    }
    if (CMC_CRC_CALCULATE_PAYLOAD(flash_config) != flash_config->crc) {
        return CMC_APP_STATE_STATUS_CONFIG_FLASH_CRC_INVALID;
    }
    return CMC_APP_STATE_STATUS_SUCCESS;
}

// Init the configuration manager, called at startup to load and validate the configuration
void cmc_config_manager_init(void) {

    // Set config status based on config in flash is valid
    cmc_app_state.status = check_flash_config(); 
    
    // If flash config is not valid, attempt to fix it
    // TODO: Should check over CANBUS if valid config can be fetched, but for now use local demo defaults and save to flash
    if (cmc_app_state.status != CMC_APP_STATE_STATUS_SUCCESS) {
        cmc_app_state.status = cmc_config_manager_save_to_flash(&cmc_config_default_for_demo);
        // If save default config to flash succeeded, check once again if flash config is valid now (should be if save succeeded)
        cmc_app_state.status = check_flash_config(); 
    }

    // If config is found valid in flash, load it into the active config struct in RAM for use by the system
    if (cmc_app_state.status == CMC_APP_STATE_STATUS_SUCCESS) {
        cmc_app_state.status = cmc_config_manager_load_from_flash(&cmc_config);
    }
    
    // If errors detected, set LED to fast blink to indicate error state
    if (cmc_app_state.status != CMC_APP_STATE_STATUS_SUCCESS) {
        cmc_onboard_led_blink_interval(cmc_app_state.status, 1000); // Config save failed, indicate error with fast blinking
    }

    // Done
    return;    
}

// Save configuration struct to flash using 64-bit double-word programming (STM32G4 requirement)
cmc_app_state_status_t cmc_config_manager_save_to_flash(const cmc_config_t* new_config) {
    if (new_config == NULL) {
        return CMC_APP_STATE_STATUS_CONFIG_SAVE_TO_FLASH_ERROR;
    }

    // Local copy so we can stamp signature + CRC without mutating the caller's struct
    cmc_config_t to_write = *new_config;
    to_write.signature = CMC_CONFIG_SIGNATURE;
    to_write.crc       = CMC_CRC_CALCULATE_PAYLOAD(&to_write);

    HAL_StatusTypeDef hal_status;

    // Unlock flash
    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return CMC_APP_STATE_STATUS_CONFIG_SAVE_TO_FLASH_ERROR;
    }

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    // Erase the config page
    FLASH_EraseInitTypeDef erase_init = {0};
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_1;
    erase_init.Page      = flash_get_page((uint32_t)flash_config);
    erase_init.NbPages   = 1;
    uint32_t page_error  = 0;

    hal_status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    if (hal_status != HAL_OK) {
        HAL_FLASH_Lock();
        return CMC_APP_STATE_STATUS_CONFIG_SAVE_TO_FLASH_ERROR;
    }

    // Program config as 64-bit double-words from the stamped local copy
    const uint64_t* src = (const uint64_t*)&to_write;
    uint32_t dest_addr  = (uint32_t)flash_config;
    const size_t dword_count = sizeof(cmc_config_t) / sizeof(uint64_t);

    for (size_t i = 0; i < dword_count; i++) {
        hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, dest_addr, src[i]);
        if (hal_status != HAL_OK) {
            HAL_FLASH_Lock();
            return CMC_APP_STATE_STATUS_CONFIG_SAVE_TO_FLASH_ERROR;
        }
        dest_addr += sizeof(uint64_t);
    }

    HAL_FLASH_Lock();
    return CMC_APP_STATE_STATUS_SUCCESS;
}

// Load configuration from flash into RAM using 32-bit word copy for safe aligned access
cmc_app_state_status_t cmc_config_manager_load_from_flash(cmc_config_t* target) {
    if (target == NULL) {
        return CMC_APP_STATE_STATUS_CONFIG_LOAD_FROM_FLASH_ERROR;
    }

    // Verify flash contains a valid config before copying
    if (flash_config->signature != CMC_CONFIG_SIGNATURE) {
        return CMC_APP_STATE_STATUS_CONFIG_FLASH_SIGNATURE_INVALID;
    }

    // Copy from memory-mapped flash to RAM, word-by-word for safe aligned access
    const uint32_t* src = (const uint32_t*)flash_config;
    uint32_t* dst       = (uint32_t*)target;
    const size_t word_count = sizeof(cmc_config_t) / sizeof(uint32_t);

    for (size_t i = 0; i < word_count; i++) {
        dst[i] = src[i];
    }

    // Verify the copy succeeded
    if (target->signature != CMC_CONFIG_SIGNATURE) {
        return CMC_APP_STATE_STATUS_CONFIG_RAM_SIGNATURE_INVALID;
    }

    // Verify CRC over payload (everything after the crc field)
    if (CMC_CRC_CALCULATE_PAYLOAD(target) != target->crc) {
        return CMC_APP_STATE_STATUS_CONFIG_FLASH_CRC_INVALID;
    }

    return CMC_APP_STATE_STATUS_SUCCESS;
}

