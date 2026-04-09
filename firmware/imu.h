#ifndef IMU_H
#define IMU_H
#include <Wire.h>
class IMU {
public:
    void begin();
    void update();
    float getPitch() { return pitch; }
    float getRoll() { return roll; }
private:
    float pitch = 0, roll = 0;
    float baseP = 0, baseR = 0;
    unsigned long lastT;
};
#endif
