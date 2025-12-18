/* 
Minimum Function Need to know

| Function         | Purpose          |
| ---------------- | ---------------- |
|  WiFi.begin()    | Start connection |
|  WiFi.status()   | Check state      |
|  WiFi.localIP()  | Get IP           |
|  WiFi.RSSI()     | Signal strength  |

Wifi.status() -> return the following i.e in status column and its meaning

| Status              | Meaning           |
| ------------------- | ----------------- |
| `WL_IDLE_STATUS`    | Starting          |
| `WL_NO_SSID_AVAIL`  | Network not found |
| `WL_CONNECT_FAILED` | Wrong password    |
| `WL_CONNECTED`      | Success           |
| `WL_DISCONNECTED`   | Lost connection   |


*/

#include <ESP8266WiFi.h>

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
}
