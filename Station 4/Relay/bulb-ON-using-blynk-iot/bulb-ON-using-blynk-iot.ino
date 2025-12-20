#define BLYNK_PRINT Serial
/* ---------- BLYNK DETAILS ---------- */
#define BLYNK_TEMPLATE_ID "TMPL6vZYdfOGw"
#define BLYNK_TEMPLATE_NAME "Relay"
#define BLYNK_AUTH_TOKEN "cWj53wExoQWVpcGNl18In7ogWsfQm_82"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* ---------- WIFI DETAILS ----------- */
char ssid[] = "KaThMaNdU Is DyInG";
char pass[] = "#PrO@98111TeCt";

/* ---------- HARDWARE --------------- */
#define RELAY_PIN D1   // GPIO5

BLYNK_WRITE(V0) {
  int value = param.asInt(); // 1 or 0

  if (value == 1) {
    digitalWrite(RELAY_PIN, LOW);   // Relay ON (active LOW)
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF initially

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
