#ifndef TOF_H
#define TOF_H

#include "Adafruit_VL53L0X.h"

class TOF {
public:
    void begin();
    float getDistance(); // Returns distance in mm
private:
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
};

#endif
