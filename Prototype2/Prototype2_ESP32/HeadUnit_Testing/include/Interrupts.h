#ifndef Interrupts_h
#define Interrupts_h

// Interrupt Service Routine, read wheel sensor and keep track of time spent per wheel rotation
void IRAM_ATTR readWheelSensor() {
    unsigned long currentTime = micros();
    unsigned long pulseIntervalMicros = currentTime - data.lastPulseWheelTimeMicros;
    // Ignore very short intervals (debounce)
    if (pulseIntervalMicros < 1000) { // Ignore intervals shorter than 1ms
        return;
    }
    data.lastPulseWheelTimeMicros = currentTime;
    // Add new speed reading to the array
    data.pulseWheelReadings[data.currentPulseWheelIndex] = pulseIntervalMicros;
    data.currentPulseWheelIndex = (data.currentPulseWheelIndex + 1) % data.pulseWheelReadingsCount;
    // Set flag that wheel rotation was detected + count rotation
    data.wheelRotaionDetected = true;
    data.wheelRotations++;
};

// Interrupt Service Routine, read hall sensor and keep track of time spent per rpm rotation
void IRAM_ATTR readRpmSensor() {
    unsigned long currentTime = micros();
    unsigned long pulseIntervalMicros = currentTime - data.lastPulseRpmTimeMicros;
    // Ignore very short intervals (debounce)
    if (pulseIntervalMicros < 1000) { // Ignore intervals shorter than 1ms
        return;
    }
    data.lastPulseRpmTimeMicros = currentTime;
    // Add new speed reading to the array
    data.pulseRpmReadings[data.currentPulseRpmIndex] = pulseIntervalMicros;
    data.currentPulseRpmIndex = (data.currentPulseRpmIndex + 1) % data.pulseRpmReadingsCount;
    // Set flag that wheel rotation was detected + count rotation
    data.rpmRotationDetected = true;
};

void interruptsInit() {
    
    // Attach interrupt to wheel sensor pin
    pinMode(data.pinWheelSensor, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(data.pinWheelSensor), readWheelSensor, RISING);

    // Attach interrupt to rpm sensor pin
    pinMode(data.pinRpmSensor, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(data.pinRpmSensor), readRpmSensor, RISING);

};

#endif