#include "Motors.h"
#include <Arduino.h>
void Motors::begin() {
    ledcAttach(PIN_MOTOR_1, 5000, 8);
    ledcAttach(PIN_MOTOR_2, 5000, 8);
    ledcAttach(PIN_MOTOR_3, 5000, 8);
    ledcAttach(PIN_MOTOR_4, 5000, 8);
}
void Motors::write(float t, float p, float r, float y) {
    if (t < 10) { stopAll(); return; }
    float bt = t + 20; // Idle Boost
    int m1 = constrain(bt + p - r + y, 0, 255);
    int m2 = constrain(bt + p + r - y, 0, 255);
    int m3 = constrain(bt - p + r + y, 0, 255);
    int m4 = constrain(bt - p - r - y, 0, 255);
    ledcWrite(PIN_MOTOR_1, m1); ledcWrite(PIN_MOTOR_2, m2);
    ledcWrite(PIN_MOTOR_3, m3); ledcWrite(PIN_MOTOR_4, m4);
}
void Motors::stopAll() {
    ledcWrite(PIN_MOTOR_1, 0); ledcWrite(PIN_MOTOR_2, 0);
    ledcWrite(PIN_MOTOR_3, 0); ledcWrite(PIN_MOTOR_4, 0);
}
