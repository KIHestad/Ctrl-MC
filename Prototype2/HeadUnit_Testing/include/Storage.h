#ifndef Storage_h
#define Storage_h

class Storage {
    
    private:
        static const unsigned int eePromSize = 16; // one float variable takes 4 bytes
        static constexpr float totalCounterStart = 46500.0f; // initial kilometers ran before this device was used

   
    public:

        // Value and EEPROM addresses for where to store the value in EEPROM
        class Prop {
            public:
                float value = 0.0; // value to store
                unsigned int address; // address in EEPROM
        };

        // The actual data to store in flash memory
        class Data {
            public:
                Prop totalCounter; // stores total kilometers
                Prop tripCounter; // stores trip in meters
                Prop fuelTripCounter; // stores trip in km since last refuel
                Prop fuelLevel; // stores fuel level in litres
        };
        
        // Instance of the data
        Data data;

        // Initialize EEPROM and read stored values
        void init() {
            // Set addresses for data
            data.totalCounter.address = 0; // occupies bytes 0,1,2,3
            data.tripCounter.address = 4;  // occupies bytes 4,5,6,7
            data.fuelTripCounter.address = 8; // occupies bytes 8,9,10,11
            data.fuelLevel.address = 12; // occupies bytes 12,13,14,15
            // Initialize EEPROM
            EEPROM.begin(eePromSize);
            // Read stored values
            EEPROM.get(data.totalCounter.address, data.totalCounter.value);
            EEPROM.get(data.tripCounter.address, data.tripCounter.value);
            EEPROM.get(data.fuelTripCounter.address, data.fuelTripCounter.value);
            EEPROM.get(data.fuelLevel.address, data.fuelLevel.value);
            // Validate values
            if (std::isnan(data.totalCounter.value)) data.totalCounter.value = totalCounterStart;
            if (std::isnan(data.tripCounter.value)) data.tripCounter.value = 0.0;
            if (std::isnan(data.fuelTripCounter.value)) data.fuelTripCounter.value = 0.0;
            if (std::isnan(data.fuelLevel.value)) data.fuelLevel.value = 0.0;
            if (data.totalCounter.value < totalCounterStart) data.totalCounter.value = totalCounterStart;
        };

        // Reset trip counter
        void resetTripCounter() {
            data.tripCounter.value = 0.0;
            EEPROM.put(data.tripCounter.address, data.tripCounter.value);
            EEPROM.commit();
        };

        // Reset fuel level and fuel trip counter
        void resetFuelLevel(float litres) {
            data.fuelLevel.value = litres;
            data.fuelTripCounter.value = 0.0;
            EEPROM.put(data.fuelLevel.address, data.fuelLevel.value);
            EEPROM.put(data.fuelTripCounter.address, data.fuelTripCounter.value);
            EEPROM.commit();
        };

        // Save current values to EEPROM
        void save() {
            EEPROM.put(data.totalCounter.address, data.totalCounter.value);
            EEPROM.put(data.tripCounter.address, data.tripCounter.value);
            EEPROM.put(data.fuelLevel.address, data.fuelLevel.value);
            EEPROM.put(data.fuelTripCounter.address, data.fuelTripCounter.value);
            EEPROM.commit();
        };
    
};

#endif