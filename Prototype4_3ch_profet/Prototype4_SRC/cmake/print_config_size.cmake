# Post-build helper: prints the size of cmc_config (cmc_config_t) from the ELF symbol table.
# Called by add_custom_command with: cmake -DNM=<path> -DELF=<path> -P print_config_size.cmake

execute_process(
    COMMAND ${NM} --print-size --defined-only ${ELF}
    OUTPUT_VARIABLE NM_OUTPUT
    ERROR_QUIET
)

# Match BSS symbol named exactly "cmc_config" (upper or lower-case B)
string(REGEX MATCH "[0-9a-f]+ ([0-9a-f]+) [Bb] cmc_config\n" _match "${NM_OUTPUT}")

if(CMAKE_MATCH_1)
    math(EXPR _bytes "0x${CMAKE_MATCH_1}" OUTPUT_FORMAT DECIMAL)
    math(EXPR _pct   "${_bytes} * 100 / 2048")
    message(STATUS "cmc_config_t: ${_bytes} bytes / 2048 max  (${_pct}% of flash config page)")
else()
    message(WARNING "cmc_config_t: symbol 'cmc_config' not found in ELF")
endif()
