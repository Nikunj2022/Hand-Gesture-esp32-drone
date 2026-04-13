# 🛸 ESP32 Gesture-Controlled Quadcopter

[![Expertise: Embedded Systems](https://img.shields.io/badge/Expertise-Embedded%20Systems-blueviolet)](#)
[![Board: ESP32](https://img.shields.io/badge/Board-ESP32-red)](https://espressif.com)
[![Protocol: UDP](https://img.shields.io/badge/Protocol-UDP-blue)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

A professional-grade, modular DIY drone system controlled via a wearable gesture glove. This project implements real-time PID stabilization, a 50Hz high-precision command bridge, and advanced safety mechanisms to ensure smooth and responsive flight.

---

## 🏗️ System Architecture

The project is structured into three distinct layers to optimize performance and minimize latency:

1. **Drone Firmware (C++)** – Modular flight controller using ESP32 LEDC PWM, MPU6050 sensor fusion (Complementary Filter), and a "Flywheel" failsafe to handle WiFi jitter.
2. **Gesture Glove (C++)** – Wearable controller mapping hand tilt to Pitch/Roll using IMU data, with an oversampled LDR for throttle control.
3. **Python Bridge** – High-precision script handling USB-to-WiFi relay, throttle ramping, calibration, and a constant heartbeat signal.

---

## 🛠️ Hardware Configuration & Pinout

### Flight Controller (Drone)

| Component | ESP32 Pin | Function |
|----------|----------|----------|
| Motor 1 | GPIO 04 | Front-Right (PWM) |
| Motor 2 | GPIO 33 | Front-Left (PWM) |
| Motor 3 | GPIO 32 | Rear-Left (PWM) |
| Motor 4 | GPIO 25 | Rear-Right (PWM) |
| I2C SDA | GPIO 21 | MPU6050 Data |
| I2C SCL | GPIO 22 | MPU6050 Clock |

### Gesture Controller (Glove)

| Component | ESP32 Pin | Function |
|----------|----------|----------|
| LDR Sensor | GPIO 34 | Analog Throttle |
| I2C SDA | GPIO 21 | MPU6050 Data |
| I2C SCL | GPIO 22 | MPU6050 Clock |

---

## 🚀 Installation & Setup

### Firmware Deployment

- Upload `ESP32_Drone.ino` to the drone ESP32 → creates WiFi AP `ESP32_Drone`
- Upload `Hand_gesture_glove.ino` to the glove ESP32
- Keep glove flat for 2 seconds during startup for auto-calibration

### Python Bridge Setup

Install dependency:

```bash
pip install pyserial
```

Steps:

- Connect PC to `ESP32_Drone` WiFi
- Connect glove via USB
- Find COM port (e.g., COM3)
- Update `USB_PORT` in `main.py`
- Run:

```bash
python main.py
```

---

## 🛡️ Flight Safety & Stability

- Flywheel failsafe → holds last command for 1.5s during signal loss  
- Schmitt-trigger LDR → avoids noise (ON: 1800, OFF: 800)  
- Linear throttle ramp → prevents sudden jumps  
- Deadzone filtering → ignores ±5° tilt for stable hover  

---

## 🔧 Tuning & Calibration

- Forward flip issue → invert pitch sign in `IMU.cpp`  
- Hover throttle → adjust `HOVER_THROTTLE` in `main.py` (default 145)  
- PID tuning → modify in `config.h` (`PID_PITCH_KP`, `PID_ROLL_KP`)  

---

## 📂 Repository Structure

```
├── Drone_Firmware/
│   ├── config.h
│   ├── IMU.cpp/h
│   ├── Motors.cpp/h
│   ├── PID.cpp/h
│   ├── Communication.cpp/h
│   └── ESP32_Drone.ino
├── Glove_Firmware/
│   └── Hand_gesture_glove.ino
└── Python_Bridge/
    └── main.py
```

---

## ⚠️ Disclaimer

Always test without propellers first.  
Use at your own risk — no responsibility for damage or injury.
