#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D6
#define ENB D7

#define JOY_Y A0   // Analog
#define JOY_X D5   // Digital

int joyY;
int speedMotor;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(JOY_X, INPUT);

  Serial.begin(9600);
}

void loop() {
  joyY = analogRead(JOY_Y); // 0–1023
  speedMotor = map(abs(joyY - 512), 0, 512, 0, 255);

  int joyX = digitalRead(JOY_X);

  if (joyY > 600 && joyX == HIGH) {
    forward(speedMotor);
  }
  else if (joyY < 400 && joyX == HIGH) {
    backward(speedMotor);
  }
  else if (joyX == LOW) {
    leftTurn(180);
  }
  else {
    stopMotors();
  }
}

void forward(int sp) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, sp);
  analogWrite(ENB, sp);
}

void backward(int sp) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, sp);
  analogWrite(ENB, sp);
}

void leftTurn(int sp) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, sp);
  analogWrite(ENB, sp);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
