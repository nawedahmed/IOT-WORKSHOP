/*
Minimum Functions (ESP32)

WiFi.begin()    → start connection
WiFi.status()   → connection state
WiFi.localIP()  → assigned IP
WiFi.RSSI()     → signal strength
*/

#include <WiFi.h>

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
}
