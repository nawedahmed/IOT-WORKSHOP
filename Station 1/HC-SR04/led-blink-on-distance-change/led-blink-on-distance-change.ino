#define TRIG_PIN D5
#define ECHO_PIN D6

int ledPins[6] = {D0, D1, D2, D3, D4, D7};
int targetDistances[5] = {5, 10, 15, 20, 25}; // cm
int tolerance = 1;   // ±1 cm

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  digitalWrite(TRIG_PIN, LOW);
  delay(100);
}

void loop() {
  // Trigger HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Turn all LEDs OFF first
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  if (duration == 0) {
    Serial.println("Out of range");
    delay(300);
    return;
  }

  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  bool ledOn = false;

  // LED1–LED5
  for (int i = 0; i < 5; i++) {
    if (distance >= targetDistances[i] - tolerance &&
        distance <= targetDistances[i] + tolerance) {
      digitalWrite(ledPins[i], HIGH);
      ledOn = true;
    }
  }

  // LED6 ON when distance > 25 cm
  if (distance > 25) {
    digitalWrite(ledPins[5], HIGH);
    ledOn = true;
  }

  delay(200);
}
