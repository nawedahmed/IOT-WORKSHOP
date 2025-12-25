#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED 2  // Built-in LED (D4 on some boards)

const char* ssid = "realme 12x 5G";       // Your router SSID
const char* password = "12345678mm";      // Your router password

const char* ap_ssid = "ESP8266_AP";       // ESP AP SSID
const char* ap_pass = "12345678";         // ESP AP password

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
      "<meta name='viewport' content='width=device-width, initial-scale=1'>"
      "<style>"
        "body { display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; font-family: Arial; }"
        "button { width: 120px; height: 60px; font-size: 20px; margin: 10px; border-radius: 10px; }"
      "</style>"
    "</head>"
    "<body>"
      "<h2>ESP8266 AP + STA</h2>"
      "<a href='/on'><button>LED ON</button></a>"
      "<a href='/off'><button>LED OFF</button></a>"
    "</body>"
    "</html>"
  );
}


void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);  // LED OFF initially (built-in LED is active LOW)

  // Dual mode
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  WiFi.softAP(ap_ssid, ap_pass);

  Serial.println("\nESP8266 Dual Mode Started");
  Serial.print("AP IP Address: "); Serial.println(WiFi.softAPIP());

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Router");
  Serial.print("STA IP Address: "); Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/", handleRoot);
  server.on("/on", []() {
    digitalWrite(LED, LOW);    // Turn ON (built-in LED is active LOW)
    server.send(200, "text/plain", "LED ON");
  });
  server.on("/off", []() {
    digitalWrite(LED, HIGH);   // Turn OFF
    server.send(200, "text/plain", "LED OFF");
  });

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
