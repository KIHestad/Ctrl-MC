#ifndef WheelSensor_h
#define WheelSensor_h

class WheelSensor {

    private:
        
    public:
    
        // Method for reading analog value from hall sensor to calculate speed
        void checkForRotations(Storage storage, Data& data) {
            bool saveDataToStorage = false; // set flag to save data to flash memory
            if (data.wheelRotaionDetected) {
                // Wheel rotation detected, disable interrupts while processing to avoid conflicts
                noInterrupts();
                data.currentWheelRotations = data.wheelRotations;
                data.wheelRotations = 0;
                data.wheelRotaionDetected = false;
                float sum = 0.0;
                int validReadings = 0;
                for (int i = 0; i < data.pulseReadingsCount; i++) {
                    if (data.pulseReadings[i] > 0) { // Only average non-zero readings
                        sum += data.pulseReadings[i];
                        validReadings++;
                    }
                }
                interrupts();
                // Calculate average pulse interval
                float avgReadings = 0.0;
                if (validReadings > 0) {
                    avgReadings = sum / (float)validReadings;
                } 
                // Calculate speed in km/h
                data.currentSpeed = data.wheelCircumference * data.cmMicrosToKmh / avgReadings;
                // Update trip counter in meters
                float currentWheelRotationsDistance = data.currentWheelRotations * data.wheelCircumference / 100.0; // Convert cm to meters;
                data.sessionCounterToUpdateFlash += currentWheelRotationsDistance; // add meters
                data.sessionCounter += currentWheelRotationsDistance; // add meters
                data.tripCounter += currentWheelRotationsDistance; // add meters
                data.totalCounter += currentWheelRotationsDistance / 1000.0;  // add km
                data.fuelTripCounter += currentWheelRotationsDistance / 1000.0; // add km
                // Set flag to save to flash memory if at least 1 km is recorded since last save
                saveDataToStorage = data.sessionCounterToUpdateFlash > 1000;
            }
            // Check if timeout has occurred to set speed to zero
            else if (data.currentSpeed > 0.0 && (data.currentMs - (data.lastPulseTimeMicros / 1000) > data.zeroSpeedTimeoutMs)) {
                // Reset speed and readings
                data.currentSpeed = 0.0;
                data.wheelRotaionDetected = false;
                for (int i = 0; i < data.pulseReadingsCount; i++) {
                    data.pulseReadings[i] = 0;
                }
                // save to flash memory if speed drops to zero if at least 100m is recorded
                saveDataToStorage = data.sessionCounterToUpdateFlash > 100;
            }
            // Save to storage if needed
            if (saveDataToStorage) {
                storage.data.totalCounter.value += (data.sessionCounterToUpdateFlash / 1000.0);  // add km
                storage.data.tripCounter.value += data.sessionCounterToUpdateFlash; // add meters
                storage.data.fuelTripCounter.value += data.sessionCounterToUpdateFlash; // add km
                storage.save();
                data.sessionCounterToUpdateFlash = 0.0; // reset counter after saving to flash    
            }
        };

};


#endif