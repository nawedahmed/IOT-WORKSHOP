


// Region: SGP1


#define BLYNK_TEMPLATE_ID "TMPL6nI8oUx2R"
#define BLYNK_TEMPLATE_NAME "Voice Assistant"
#define BLYNK_AUTH_TOKEN "eykSOSJS3RyEMKAXZgBiisHXr8Jkg4f1"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "eykSOSJS3RyEMKAXZgBiisHXr8Jkg4f1";
char ssid[] = "realme 12x 5G";
char pass[] = "12345678mm";

#define LED_PIN D1

BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(LED_PIN, value);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
