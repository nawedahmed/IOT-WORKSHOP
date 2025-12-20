#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define TRIG_PIN D5
#define ECHO_PIN D6

ESP8266WebServer server(80);

int ledPins[6] = {D0, D1, D2, D3, D4, D7};
int targetDistances[5] = {5, 10, 15, 20, 25};
int tolerance = 1;

long duration;
float distance;
bool ledState[6];

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    ledState[i] = false;
  }

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start AP mode
  WiFi.softAP("ESP8266_Distance", "12345678");
  Serial.println("AP Started");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.begin();
}

void handleRoot() {
  String html = "<html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='1'>"; // Auto-refresh every 1 second
  html += "<style>body{font-family:Arial;text-align:center;} .on{color:green;} .off{color:red;}</style>";
  html += "</head><body>";
  html += "<h2>ESP8266 Distance Monitor</h2>";
  html += "<h3>Distance: " + String(distance) + " cm</h3>";

  for (int i = 0; i < 6; i++) {
    html += "LED" + String(i + 1) + ": ";
    html += ledState[i] ? "<span class='on'>ON</span><br>" :
                          "<span class='off'>OFF</span><br>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void loop() {
  server.handleClient();

  // Trigger HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Reset LED states
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
    ledState[i] = false;
  }

  if (duration != 0) {
    distance = duration * 0.0343 / 2;

    // LED1–LED5
    for (int i = 0; i < 5; i++) {
      if (distance >= targetDistances[i] - tolerance &&
          distance <= targetDistances[i] + tolerance) {
        digitalWrite(ledPins[i], HIGH);
        ledState[i] = true;
      }
    }

    // LED6 (>25 cm)
    if (distance > 25) {
      digitalWrite(ledPins[5], HIGH);
      ledState[5] = true;
    }
  }

  delay(200);
}
