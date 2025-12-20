#define RELAY_PIN D1
#define SWITCH_PIN D2

bool lastSwitchState = HIGH;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, LOW); // Relay OFF (change if active LOW)
}

void loop() {
  bool switchState = digitalRead(SWITCH_PIN);

  // Simple debounce
  if (switchState != lastSwitchState) {
    delay(50);
    switchState = digitalRead(SWITCH_PIN);

    if (switchState == LOW) {
      digitalWrite(RELAY_PIN, HIGH); // Relay ON
    } else {
      digitalWrite(RELAY_PIN, LOW);  // Relay OFF
    }

    lastSwitchState = switchState;
  }
}
