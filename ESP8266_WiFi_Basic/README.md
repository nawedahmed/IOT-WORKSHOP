\# ESP8266 WiFi Basics



This folder contains basic ESP8266 WiFi examples used in the IoT Workshop.

The goal is to understand how the ESP8266 WiFi module works in different modes

before connecting sensors and cloud platforms.



---



\## 1. WiFi Network Scanning

The ESP8266 can scan nearby WiFi networks and display:

\- SSID (network name)

\- Signal strength (RSSI)

\- Encryption type



📌 Used to identify available networks before connecting.



---



\## 2. WiFi Station Mode (STA)

In Station mode, ESP8266 connects to an existing WiFi network (router).



Features:

\- Connects to home / campus WiFi

\- Gets an IP address from router

\- Used for Internet and cloud-based IoT



📌 Most common mode for IoT applications.



---



\## 3. WiFi Access Point Mode (AP)

In Access Point mode, ESP8266 creates its own WiFi network.



Features:

\- Mobile or laptop connects directly to ESP8266

\- No external router required

\- Useful for local control and configuration



📌 Used in device setup and offline IoT systems.



---



\## 4. WiFi AP + STA Mode

ESP8266 works as both Access Point and Station at the same time.



Features:

\- Connects to router (STA)

\- Creates its own WiFi network (AP)

\- Allows configuration while staying online



📌 Used in advanced IoT devices.



---



\## 5. ESP8266 WiFi Information

This example shows how to read WiFi-related information such as:

\- IP address

\- MAC address

\- Signal strength (RSSI)

\- Connected network details



📌 Helps in debugging and understanding network status.



---



\## Hardware Required

\- ESP8266 (NodeMCU)

\- USB Cable

\- Laptop with Arduino IDE



---



\## Software Required

\- Arduino IDE

\- ESP8266 Board Package installed



---



\## Notes for Students

\- Always check WiFi mode before connecting

\- Keep SSID and password correct

\- Observe Serial Monitor output carefully



---



\## Developed For

Electrical Club – Pulchowk Campus  

IoT Workshop



