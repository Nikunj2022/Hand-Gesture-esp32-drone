#ifndef COMM_H
#define COMM_H
#include <WiFi.h>
#include <WiFiUdp.h>
struct ControlData { int throttle; float pitch, roll, yaw; unsigned long lastPacketTime; };
class Communication {
public:
    void begin();
    bool receive(ControlData &data);
private:
    WiFiUDP udp;
};
#endif
