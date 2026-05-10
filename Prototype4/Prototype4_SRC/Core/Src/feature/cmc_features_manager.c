/**
  *********************************************************************************************
  * @file      cmc_features_manager.h
  * @brief     Inits and processes all features based on the configuration, called from the main app logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "feature/cmc_features_manager.h"
#include "feature/cmc_feature_horn.h"

void cmc_features_init(void) {
    // Initialize all features based on the configuration, call the init function for each feature module
    cmc_feature_horn_init();
}

void cmc_features_process(void) {
    // Process all features based on the configuration, call the process function for each feature module
    cmc_feature_horn_process();
}