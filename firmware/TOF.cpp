#include "TOF.h"

void TOF::begin() {
    if (!lox.begin()) {
        Serial.println(F("Failed to boot VL53L0X"));
    }
    // Set to high speed mode for flight stability
    lox.startMeasurement(); 
}

float TOF::getDistance() {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); 

    if (measure.RangeStatus != 4) {  // Phase failures have status 4
        return (float)measure.RangeMilliMeter;
    } else {
        return 0; // Out of range
    }
}
