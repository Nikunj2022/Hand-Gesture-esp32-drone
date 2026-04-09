#ifndef PID_H
#define PID_H
class PID {
public:
    PID(float kp, float ki, float kd);
    float compute(float set, float cur, float dt);
private:
    float _kp, _ki, _kd, _err, _int;
};
#endif
