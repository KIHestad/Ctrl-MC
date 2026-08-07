# Before starting check the following:
- If a canbus message is needed for the feature, this needs to be created manually first by the user. The canbus message to use should be specified in the user's prompt.
- Only the user is allowed to add canbus messages or signals to existing messages by using cantools to generate the /Core/Inc/can/cmc_can_message.h and /Core/Src/can/cmc_can_message.c files.
- Never modify these generated .c and .h files as part of this feature creation!

# Create a new feature module following the Ctrl-MC pattern:
- Header in `Core/Inc/feature/cmc_feature_<name>.h`
- Source in `Core/Src/feature/cmc_feature_<name>.c`
- Follow naming rules in `_documents/2_Naming_convention.md`
- Register in `cmc_features_manager`

# Instructions for implementing the feature logic:
Create a `cmc_feature_<name>_init()` function that initializes the feature and is called from `cmc_features_manager` during system initialization. The feature subscribes relevant state changes in `cmc_app_state` and implement the necessary logic to control outputs or perform actions based on the state of the system. Use `cmc_features_output` functions to control physical outputs as needed.

Create a `cmc_feature_<name>_process()` function that is called from the main loop in `cmc_features_manager`. This function is the single authoritative resolver for the feature's output state. It implements two independent parallel paths that both execute on every call:

**Path 1 — Switch output:** Read the relevant resolved state from `cmc_app_state`, compare to previous output state, and drive physical switch outputs if anything changed. All output-only features implement only this path.

**Path 2 — Logical state (only for features that compute derived state):** Read multiple fields from `cmc_app_state` (button inputs, CAN-received states, IMU events, alarm state, ignition state, etc.), apply priority and conflict resolution rules, and if the computed logical state has changed, call the appropriate `cmc_app_state_update_<state>()` function in `cmc_app_state_updater.c`. That function writes the resolved state to `cmc_app_state` and broadcasts it over CAN so all units stay in sync. Features never write to `cmc_app_state` directly — they always go through the updater as the write gateway.

Examples of features using only Path 1: horn, ignition output, starter.
Examples of features using both paths: direction indicator (resolves cancel-other/hazard → Path 2, then drives blink outputs → Path 1), alarm (computes alarm active state → Path 2, then drives hazard outputs → Path 1).

Add into `cmc_app_state_updater.c` logic to update the app state and send over canbus the appropriate messages based on input states or other conditions that are relevant for the new feature. This could involve adding new variables to the `cmc_app_state` struct to track the necessary state for the feature. This must be considered carefully to ensure that the app state remains efficient and does not exceed flash storage limits.

If the feature requires configuration parameters, add them as a dedicated struct (e.g. `cmc_feature_<name>_t`) in the feature header, then:
1. Add a field for it inside `cmc_config_t` in `cmc_config_type.h`, alongside the other `feature_*` members.
2. Add `sizeof(cmc_feature_<name>_t)` to the `_padding` expression in the same struct so that the total size of `cmc_config_t` remains a multiple of 8 bytes for flash storage alignment. The padding is calculated as `(8 - (sum of all member sizes) % 8) % 8` — every new member must be included in that sum.
3. Set sensible default values in `cmc_config_defaults.c` under the `cmc_config_default_for_demo` initialiser.

Remember to add new c-files to the `CMakeLists.txt` at root level in the appropriate sections to ensure they are compiled and linked correctly. 


