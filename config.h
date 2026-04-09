#ifndef CONFIG_H
#define CONFIG_H

#define PIN_MOTOR_1 4   // Front Right
#define PIN_MOTOR_2 33  // Front Left
#define PIN_MOTOR_3 32  // Rear Left
#define PIN_MOTOR_4 25  // Rear Right

#define WIFI_SSID "ESP32_Drone"
#define WIFI_PASS "123456789"
#define UDP_PORT 8888

#define PID_PITCH_KP 0.8f  // Lowered for stability
#define PID_PITCH_KI 0.02f
#define PID_PITCH_KD 0.1f

#define PID_ROLL_KP 0.8f
#define PID_ROLL_KI 0.02f
#define PID_ROLL_KD 0.1f

#define FAILSAFE_TIMEOUT_MS 1500 // "Flywheel" safety
#define LOOP_FREQ_HZ 100
#define LOOP_TIME_MS (1000 / LOOP_FREQ_HZ)

#endif
