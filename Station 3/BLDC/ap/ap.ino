#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define ESC_PIN D1   // GPIO5

const char* ssid = "BLDC_Control";
const char* password = "12345678";

ESP8266WebServer server(80);
Servo esc;

int escValue = 1000;

// HTML page with slider
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>BLDC Control</title>
</head>
<body>
  <h2>BLDC Speed Control</h2>
  <input type="range" min="0" max="100" value="0"
         oninput="sendSpeed(this.value)">
  <p>Speed: <span id="val">0</span>%</p>

<script>
function sendSpeed(val) {
  document.getElementById('val').innerHTML = val;
  fetch('/speed?value=' + val);
}
</script>
</body>
</html>
)rawliteral";

// Handle slider input
void handleSpeed() {
  if (server.hasArg("value")) {
    int slider = server.arg("value").toInt();

    if (slider < 5) {
      escValue = 1000;  // STOP
    } else {
      escValue = map(slider, 0, 100, 1100, 2000);
    }

    esc.writeMicroseconds(escValue);
    Serial.println(escValue);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);

  esc.attach(ESC_PIN, 1000, 2000);
  esc.writeMicroseconds(1000);   // Minimum throttle
  delay(3000);                   // Arm ESC

  // Start WiFi Hotspot
  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Web server routes
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/speed", handleSpeed);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
