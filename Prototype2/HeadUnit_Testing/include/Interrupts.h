#ifndef Interrupts_h
#define Interrupts_h

// Interrupt Service Routine, read hall sensor and keep track of time spent per wheel rotation
void IRAM_ATTR readHallSensor() {
    unsigned long currentTime = micros();
    unsigned long pulseIntervalMicros = currentTime - data.lastPulseTimeMicros;
    // Ignore very short intervals (debounce)
    if (pulseIntervalMicros < 1000) { // Ignore intervals shorter than 1ms
        return;
    }
    data.lastPulseTimeMicros = currentTime;
    // Add new speed reading to the array
    data.pulseReadings[data.currentPulseIndex] = pulseIntervalMicros;
    data.currentPulseIndex = (data.currentPulseIndex + 1) % data.pulseReadingsCount;
    // Set flag that wheel rotation was detected + count rotation
    data.wheelRotaionDetected = true;
    data.wheelRotations++;
};

void interruptsInit() {
    
    // Pin for hall sensor input
    static const int hallSensorPin = 21; // connect D0 from hall sensor to this pin
    // pinmode for hall sensor
    pinMode(hallSensorPin, INPUT_PULLUP);
    // Attach interrupt to hall sensor pin
    attachInterrupt(digitalPinToInterrupt(hallSensorPin), readHallSensor, RISING);

};

#endif