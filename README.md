# 🛠️ Floating Trash Collector Bot (Arduino-Based)

This project is a **solar-powered river cleaning robot** designed to detect and collect floating waste from water bodies using ultrasonic sensors, servos, and a dual-motor system. It supports both **manual** and **autonomous** modes and aims to reduce human effort in cleaning polluted rivers and lakes.

---

## 🚀 Features

- **Dual Ultrasonic Sensors**:
  - *Waste Detection Sensor* – detects floating trash.
  - *Obstacle Detection Sensor* – prevents collisions.

- **Servo-Powered Scoop Mechanism**:
  - Uses two servos to scoop and collect floating waste.

- **Manual & Automatic Modes**:
  - Switch between manual control via Bluetooth and autonomous obstacle/waste navigation.

- **Motor Driver Integration**:
  - Dual motors (Left and Right) controlled for smooth navigation.

---

## 📦 Hardware Requirements

- Arduino Uno/Nano
- L298N Motor Driver
- Ultrasonic Sensors (2x)
- Servo Motors (2x)
- DC Motors (2x)
- Bluetooth Module (HC-05/HC-06)
- Solar Panel (for power supply, optional)
- Power Supply/Battery
- Chassis with Water-Resistant Design

---

## 💡 Getting Started

1. **Clone this repository**:
   ```bash
   git clone https://github.com/your-username/floating-trash-bot.git
   ```

2. **Upload Code**:
   - Open the `.ino` file in Arduino IDE.
   - Select the correct board and port.
   - Upload to your Arduino board.

3. **Serial Commands**:
   - `M` - Toggle between Manual and Automatic mode.
   - `F`, `B`, `L`, `R`, `S` - Movement commands in Manual mode.
   - `P` - Activate scoop mechanism.

---
## Demonstration


https://github.com/user-attachments/assets/bdb09011-1316-4f06-b0b1-067ab473e2b5

https://github.com/user-attachments/assets/90ec1ab6-2cf4-4719-a1c4-8c5dc4f70cb0


## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
