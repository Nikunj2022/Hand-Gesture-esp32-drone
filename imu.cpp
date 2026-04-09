#include "IMU.h"
#include <Arduino.h>
void IMU::begin() {
    Wire.begin(21, 22, 400000);
    Wire.beginTransmission(0x68);
    Wire.write(0x6B); Wire.write(0); Wire.endTransmission(true);
    
    // Calibration
    float sp=0, sr=0;
    for(int i=0; i<200; i++) { update(); sp+=pitch; sr+=roll; delay(5); }
    baseP = sp/200.0; baseR = sr/200.0;
}
void IMU::update() {
    Wire.beginTransmission(0x68); Wire.write(0x3B); Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true);
    int16_t ax = Wire.read()<<8|Wire.read();
    int16_t ay = Wire.read()<<8|Wire.read();
    int16_t az = Wire.read()<<8|Wire.read();
    Wire.read(); Wire.read();
    int16_t gx = Wire.read()<<8|Wire.read();
    int16_t gy = Wire.read()<<8|Wire.read();

    float dt = (millis() - lastT) / 1000.0f; lastT = millis();
    float ap = atan2(ay, az) * 180 / PI;
    float ar = atan2(-ax, sqrt(ay*ay + az*az)) * 180 / PI;

    pitch = 0.98f * (pitch + (gx / 131.0f) * dt) + 0.02f * ap;
    roll = 0.98f * (roll + (gy / 131.0f) * dt) + 0.02f * ar;
    pitch -= baseP; roll -= baseR;
}
