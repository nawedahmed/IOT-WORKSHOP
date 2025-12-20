#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6LNWxDBAe"
#define BLYNK_TEMPLATE_NAME "BLDC Control"
#define BLYNK_AUTH_TOKEN "MQky3PA4J34KJenoHQqGSvWmIMVoSoxb"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// WiFi credentials
char ssid[] = "KaThMaNdU Is DyInG";
char pass[] = "#PrO@98111TeCt";

#define ESC_PIN D1   // GPIO5

Servo esc;
int escValue = 1000;   // Minimum throttle

// Slider widget (0–100)
BLYNK_WRITE(V0) {
  int sliderValue = param.asInt();  // 0–100
  escValue = map(sliderValue, 0, 100, 1100, 2000);
  esc.writeMicroseconds(escValue);
}

void setup() {
  Serial.begin(9600);

  esc.attach(ESC_PIN, 1000, 2000);

  Serial.println("Arming ESC...");
  esc.writeMicroseconds(1000);   // Min throttle
  delay(3000);                   // ESC arm time

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
