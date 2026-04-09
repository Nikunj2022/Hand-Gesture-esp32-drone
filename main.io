#include "config.h"
#include "IMU.h"
#include "PID.h"
#include "Motors.h"
#include "Communication.h"

IMU imu; Motors motors; Communication comm;
PID pitchPID(PID_PITCH_KP, PID_PITCH_KI, PID_PITCH_KD);
PID rollPID(PID_ROLL_KP, PID_ROLL_KI, PID_ROLL_KD);
ControlData remote = {0, 0, 0, 0, 0};
bool armed = false;
unsigned long lastLoop = 0;

void setup() {
    Serial.begin(115200);
    imu.begin(); motors.begin(); comm.begin();
}

void loop() {
    unsigned long now = millis();
    if (now - lastLoop >= LOOP_TIME_MS) {
        lastLoop = now;
        imu.update();
        comm.receive(remote);

        // Flywheel Failsafe
        if (now - remote.lastPacketTime > FAILSAFE_TIMEOUT_MS) {
            motors.stopAll();
            armed = false;
        } else {
            if (!armed && remote.throttle < 10) armed = true;
            if (armed) {
                float p_out = pitchPID.compute(remote.pitch, imu.getPitch(), 0.01);
                float r_out = rollPID.compute(remote.roll, imu.getRoll(), 0.01);
                motors.write(remote.throttle, p_out, r_out, remote.yaw);
            }
        }
    }
}
