#ifndef RpmSensor_h
#define RpmSensor_h

class RpmSensor {

    private:
        
    public:
    
        // Method for reading analog value from hall sensor to calculate speed
        void checkForRotations(Data& data) {
            if (data.rpmRotationDetected) {
                // Rpm rotation detected, disable interrupts while processing to avoid conflicts
                noInterrupts();
                data.rpmRotationDetected = false;
                float sum = 0.0;
                int validReadings = 0;
                for (int i = 0; i < data.pulseRpmReadingsCount; i++) {
                    if (data.pulseRpmReadings[i] > 0) { // Only average non-zero readings
                        sum += data.pulseRpmReadings[i];
                        validReadings++;
                    }
                }
                interrupts();
                // Calculate average pulse interval
                float avgReadings = 0.0;
                if (validReadings > 0) {
                    avgReadings = sum / (float)validReadings;
                } 
                // Calculate rpm
                data.engineRpm = data.rpmMicrosToMinutes * data.rpmFactor / avgReadings;
            }
            // Check if timeout has occurred to set speed to zero
            else if (data.engineRpm > 0.0 && (data.currentMs - (data.lastPulseRpmTimeMicros / 1000) > data.zeroRpmTimeoutMs)) {
                // Reset speed and readings
                data.engineRpm = 0.0;
                data.rpmRotationDetected = false;
                for (int i = 0; i < data.pulseRpmReadingsCount; i++) {
                    data.pulseRpmReadings[i] = 0;
                }
            }
        };

};


#endif