#include "Communication.h"
#include "config.h"
void Communication::begin() {
    WiFi.softAP(WIFI_SSID, WIFI_PASS);
    udp.begin(UDP_PORT);
}
bool Communication::receive(ControlData &data) {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        char buf[64]; int len = udp.read(buf, 63); buf[len] = 0;
        if (sscanf(buf, "%d,%f,%f,%f", &data.throttle, &data.pitch, &data.roll, &data.yaw) == 4) {
            data.lastPacketTime = millis(); return true;
        }
    }
    return false;
}
