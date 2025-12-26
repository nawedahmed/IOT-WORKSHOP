#define RELAY_PIN   5   // GPIO5
#define SWITCH_PIN  4   //  GPIO4

bool lastSwitchState = HIGH;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, LOW); // Relay OFF (adjust if active LOW)
}

void loop() {
  bool switchState = digitalRead(SWITCH_PIN);

  // Simple debounce
  if (switchState != lastSwitchState) {
    delay(50);
    switchState = digitalRead(SWITCH_PIN);

    if (switchState == LOW) {
      digitalWrite(RELAY_PIN, LOW); // Relay OFF
    } else {
      digitalWrite(RELAY_PIN, HIGH);  // Relay O
    }

    lastSwitchState = switchState;
  }
}
