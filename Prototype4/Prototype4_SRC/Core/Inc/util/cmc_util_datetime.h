#ifndef CMC_UTIL_DATETIME_H
#define CMC_UTIL_DATETIME_H

#include <stdint.h>

/**
 * Ctrl-MC custom epoch offset (Unix timestamp 1,750,000,000).
 * Corresponds to 2025-06-15T07:33:20 UTC.
 * Valid range: mid-2025 to ~2161.
 */
#define CMC_EPOCH_OFFSET 1750000000UL

static inline uint32_t cmc_datetime_from_unix(uint32_t unix_sec)
{
    return unix_sec - CMC_EPOCH_OFFSET;
}

static inline uint32_t cmc_datetime_to_unix(uint32_t cmc_datetime)
{
    return cmc_datetime + CMC_EPOCH_OFFSET;
}

#endif /* CMC_UTIL_DATETIME_H */
