# 🦾 Dual Serial Servo Controller with Arduino : Horizon Serial-Servo-Control task  
Q. Using the serial servo bus controller, write code to move the servo’s into desired angles simultaneously. The angles will be taken as an array of float.

This Arduino sketch allows you to control **two serial servos** (like LX-16A) via **SoftwareSerial** using either:

- ✅ The `LX16Servo.h` library for ease of use  
- ⚙️ A manual serial protocol (without any library) for low-level control (commented)

---

## 🔧 Hardware Requirements

- Arduino UNO (or compatible)
- 2x Serial Bus Servos (e.g., LX-16A)
- Y-cable for serial bus (TX shared line)
- External 6V power supply for servos
- **Wiring:**
  - `TX` (Pin 11) → Servo Signal line (shared)
  - `GND` shared between Arduino and servo power

---

## 🚀 How It Works

- You send angles like `90,45` via the **Serial Monitor**.
- The servos move to the specified angles.
- Works with:
  - ✅ `LX16Servo.h` for easy servo control
  - 🔍 Manual packet mode for raw serial protocol

---

↗️ [Tinkercad simulation](https://www.tinkercad.com/things/38gMIGXrHpu-serial-servo-control?sharecode=gLhvVtTy-r7HfV7HfKr7NuRwdmaScRgoO-FOjPSLRkw)  
Tinkercad simulation uses 2 servos instead of serial servo bus, serial bus servo code is implimented in ./src/sketch.ino  
