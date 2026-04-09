#ifndef MOTORS_H
#define MOTORS_H
#include "config.h"
class Motors {
public:
    void begin();
    void write(float t, float p, float r, float y);
    void stopAll();
};
#endif
