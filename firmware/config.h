#ifndef CONFIG_H
#define CONFIG_H

// Motors
#define PIN_MOTOR_1 4
#define PIN_MOTOR_2 33
#define PIN_MOTOR_3 32
#define PIN_MOTOR_4 25

// WiFi
#define WIFI_SSID "ESP32_Drone"
#define WIFI_PASS "123456789"
#define UDP_PORT 8888

// Stability PID
#define PID_PITCH_KP 0.8f
#define PID_PITCH_KI 0.02f
#define PID_PITCH_KD 0.1f

#define PID_ROLL_KP 0.8f
#define PID_ROLL_KI 0.02f
#define PID_ROLL_KD 0.1f

// Altitude Assist Config
#define TARGET_HEIGHT_MM 300.0f  // Target 30cm height
#define ALTITUDE_KP 0.4f         // How strongly it corrects height

// Safety
#define FAILSAFE_TIMEOUT_MS 1500
#define LOOP_TIME_MS 10 // 100Hz

#endif
