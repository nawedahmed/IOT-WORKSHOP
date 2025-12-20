#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define SERVO_PIN D1   // GPIO5

const char* ssid = "Servo_Control";
const char* password = "12345678";

ESP8266WebServer server(80);
Servo myServo;

int servoAngle = 0;

// HTML page with slider
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Servo Control</title>
</head>
<body>
  <h2>Servo Motor Control</h2>
  <input type="range" min="0" max="180" value="0"
         oninput="sendAngle(this.value)">
  <p>Angle: <span id="val">0</span>°</p>

<script>
function sendAngle(val) {
  document.getElementById('val').innerHTML = val;
  fetch('/angle?value=' + val);
}
</script>
</body>
</html>
)rawliteral";

// Handle slider input
void handleAngle() {
  if (server.hasArg("value")) {
    servoAngle = server.arg("value").toInt();
    myServo.write(servoAngle);
    Serial.print("Servo Angle: ");
    Serial.println(servoAngle);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);

  myServo.attach(SERVO_PIN);

  // Start WiFi Hotspot
  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Web server routes
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/angle", handleAngle);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
