# IOT-WORKSHOP

IoT workshop projects using ESP8266 WiFi module for sensor monitoring and WiFi-based control.

---



## ✅ Required Libraries:

### for Blynk, we will add it on ( Day 3 )  so for now skip it.
---
1. Blynk Library (v1.0.1)
🔹 Go to Arduino IDE → Sketch → Include Library → Manage Libraries
🔹 Search for: Blynk
🔹 Install the one by Volodymyr Shymanskyy (NOT Blynk IoT or Blynk.Edgent – just "Blynk").
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


  ![Wifi scan image](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/wifi_scan.png)


### `wifi_station_mode.ino`

![Esp connected to wifi](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/espConnectedToWifi.png)

### `wifi_AP_Mode.ino`

![Esp providing network](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/wifi_AP.png)

### `Both_STA_AP_Mode.ino`

![Both Mode LED On/Off](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/Both_Mode.png)



### `welcome_code.ino`

![Welcome text](https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/welcome.png)

### `coffeeMachine_APMode.ino`
 
 In sequence from connecting to esp ->  dashboard login -> On/Off page for controlling
<p align="Center">
 <img src ="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/coffeeMachine1.jpg" width="200">
 <img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/coffMachine2.jpg" width="200">
<img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/coffMachine3.jpg" width ="200">
 <img src="https://github.com/nawedahmed/IOT-WORKSHOP/blob/main/ESP8266_WiFi_Basic/images/coffMachine4.jpg" width="200">

 </p>
 

 ## The end of first Day .



