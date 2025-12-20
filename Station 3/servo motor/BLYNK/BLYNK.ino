// Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL6oqMuXnZw"
#define BLYNK_TEMPLATE_NAME "SERVO"
#define BLYNK_AUTH_TOKEN "_v85WocCGwioLv2q70-_YeRbc01Mj9Cn"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// WiFi credentials
char ssid[] = "KaThMaNdU Is DyInG";
char pass[] = "#PrO@98111TeCt";

Servo myServo;
int servoPin = D4;   // GPIO2

// Slider widget on V0
BLYNK_WRITE(V0) {
  int angle = param.asInt();   // 0–180
  myServo.write(angle);
}

void setup() {
  Serial.begin(9600);

  myServo.attach(servoPin);
  myServo.write(90); // center position

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
