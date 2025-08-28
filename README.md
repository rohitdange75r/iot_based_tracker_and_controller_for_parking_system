🚗 IoT Based Tracker and Controller for Parking System

📌 Introduction

This project is an **IoT-enabled smart parking system** that monitors parking slots, detects car entry/exit, and updates the availability in **real-time** on an LCD and the **Blynk mobile app**. It also controls entry/exit gates using **servo motors**.

🛠️ Components Used

* ESP32 Development Board
* Servo Motors (2 × for entry & exit gates)
* IR Sensors for car detection
* LCD 20×4 (I2C)
* Blynk IoT Platform (for mobile monitoring)
* Wi-Fi connection

⚙️ Working

1. *Entry Gate Control* – When a car is detected at the entry, the *servo gate opens*, and the system assigns a slot if available.
2. *Slot Detection* – IR sensors track which slot is occupied (Slot1–Slot4).
3. *Exit Gate Control* – When a car leaves a slot and reaches the exit sensor, the *exit gate opens*, and the slot count is updated.
4. *Monitoring & Control* –

   * *LCD* shows slot status in real-time.
   * *Blynk app* displays available slots remotely.

🌐 Features

✔️ Real-time car entry/exit tracking
✔️ LCD display for local monitoring
✔️ Blynk IoT app for remote monitoring
✔️ Automatic entry/exit gate control with servos
✔️ Slot availability updates
