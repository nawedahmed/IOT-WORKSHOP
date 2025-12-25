/* 
 
This project shows how an ESP32 works in AP mode to control GPIO pins like a switch within Wi-Fi range.
The device creates its own secured network with a password and a login page, demonstrating practical, secure, and local control for real-world IoT applications.
*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Coffee Machine";
const char* password = "coffee@#123";
const char* loginPassword = "coffee123";

ESP8266WebServer server(80);
bool ledState = false;

#define LED_PIN 5  // D1 on NodeMCU

String loginPage() {
  return R"====(
    <html>
    <head>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <style>
        body { font-family: Arial; text-align: center; background: #f2f2f2; padding-top: 50px; }
        form { background: white; display: inline-block; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px #aaa; }
        input[type=password], input[type=submit] {
          padding: 10px; margin: 10px; width: 200px; border-radius: 5px; border: 1px solid #ccc;
        }
        input[type=submit] {
          background: #007BFF; color: white; border: none;
        }
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

String controlPage() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <style>
        body { font-family: Arial; text-align: center; background-color: #f4f4f4; padding-top: 30px; }
        h2 { color: #333; }
        .status { font-size: 20px; margin: 20px; }
        .btn {
          display: inline-block;
          padding: 15px 25px;
          margin: 10px;
          font-size: 18px;
          cursor: pointer;
          text-decoration: none;
          border: none;
          border-radius: 8px;
        }
        .on { background-color: #28a745; color: white; }
        .off { background-color: #dc3545; color: white; }
      </style>
      <script>
        function toggleLED(state) {
          fetch("/toggle?state=" + state + "&password=coffee123")
            .then(response => response.text())
            .then(text => console.log(text));
        }

        function refreshStatus() {
          fetch("/status")
            .then(response => response.text())
            .then(state => {
              document.getElementById("ledStatus").innerHTML = "Status: <b>" + state + "</b>";
            });
        }

        setInterval(refreshStatus, 1000); // Update every 1 sec
        window.onload = refreshStatus;
      </script>
    </head>
    <body>
      <h2> Coffee Machine </h2>
      <div class='status' id='ledStatus'>Status: <b>...</b></div>
      <button class='btn on' onclick="toggleLED('on')">Turn ON</button>
      <button class='btn off' onclick="toggleLED('off')">Turn OFF</button>
    </body>
    </html>
  )rawliteral";

  return html;
}

void handleRoot() {
  if (!server.hasArg("password") || server.arg("password") != loginPassword) {
    server.send(200, "text/html", loginPage());
    return;
  }
  server.send(200, "text/html", controlPage());
}

void handleToggle() {
  if (server.arg("password") != loginPassword) {
    server.send(403, "text/plain", "Access Denied");
    return;
  }

  String state = server.arg("state");
  if (state == "on") {
    digitalWrite(LED_PIN, HIGH);  // LED ON
    ledState = true;
  } else if (state == "off") {
    digitalWrite(LED_PIN, LOW); // LED OFF
    ledState = false;
  }
  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  server.send(200, "text/plain", ledState ? "ON" : "OFF");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // LED OFF at startup
  ledState = false;

  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("AP Started. Visit http://192.168.4.1");

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();
}
