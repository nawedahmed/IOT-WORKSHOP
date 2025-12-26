#define BLYNK_PRINT Serial

/* ---------- BLYNK DETAILS ---------- */
#define BLYNK_TEMPLATE_ID "TMPL68WkMiY9w"
#define BLYNK_TEMPLATE_NAME "Relay ESP32"
#define BLYNK_AUTH_TOKEN "uHFP33OURW6gSoQZP6heasfRZ0W8pVmW"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

/* ---------- WIFI DETAILS ----------- */
char ssid[] = "POCO F7";
char pass[] = "ainul12345678";

/* ---------- HARDWARE --------------- */
#define RELAY_PIN 5   // D1 -> GPIO5

// Blynk Virtual Pin V0
BLYNK_WRITE(V0) {
  int value = param.asInt(); // 1 = ON, 0 = OFF

  if (value == 1) {
    digitalWrite(RELAY_PIN, LOW);   // Relay ON (active LOW)
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
  }

  Serial.print("Relay state: ");
  Serial.println(value ? "ON" : "OFF");
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
