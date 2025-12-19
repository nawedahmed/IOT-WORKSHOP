#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6z4UJNwuV"
#define BLYNK_TEMPLATE_NAME "L298N"
#define BLYNK_AUTH_TOKEN "1dUCKFNOTD04WkQht_Ez6atfxG7jOiRR"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi and Blynk Auth Token
char auth[] = "1dUCKFNOTD04WkQht_Ez6atfxG7jOiRR";
char ssid[] = "KaThMaNdU Is DyInG";
char pass[] = "#PrO@98111TeCt";

// Motor pins
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D6
#define ENB D7

int speedMotor = 150;

// ================= MOTOR FUNCTIONS =================
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void leftTurn() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void rightTurn() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ================= BLYNK VIRTUAL PINS =================
BLYNK_WRITE(V1) {  // Forward
  if (param.asInt()) forward(); else stopMotors();
}

BLYNK_WRITE(V2) {  // Backward
  if (param.asInt()) backward(); else stopMotors();
}

BLYNK_WRITE(V3) {  // Left
  if (param.asInt()) leftTurn(); else stopMotors();
}

BLYNK_WRITE(V4) {  // Right
  if (param.asInt()) rightTurn(); else stopMotors();
}

BLYNK_WRITE(V5) {  // Stop
  stopMotors();
}

BLYNK_WRITE(V6) {  // Speed Slider
  speedMotor = param.asInt();  // 0-255
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

// ================= LOOP =================
void loop() {
  Blynk.run();
}
