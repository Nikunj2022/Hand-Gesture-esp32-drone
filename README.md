# 🛸 ESP32 Gesture-Controlled Quadcopter

[![Expertise: Embedded Systems](https://img.shields.io/badge/Expertise-Embedded%20Systems-blueviolet)](https://github.com/yourusername)
[![Board: ESP32](https://img.shields.io/badge/Board-ESP32-red)](https://espressif.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

A production-grade, modular drone firmware and wearable gesture controller. This project uses an ESP32-based flight controller and a secondary ESP32 "Glove" to control flight via hand tilts and light intensity (LDR).

---

## 🧠 System Architecture

The system is split into three distinct layers to ensure real-time stability and low latency:

1.  **Drone Firmware:** Modular C++ code using a 100Hz PID loop and a "Flywheel" failsafe.
2.  **Gesture Glove:** A wearable device that processes IMU data and LDR triggers.
3.  **Python Bridge:** A high-precision heartbeat script that connects USB Serial to WiFi UDP.

---

## 🛠 Hardware Configuration

### Flight Controller (Drone)
| Component | GPIO Pin | Function |
| :--- | :--- | :--- |
| **Motor 1** | GPIO 04 | Front-Right (PWM) |
| **Motor 2** | GPIO 33 | Front-Left (PWM) |
| **Motor 3** | GPIO 32 | Rear-Left (PWM) |
| **Motor 4** | GPIO 25 | Rear-Right (PWM) |
| **MPU6050 SDA**| GPIO 21 | I2C Data |
| **MPU6050 SCL**| GPIO 22 | I2C Clock |

### Gesture Controller (Glove)
| Component | GPIO Pin | Function |
| :--- | :--- | :--- |
| **LDR Input**  | GPIO 34 | Throttle Trigger (Analog) |
| **MPU6050 SDA**| GPIO 21 | I2C Data |
| **MPU6050 SCL**| GPIO 22 | I2C Clock |

---

## 🚀 Installation & Setup

### 1. Firmware Upload
Ensure you have the **ESP32 Arduino Core 3.0+** installed.
*   **Drone:** Upload `ESP32_Drone.ino`. It will create a WiFi AP named `ESP32_Drone`.
*   **Glove:** Upload `Hand_gesture_glove.ino`. Keep the glove flat on the desk during power-up for auto-calibration.

### 2. Python Bridge Setup
The Python script is required to bridge the USB-connected Glove to the WiFi-connected Drone.
```bash
pip install pyserial
Connect your Laptop to the ESP32_Drone WiFi.
Plug the Glove into your Laptop via USB.
Update USB_PORT in main.py (e.g., COM3).
Run: python main.py.
🛡️ Flight Safety & Stability
This firmware implements several safety mechanisms to prevent accidents:
Flywheel Failsafe: The drone maintains its last command for up to 1.5 seconds if a WiFi packet is dropped, preventing "pulsing" throttle.
Schmitt-Trigger Throttle: The LDR uses dual thresholds (ON at 1800, OFF at 800) to prevent noisy light signals from toggling the motors.
Soft-Ramping: Throttle increases gradually rather than jumping, preventing violent takeoffs.
Neutral Deadzone: Hand tilts under 5° are ignored to ensure a stable hover.
🔧 Tuning Guide
Forward Flip Fix: If the drone flips forward on takeoff, verify that tilting the nose down causes the front motors to speed up. If they don't, invert the pitch sign in IMU.cpp.
PID Gains: Adjust PID_PITCH_KP and PID_ROLL_KP in config.h to change how aggressively the drone balances itself.
Hover Power: Adjust HOVER_THROTTLE in the Python script based on your drone's weight/battery voltage.
📂 Project Structure
├── Drone_Firmware/
│   ├── config.h            # Pinouts and PID Tuning
│   ├── IMU.cpp/h           # Complementary Filter & Calibration
│   ├── Motors.cpp/h        # X-Config Mixer & LEDC PWM
│   ├── PID.cpp/h           # Control Algorithm
│   └── ESP32_Drone.ino     # Main Entry & Failsafe Logic
├── Glove_Firmware/
│   └── Hand_gesture_glove.ino
└── Python_Bridge/
    └── main.py             # 50Hz Precision Heartbeat Script
Disclaimer: Always conduct initial tests without propellers. This is an experimental project; use at your own risk.
