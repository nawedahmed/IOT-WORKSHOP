# IOT-WORKSHOP

IoT workshop projects using ESP8266 WiFi module for sensor monitoring and WiFi-based control.

---



## ✅ Required Libraries:

### for Blynk, we will add it on ( Day 2 )  so for now skip it.
---
1. Blynk Library (v1.0.1)
- 🔹 Go to Arduino IDE → Sketch → Include Library → Manage Libraries
- 🔹 Search for: Blynk
- 🔹 Install the one by Volodymyr Shymanskyy (NOT Blynk IoT or Blynk.Edgent – just "Blynk").
---


## 2. ESP8266WiFi Library
🔹 This comes automatically with the ESP8266 board package. You don’t need to install it separately.

## ✅ Board Package:

You must install the ESP8266 board package for Arduino.

📦 How to install:

1. Go to File → Preferences

2. In the “Additional Board Manager URLs” field, paste this:

```text
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```

3. Then go to Tools → Board → Boards Manager

4. Search: ESP8266 and install it (by ESP8266 Community)

## ✅ Board Selection:

After installation, go to
Tools → Board → select "NodeMCU 1.0 (ESP-12E Module)"
(or Generic Esp8266 module")

## ✅ Notes:

* Make sure your COM port is correctly selected in Tools → Port.

* Select proper baud rate (usually 115200 or 9600) under Tools → Upload Speed.

* Connect your board to PC via USB before uploading.

---



## 📅 DAY 1: ESP8266 WiFi Basics

This is the sequence of code that we will teach.

📁 **ESP8266_WIFI_BASIC/**

### 🔁 Flow of code to teach:

### `wifi_scanning.ino`


  ![Wifi scan image](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/wifi_scan.png)


### `wifi_station_mode.ino`

![Esp connected to wifi](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/espConnectedToWifi.png)

### `wifi_AP_Mode.ino`

![Esp providing network](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/wifi_AP.png)

### `Both_STA_AP_Mode.ino`

![Both Mode LED On/Off](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/Both_Mode.png)



### `welcome_code.ino`

![Welcome text](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/welcome.png)

### `coffeeMachine_APMode.ino`
 
 In sequence from connecting to esp ->  dashboard login -> On/Off page for controlling
<p align="Center">
 <img src ="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/coffeeMachine1.jpg" width="200">
 <img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/coffMachine2.jpg" width="200">
<img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/coffMachine3.jpg" width ="200">
 <img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/DAY%201/ESP8266_WiFi_Basic/images/coffMachine4.jpg" width="200">

 </p>
 

 ## The end of first Day .

 ---

 ---

 # Station 1

 Got it 👍
Below is the **FINAL, complete theory for Station 1**, written **short, clear, and beginner-friendly**, suitable for **README** and **first-time microcontroller students**.
You can paste this **directly**.

---

# 📡 Station 1: Sensors & Indicators (Final Theory)

### Objective

Station 1 introduces students to how the **ESP8266 senses the environment** and responds using **LEDs and a buzzer**. Students learn how **physical changes (distance, movement, light interruption)** are converted into **electrical signals** and processed using **simple program logic**.



## 1️⃣ Ultrasonic Sensor (HC-SR04) – Distance Measurement

### Working Principle

The HC-SR04 measures distance using **ultrasonic sound waves**.

1. ESP8266 sends a short pulse to the **TRIG** pin
2. The sensor emits ultrasonic waves
3. Waves reflect from an object
4. The **ECHO** pin stays HIGH for a duration proportional to distance

Distance is calculated using:

```
Distance = (Time × Speed of Sound) / 2
```

---

### Distance-Based LED Indication

Five LEDs visually represent object distance.

| Distance | LED Status |
| -------- | ---------- |
| ≤ 5 cm   | LED 1 ON   |
| ≤ 10 cm  | LED 2 ON   |
| ≤ 15 cm  | LED 3 ON   |
| ≤ 20 cm  | LED 4 ON   |
| > 20 cm  | LED 5 ON   |

This mimics **real-world proximity indicators** such as parking sensors.



## 2️⃣ Joystick Module – Analog Position Control

### Description

A joystick contains **two potentiometers**:

* **X-axis** → left / right
* **Y-axis** → up / down

### ESP8266 Reading

* Connected to **A0 (analog pin)**
* Value range: **0–1023**

### Learning Concept

Students learn:

* How **analog inputs** work
* Continuous control instead of ON/OFF
* Mapping physical movement to digital values

This concept is later used in **robot control and motor speed regulation**.



## 3️⃣ Laser + LDR Tripwire with Buzzer

### Working Principle

* A **laser module** continuously shines on an **LDR (Light Dependent Resistor)**
* The LDR is connected using a **voltage divider** and read via **A0**
* When the laser beam is **blocked**:

  * Light intensity drops
  * Analog value crosses a **threshold**
  * ESP8266 detects the interruption
  * **Buzzer turns ON**
* When the beam is restored:

  * **Buzzer turns OFF**

This setup acts as a **light-based tripwire system**.



## 🔔 Buzzer – Alert Output

### Purpose

The buzzer provides **instant audio feedback** when a critical event occurs, such as:

* Object approaching too close
* Laser beam interruption

This teaches students how **sensor conditions trigger output actions**.

 ---

---

# Station 2

## 🚗  DC Motor Control – ESP8266 + L298N :
<p align="Center">
<img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/Station%202/image/L298N.webp" width="500">
<img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/Station%202/image/L298NwithChip.webp" width="500">
</p>


A **DC motor** converts electrical energy into mechanical rotation.
The **L298N motor driver** allows a low-power microcontroller (ESP8266) to control a high-current motor safely.

As specified in L298N H-Bridge module the motor driver has a two motor terminal block to connect DC motor. Output A+ /- and Output B+/- .

The L298N H-Bridge module has facilitate with additional external input power supply source to handling handle starting current requirement for both DC motor. This three terminal block with +12V, GND, and +5V. The +12V terminal block is used to power up the motors. The +5V terminal is used to power up the L298N chip. If you supply more than 12V, you need to remove the jumper and supply 5V to the +5V terminal.

- +12V: The +12V terminal is where you should connect your power supply
- GND: power supply GND
- +5V: provide 5V if jumper is removed. Acts as a 5V output if jumper is in place
- Jumper: jumper in place – uses the motors power supply to power up the chip. Jumper removed: you need to provide 5V to the +5V terminal. If you supply more than 12V, you should remove the jumper

**Key concepts used:**

* **Direction control** → using IN1 / IN2 and IN3 / IN4 pins
* **Speed control** → using PWM on EN pin
* **Wi-Fi control** → ESP8266 in AP mode & Internet mode
* **Human interface** → Buttons, Joystick, Blynk IoT APP

This project is structured **step-by-step**, from **basic motor ON/OFF** to **smart IoT voice control**, so learners understand *how control complexity increases*.



## 🔹 Code Flow (Learning Order):

### 1️⃣ Single Motor (Basic)

<img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/Station%202/image/ESP8266-DC-Motor_bb.png.webp" width="500">

**Goal:** Understand motor direction

* ESP8266 → L298N
* Forward / Reverse using digital HIGH–LOW
* No Wi-Fi, no speed control

➡️ *Foundation of motor logic*



### 2️⃣ AP Mode – No Speed Control

**Goal:** Control motor wirelessly (local)

* ESP8266 creates its own Wi-Fi (AP mode)
* Web page buttons: Forward / Reverse / Stop
* Motor runs at fixed speed

➡️ *Introduces Wi-Fi + web control*



### 3️⃣ AP Mode – With Speed Control

**Goal:** Learn PWM motor control

* EN pin connected to PWM
* Speed varies using slider (0–1023)
* Direction + speed together

➡️ *Core motor control concept*



### 4️⃣ Joystick Control

**Goal:** Human-like control

* Joystick Y-axis → speed
* Joystick direction → motor direction
* Real-time response

➡️ *Analog input + control mapping*



### 5️⃣ Blynk IoT (Internet Control)

**Goal:** Full IoT control

* Control motor from **anywhere**
* Button / Slider / ( via Blynk)
* Internet-based operation

## The end of Station 2 .


 ---



