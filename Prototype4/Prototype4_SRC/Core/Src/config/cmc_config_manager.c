/**
  *********************************************************************************************
  * @file      cmc_config_manager.c
  * @brief     Configuration manager for handling loading, validating, and saving system configuration
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "config/cmc_config_manager.h"
#include "config/cmc_config_defaults.h" // For demo default configuration
#include "stm32g4xx_hal.h"       // For Flash and CRC access
#include <string.h>              // For memcpy

// Compile-time check: struct must be a multiple of 8 bytes for 64-bit flash double-word programming
_Static_assert(sizeof(cmc_config_t) % 8 == 0, "cmc_config_t size must be a multiple of 8 bytes for flash double-word programming");

// The global configuration variable that holds the active configuration for the system, loaded at startup from flash or defaults
extern cmc_config_t cmc_config;

// Define where the Flash storage starts (The "Archive")
static const cmc_config_t* flash_config = (cmc_config_t*)0x0801F800; // Last 2KB of Flash for config storage

// Helper: compute flash page number from address
static uint32_t flash_get_page(uint32_t address) {
    return (address - FLASH_BASE) / FLASH_PAGE_SIZE;
}

// Init the configuration manager, called at startup to load and validate the configuration
cmc_config_status_t cmc_config_manager_init(void) {
    
    // Check if the config in flash is valid
    if (flash_config->signature != CMC_CONFIG_SIGNATURE) {
        // Signature mismatch, should halt for receiving config over CAN, but for now use local demo defaults
        if (cmc_config_default_for_demo_use) {
            // Copy firmware default from ROM into flash
            cmc_config_status_t save_status = cmc_config_manager_save_to_flash(&cmc_config_default_for_demo);
            if (save_status != CMC_CONFIG_STATUS_SUCCESS) {
                return CMC_CONFIG_STATUS_ERROR; // Failed to save default config to flash, should halt and wait for config over CAN, but for now just return error
            }
        }
    }
    
    // Check if config in flash is still valid
    if (flash_config->signature != CMC_CONFIG_SIGNATURE) {
        return CMC_CONFIG_STATUS_INVALID_FLASH_SIGNATURE; 
    }

    // Load from flash into the active RAM config
    return cmc_config_manager_load_from_flash(&cmc_config);
}

// Save configuration struct to flash using 64-bit double-word programming (STM32G4 requirement)
cmc_config_status_t cmc_config_manager_save_to_flash(const cmc_config_t* new_config) {
    if (new_config == NULL) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    HAL_StatusTypeDef hal_status;

    // Unlock flash
    hal_status = HAL_FLASH_Unlock();
    if (hal_status != HAL_OK) {
        return CMC_CONFIG_STATUS_ERROR;
    }

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
        return CMC_CONFIG_STATUS_ERROR;
    }

    // Program config as 64-bit double-words
    const uint64_t* src = (const uint64_t*)new_config;
    uint32_t dest_addr  = (uint32_t)flash_config;
    const size_t dword_count = sizeof(cmc_config_t) / sizeof(uint64_t);

    for (size_t i = 0; i < dword_count; i++) {
        hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, dest_addr, src[i]);
        if (hal_status != HAL_OK) {
            HAL_FLASH_Lock();
            return CMC_CONFIG_STATUS_ERROR;
        }
        dest_addr += sizeof(uint64_t);
    }

    HAL_FLASH_Lock();
    return CMC_CONFIG_STATUS_SUCCESS;
}

// Load configuration from flash into RAM using 32-bit word copy for safe aligned access
cmc_config_status_t cmc_config_manager_load_from_flash(cmc_config_t* target) {
    if (target == NULL) {
        return CMC_CONFIG_STATUS_ERROR;
    }

    // Verify flash contains a valid config before copying
    if (flash_config->signature != CMC_CONFIG_SIGNATURE) {
        return CMC_CONFIG_STATUS_INVALID_FLASH_SIGNATURE;
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
        return CMC_CONFIG_STATUS_INVALID_RAM_SIGNATURE;
    }

    return CMC_CONFIG_STATUS_SUCCESS;
}

