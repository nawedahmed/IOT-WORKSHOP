#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RELAY_PIN D1   // GPIO5

ESP8266WebServer server(80);

// Change if your relay is ACTIVE HIGH
bool relayState = false; // false = OFF, true = ON

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;}";
  html += "button{font-size:25px;padding:15px 30px;margin:10px;}";
  html += "</style></head><body>";

  html += "<h2>ESP8266 Bulb Control</h2>";

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

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF

  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP8266-BULB", "12345678");

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
