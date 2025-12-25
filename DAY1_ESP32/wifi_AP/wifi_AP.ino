/*
Minimum AP functions (ESP32)

WiFi.softAP()              → create hotspot
WiFi.softAPIP()            → get AP IP
WiFi.softAPgetStationNum() → connected clients
*/

#include <WiFi.h>

const char* ap_ssid = "ESP32_WORKSHOP";
const char* ap_password = "12345678";   // min 8 chars

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println("Access Point Started");
  Serial.print("AP SSID: ");
  Serial.println(ap_ssid);

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  Serial.print("Connected Clients: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(2000);
}
