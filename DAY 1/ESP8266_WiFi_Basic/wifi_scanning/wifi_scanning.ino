#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();   // Clear old connections
  delay(100);

  Serial.println("Scanning WiFi networks...");
  

}
void loop(){
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
      Serial.println(
        (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Open" : "Secured"
      );
      delay(5000);
    }
  }
}



