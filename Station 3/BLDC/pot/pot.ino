#include <Servo.h>

#define ESC_PIN D1      // GPIO5
#define POT_PIN A0

Servo esc;

int potValue;
int escSignal;

void setup() {
  Serial.begin(9600);

  esc.attach(ESC_PIN, 1000, 2000);  // ESC min/max pulse

  Serial.println("Arming ESC...");
  esc.writeMicroseconds(1000);      // Minimum throttle
  delay(3000);                      // Wait to arm ESC
}

void loop() {
  potValue = analogRead(POT_PIN);   // 0–1023
  escSignal = map(potValue, 0, 1023, 1000, 2000);

  esc.writeMicroseconds(escSignal);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  ESC: ");
  Serial.println(escSignal);

  delay(20);  // ESC refresh
}
