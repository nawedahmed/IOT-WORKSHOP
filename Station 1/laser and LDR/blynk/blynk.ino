#define BLYNK_PRINT Serial
// ==== Blynk 2.0 required info ====
#define BLYNK_TEMPLATE_ID "TMPL6vwyGbxBg"
#define BLYNK_TEMPLATE_NAME "LDR"
#define BLYNK_AUTH_TOKEN "-4jA_zJAqz8mIM_loFJWePtFuifofQu9"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "KaThMaNdU Is DyInG";
char pass[] = "#PrO@98111TeCt";

// Pins
#define LDR_PIN A0
#define BUZZER_PIN D5

int threshold = 700;  // adjust based on light
bool alarmState = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int ldrValue = analogRead(LDR_PIN);
  Serial.println(ldrValue);

  if (ldrValue < threshold) {  // beam broken
    if (!alarmState) {
      Serial.println("Intruder Detected!");
      digitalWrite(BUZZER_PIN, HIGH);
      Blynk.virtualWrite(V10, "⚠️ Intruder detected! Laser beam broken!");

      alarmState = true;
    }
  } else {  // beam restored
    if (alarmState) {
      digitalWrite(BUZZER_PIN, LOW);
      alarmState = false;
    }
  }

  delay(100); // small delay for stability
}
