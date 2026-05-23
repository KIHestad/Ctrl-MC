# Create a new features in separate files following this pattern:
- Header in `Core/Inc/cs_<name>.h`
- Source in `Core/Src/cs_<name>.c`
- Use snake_case naming with `cs_` prefix for all feature-specific identifiers (functions, types, variables).

# Instructions for implementing the feature logic:
Create a `cs_<name>_init()` function if suitable for the feature to be implemented to be called from the main initialization sequence in `main.c` withinn /* USER CODE BEGIN 2 */ section
Create a `cs_<name>_process()` function that is called from the main loop in `main.c` within the /* USER CODE BEGIN 3 */ section to execute the feature's main logic.

Remember to add new c-files to the `CMakeLists.txt` at root level in the appropriate sections to ensure they are compiled and linked correctly. 


