#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);   // clear old config
  delay(100);

  Serial.println("Scanning WiFi networks...");
}

void loop() {
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.println("Networks found:");
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm | ");

      wifi_auth_mode_t enc = WiFi.encryptionType(i);
      Serial.println((enc == WIFI_AUTH_OPEN) ? "Open" : "Secured");

      delay(500);
    }
  }

  Serial.println("-----------------------");
  delay(5000);   // rescan after 5 sec
}
