/*
 ESP32 AP Mode demo
 - ESP32 creates WiFi hotspot
 - Login page
 - Control GPIO like a switch
 - Practical AP-mode application
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Coffee Machine";
const char* password = "coffee@#123";     // AP password (min 8 chars)
const char* loginPassword = "coffee123";  // Web login password

WebServer server(80);
bool ledState = false;

#define LED_PIN 4   // GPIO2 (built-in LED on most ESP32 boards)

/* ---------- LOGIN PAGE ---------- */
String loginPage() {
  return R"====(
    <html>
    <head>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <style>
        body { font-family: Arial; text-align: center; background: #f2f2f2; padding-top: 50px; }
        form { background: white; display: inline-block; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px #aaa; }
        input { padding: 10px; margin: 10px; width: 200px; border-radius: 5px; }
        input[type=submit] { background: #007BFF; color: white; border: none; }
      </style>
    </head>
    <body>
      <form action='/' method='GET'>
        <h2>Coffee Machine Login</h2>
        <input type='password' name='password' placeholder='Enter Password'><br>
        <input type='submit' value='Login'>
      </form>
    </body>
    </html>
  )====";
}

/* ---------- CONTROL PAGE ---------- */
String controlPage() {
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <style>
        body { font-family: Arial; text-align: center; background-color: #f4f4f4; padding-top: 30px; }
        .btn { padding: 15px 25px; margin: 10px; font-size: 18px; border-radius: 8px; border: none; }
        .on { background: #28a745; color: white; }
        .off { background: #dc3545; color: white; }
      </style>
      <script>
        function toggleLED(state) {
          fetch("/toggle?state=" + state + "&password=coffee123");
        }
        function refreshStatus() {
          fetch("/status")
            .then(r => r.text())
            .then(t => document.getElementById("st").innerHTML = t);
        }
        setInterval(refreshStatus, 1000);
        window.onload = refreshStatus;
      </script>
    </head>
    <body>
      <h2>Coffee Machine</h2>
      <h3>Status: <span id="st">---</span></h3>
      <button class="btn on" onclick="toggleLED('on')">ON</button>
      <button class="btn off" onclick="toggleLED('off')">OFF</button>
    </body>
    </html>
  )rawliteral";
}

/* ---------- HANDLERS ---------- */
void handleRoot() {
  if (!server.hasArg("password") || server.arg("password") != loginPassword) {
    server.send(200, "text/html", loginPage());
    return;
  }
  server.send(200, "text/html", controlPage());
}

void handleToggle() {
  if (server.arg("password") != loginPassword) {
    server.send(403, "text/plain", "Denied");
    return;
  }

  if (server.arg("state") == "on") {
    digitalWrite(LED_PIN, HIGH);
    ledState = true;
  } else {
    digitalWrite(LED_PIN, LOW);
    ledState = false;
  }
  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  server.send(200, "text/plain", ledState ? "ON" : "OFF");
}

/* ---------- SETUP ---------- */
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("ESP32 AP Started");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP()); // 192.168.4.1

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.begin();
}

/* ---------- LOOP ---------- */
void loop() {
  server.handleClient();
}
