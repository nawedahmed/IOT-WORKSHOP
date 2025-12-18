/* 
Minimum AP functions need to know
| Function                     | Purpose        |
| ---------------------------- | -------------- |
| `WiFi.softAP()`              | Create hotspot |
| `WiFi.softAPIP()`            | Get AP IP      |
| `WiFi.softAPgetStationNum()` | Count clients  |

*/

#include <ESP8266WiFi.h>

const char* ap_ssid = "ESP8266_WORKSHOP";
const char* ap_password = "12345678"; // min 8 chars

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println("Access Point Started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
}
