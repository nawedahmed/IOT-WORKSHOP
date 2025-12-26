#include <WiFi.h>
#include <WebServer.h>

#define RELAY_PIN 5   // D1 -> GPIO5

WebServer server(80);

// Relay state: false = OFF, true = ON
bool relayState = false;  

// ================= HTML PAGE =================
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;}";
  html += "button{font-size:25px;padding:15px 30px;margin:10px;}";
  html += "</style></head><body>";

  html += "<h2>ESP32 Bulb Control</h2>";

  if (relayState) {
    html += "<p>Status: <b>ON</b></p>";
    html += "<a href='/off'><button style='background:red;color:white'>OFF</button></a>";
  } else {
    html += "<p>Status: <b>OFF</b></p>";
    html += "<a href='/on'><button style='background:green;color:white'>ON</button></a>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);
}

// ================= HANDLERS =================
void handleOn() {
  relayState = true;
  digitalWrite(RELAY_PIN, LOW);   // ACTIVE LOW relay
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  relayState = false;
  digitalWrite(RELAY_PIN, HIGH);  // ACTIVE LOW relay
  server.sendHeader("Location", "/");
  server.send(303);
}

// ================= SETUP =================
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF

  // Start ESP32 in AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32-BULB", "12345678");

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.begin(115200);
  Serial.println("Web server started");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
}

// ================= LOOP =================
void loop() {
  server.handleClient();
}
