/**
  *********************************************************************************************
  * @file      cmc_features_manager.h
  * @brief     Inits and processes all features based on the configuration, called from the main app logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURES_MANAGER_H_
#define CMC_FEATURES_MANAGER_H_

// Call this in the main initialization to set up the feature state based on the configuration
void cmc_features_init(void); 

// Call this in the main processing loop to handle feature logic
void cmc_features_process(void); 

#endif /* CMC_FEATURES_MANAGER_H_ */