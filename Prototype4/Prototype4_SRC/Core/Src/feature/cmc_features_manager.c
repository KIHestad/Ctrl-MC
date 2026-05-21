/**
  *********************************************************************************************
  * @file      cmc_features_manager.h
  * @brief     Inits and processes all features based on the configuration, called from the main app logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#include "feature/cmc_features_manager.h"
#include "feature/cmc_feature_ignition.h"
#include "feature/cmc_feature_starter.h"
#include "feature/cmc_feature_horn.h"
#include "feature/cmc_feature_direction_indicator.h"
#include "feature/cmc_feature_light.h"
#include "feature/cmc_feature_brake_light.h"
#include "feature/cmc_feature_neutral.h"
#include "feature/cmc_feature_oil_pressure.h"
#include "feature/cmc_features_output.h"

void cmc_features_init(void) {
    // Clear any latched PROFET fault states before feature inits run
    cmc_features_out_init_all();
    // Initialize all features based on the configuration, call the init function for each feature module
    cmc_feature_direction_indicator_init();
    cmc_feature_horn_init();
    cmc_feature_ignition_init(); // Must run before any feature that depends on ignition_on
    cmc_feature_starter_init();
    cmc_feature_light_init();
    cmc_feature_brake_light_init();
    cmc_feature_neutral_init();
    cmc_feature_oil_pressure_init();
}

void cmc_features_process(void) {
    // Process all features based on the configuration, call the process function for each feature module
    cmc_feature_direction_indicator_process();
    cmc_feature_horn_process();
    cmc_feature_ignition_process(); // Must run before any feature that reads ignition_on
    cmc_feature_starter_process();
    cmc_feature_light_process();
    cmc_feature_brake_light_process();
    cmc_feature_neutral_process();
    cmc_feature_oil_pressure_process();
}