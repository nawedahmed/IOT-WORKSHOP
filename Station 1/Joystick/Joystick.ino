#define JOY_PIN A0
#define SW_PIN  D5

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  int joyVal = analogRead(JOY_PIN);   // 0–1023
  bool pressed = !digitalRead(SW_PIN);

  Serial.print("Joystick: ");
  Serial.print(joyVal);
  Serial.print(" | Button: ");
  Serial.println(pressed ? "PRESSED" : "RELEASED");

  delay(150);
}
