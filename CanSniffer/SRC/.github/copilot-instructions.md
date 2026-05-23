# CanSniffer Instructions

## Project Scope
- This project is a firmware codebase for a canbus message reader (sniffer) to transfer messages to a PC over USB
- The canbus messages uses either CAN 2.0 or FD CAN protocols
- The messages over canbus are decoded using a DBC file
- The PC used USB and standard software as SavvyCAN to read the messages, the software is loaded with the correct DBC file to decode the messages
- MCU hardware target: STM32G4 family (STM32G431xx)
- MCU profile: Cortex-M4
- MCU hardware single-precision: use FPU.
- Firmware style: bare-metal, no RTOS.
- Build system: CMake.
- Repository: https://github.com/KIHestad/Ctrl-MC/CanSniffer

## 1 Naming Conventions
- All project-owned names must use `snake_case` style.
- All project-owned names must have `cs_` prefix.

## 2 Coding Rules
- Never rename vendor/library symbols (`HAL_*`, `LL_*`, CMSIS/ST identifiers).
- No dynamic allocation (`malloc/new`) in runtime-critical paths.
- Keep ISRs short, deterministic, and non-blocking.

## 3 Secondary Guidelines 
The following guidelines are not strict rules but should be followed when practical and unless explicitly overridden in the task description provided alongside this prompt.

### 3.1 Code Structure and Embedded Constraints
- Primary firmware language is C11; use STM32 HAL/LL and CMSIS conventions.
- C++ may only be used in modules where it is already implemented, or when explicitly requested in the task description provided alongside this prompt.
  - Never use dynamic allocation in C++ modules; prefer stack-based or statically allocated patterns.
  - Avoid exceptions and RTTI unless explicitly required by existing module design.
- Keep logic modular.
- Isolate hardware abstraction from core system logic.
- Keep modules cohesive and focused on a single responsibility.
- Prefer internal linkage (`static`) for private functions and data.
- Prioritize low-latency and hardware resource efficiency (RAM/flash/CPU).
- Prefer fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`, etc.).

### 3.2 CMake and Tooling
- Preserve existing CMake target structure unless asked to change it.
- Keep IntelliSense-friendly compile database usage (`compile_commands.json`) intact.

### 3.3 Hardware-Specific Constraints
- For compute-heavy control loops, prefer STM32G4 hardware accelerators (CORDIC/FMAC) where practical.
- Ensure the hardware configuration matches the STM32G4 family and the specific STM32G431xx MCU.
- Follow STM32 HAL/LL best practices for peripheral initialization and usage.
