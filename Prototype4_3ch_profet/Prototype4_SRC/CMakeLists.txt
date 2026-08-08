cmake_minimum_required(VERSION 3.22)
# This file is generated only once, and is not re-generated if converter is called multiple times.
# User is free to modify the file as much as necessary

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Prototype4_SmartSwitch_V1)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # app
    ./Core/Src/app/cmc_app_logic.c
    ./Core/Src/app/cmc_app_state_updater.c
    # can
    ./Core/Src/can/cmc_can_manager.c
    ./Core/Src/can/cmc_can_message.c
    # config
    ./Core/Src/config/cmc_config_defaults.c
    ./Core/Src/config/cmc_config_hw_mapping.c
    ./Core/Src/config/cmc_config_manager.c
    ./Core/Src/config/cmc_config_unit_info.c 
    # features
    ./Core/Src/feature/cmc_feature_brake_light.c
    ./Core/Src/feature/cmc_feature_direction_indicator.c
    ./Core/Src/feature/cmc_feature_horn.c
    ./Core/Src/feature/cmc_feature_ignition.c
    ./Core/Src/feature/cmc_feature_light.c
    ./Core/Src/feature/cmc_feature_neutral.c
    ./Core/Src/feature/cmc_feature_oil_pressure.c
    ./Core/Src/feature/cmc_feature_starter.c
    ./Core/Src/feature/cmc_feature_channel_info.c
    # features manager and output
    ./Core/Src/feature/cmc_features_manager.c
    ./Core/Src/feature/cmc_features_output.c
    # input
    ./Core/Src/input/cmc_input_scanner.c
    # util
    ./Core/Src/util/cmc_util_crc.c
    ./Core/Src/util/cmc_util_onboard_led.c
    ./Core/Src/util/cmc_util_switch_driver.c
    ./Core/Src/util/cmc_util_usage_journal.c
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
# Post-build: report size of cmc_config_t relative to the 2KB flash config page
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DNM=${CMAKE_NM}
        -DELF=$<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/print_config_size.cmake
    VERBATIM
    COMMENT "Checking cmc_config_t flash config size"
)