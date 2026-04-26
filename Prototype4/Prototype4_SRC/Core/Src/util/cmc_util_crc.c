/**
  *********************************************************************************************
  * @file      cmc_util_crc.c
  * @brief     CRC calculation utility using STM32 hardware peripheral
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "util/cmc_util_crc.h"
#include "main.h"           

extern CRC_HandleTypeDef hcrc; // Defined in main.c, initialized by CubeMX, configured for CRC-32 with polynomial 0x04C11DB7

uint32_t cmc_util_crc_calculate(const void* data, size_t length_bytes) {
    // Hardware CRC operates on 32-bit words; caller guarantees 4-byte multiple
    return HAL_CRC_Calculate(&hcrc, (uint32_t*)data, length_bytes / 4U);
}