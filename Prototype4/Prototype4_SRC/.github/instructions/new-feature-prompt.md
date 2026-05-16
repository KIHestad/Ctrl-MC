Create a new feature module following the Ctrl-MC pattern:
- Header in `Core/Inc/feature/cmc_feature_<name>.h`
- Source in `Core/Src/feature/cmc_feature_<name>.c`
- Follow naming rules in `_documents/2_Naming_convention.md`
- Register in `cmc_features_manager`

Create a cmc_feature_<name>_init() function that initializes the feature and is called from cmc_features_manager during system initialization. The feature should subscribe to relevant state changes in cmc_app_state and implement the necessary logic to control outputs or perform actions based on the state of the system. Use cmc_features_output functions to control physical outputs as needed.

Create a cmc_feature_<name>_process() function that is called from the main loop in cmc_features_manager. This function should contain the main logic for the feature, checking the relevant state and controlling outputs or performing actions accordingly.

Add into cmc_app_state_updater.c logic to update the app state and send over canbus the appropriate messages  based on input states or other conditions that are relevant for the new feature. This may involve adding new fields to the cmc_app_state struct to track the necessary state for the feature.

