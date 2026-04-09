#include "PID.h"
#include <Arduino.h>
PID::PID(float kp, float ki, float kd) : _kp(kp), _ki(ki), _kd(kd), _err(0), _int(0) {}
float PID::compute(float set, float cur, float dt) {
    float error = set - cur;
    _int = constrain(_int + error * dt, -50, 50);
    float deriv = (error - _err) / dt;
    _err = error;
    return (_kp * error) + (_ki * _int) + (_kd * deriv);
}
