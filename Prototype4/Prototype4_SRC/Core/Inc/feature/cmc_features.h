/**
  *********************************************************************************************
  * @file      cmc_features.h
  * @brief     Inits and processes all features based on the configuration, called from the main app logic
  * @attention This is part of the Ctrl-MC system: https://github.com/KIHestad/Ctrl-MC
  * @copyright KI Hestad, Complicated Productions
  *********************************************************************************************
  */

#ifndef CMC_FEATURES_H_
#define CMC_FEATURES_H_


extern void cmc_features_init(void); // Call this in the main initialization to set up the feature state based on the configuration
extern void cmc_features_process(void); // Call this in the main processing loop to handle feature logic

#endif /* CMC_FEATURES_H_ */