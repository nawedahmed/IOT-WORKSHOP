#include <Servo.h>

#define SERVO_PIN D1   // GPIO5
#define POT_PIN   A0

Servo servo360;

int potValue;
int servoPulse;

void setup() {
  Serial.begin(9600);

  servo360.attach(SERVO_PIN);
  servo360.writeMicroseconds(1500);  // STOP
  delay(1000);

  Serial.println("360 Servo controlled by Potentiometer");
}

void loop() {
  potValue = analogRead(POT_PIN);  // 0–1023

  // Dead zone around center
  if (potValue > 480 && potValue < 540) {
    servoPulse = 1500;  // STOP
  }
  // Clockwise rotation
  else if (potValue >= 540) {
    servoPulse = map(potValue, 540, 1023, 1500, 2000);
  }
  // Counter-clockwise rotation
  else {
    servoPulse = map(potValue, 0, 480, 1000, 1500);
  }

  servo360.writeMicroseconds(servoPulse);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Pulse: ");
  Serial.println(servoPulse);

  delay(20); // smooth update
}
