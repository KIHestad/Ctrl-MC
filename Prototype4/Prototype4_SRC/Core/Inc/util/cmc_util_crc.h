/**
  *********************************************************************************************
  * @file      cmc_util_crc.h
  * @brief     CRC calculation utility using STM32 hardware peripheral
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_UTIL_CRC_H_
#define CMC_UTIL_CRC_H_

#include <stdint.h>
#include <stddef.h>

// Compute CRC-32 over a byte buffer. Length must be a multiple of 4 bytes.
// Uses the STM32 hardware CRC peripheral (configured via CubeMX, default polynomial 0x04C11DB7).
uint32_t cmc_util_crc_calculate(const void* data, size_t length_bytes);

// Compute CRC over the bytes of `*ptr` that follow the `crc` field. (ptr = pointer)
// Assumes the struct contains a `uint32_t crc;` member.
#define CMC_UTIL_CRC_CALCULATE_PAYLOAD(ptr)                                           \
    cmc_util_crc_calculate(                                                           \
        (const uint8_t*)(ptr) + offsetof(__typeof__(*(ptr)), crc) + sizeof(uint32_t), \
        sizeof(*(ptr)) - offsetof(__typeof__(*(ptr)), crc) - sizeof(uint32_t)         \
    )

#endif /* CMC_UTIL_CRC_H_ */