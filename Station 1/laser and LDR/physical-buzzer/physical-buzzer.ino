#include <ESP8266WiFi.h>

#define LDR_PIN A0// include voltage divider
#define BUZZER_PIN D5

int threshold = 700;  // adjust based on light conditions
bool alarmState = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.println(ldrValue);

  if (ldrValue < threshold) {  // beam broken
    if (!alarmState) {
      Serial.println("Intruder Detected!");
      digitalWrite(BUZZER_PIN, HIGH);
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
