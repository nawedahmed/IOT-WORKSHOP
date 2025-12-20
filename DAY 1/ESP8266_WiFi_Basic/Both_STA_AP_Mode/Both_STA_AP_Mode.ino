#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED D1

// Router credentials (STA)
const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";

// AP credentials
const char* ap_ssid = "ESP8266_AP";
const char* ap_pass = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<h2>ESP8266 AP + STA</h2>"
    "<a href='/on'><button>LED ON</button></a>"
    "<a href='/off'><button>LED OFF</button></a>"
  );
}

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  WiFi.mode(WIFI_AP_STA);

  // STA mode
  WiFi.begin(ssid, password);

  // AP mode
  WiFi.softAP(ap_ssid, ap_pass);

  // -------- SERIAL INFO (IMPORTANT FOR STUDENTS) --------
  Serial.println("\nESP8266 Dual Mode Started");

  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());   // AP IP

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Router");
  Serial.print("STA IP Address: ");
  Serial.println(WiFi.localIP());    // STA IP
  // -----------------------------------------------------

  server.on("/", handleRoot);

  server.on("/on", []() {
    digitalWrite(LED, HIGH);
    server.send(200, "text/plain", "LED ON");
  });

  server.on("/off", []() {
    digitalWrite(LED, LOW);
    server.send(200, "text/plain", "LED OFF");
  });

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}















// ------ Simplified code but nothing show in serial monitor but work properly


//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
//
//#define LED D1
//
//// Router credentials (STA)
//const char* ssid = "realme 12x 5G";
//const char* password = "12345678mm";
//
//// AP credentials
//const char* ap_ssid = "ESP8266_AP";
//const char* ap_pass = "12345678";
//
//ESP8266WebServer server(80);
//
//void handleRoot() {
//  server.send(200, "text/html",
//    "<h2>ESP8266 AP + STA</h2>"
//    "<a href='/on'><button>LED ON</button></a>"
//    "<a href='/off'><button>LED OFF</button></a>"
//  );
//}
//
//void setup() {
//  pinMode(LED, OUTPUT);
//  digitalWrite(LED, LOW);
//
//  WiFi.mode(WIFI_AP_STA);
//
//  // STA mode
//  WiFi.begin(ssid, password);
//
//  // AP mode
//  WiFi.softAP(ap_ssid, ap_pass);
//
//  server.on("/", handleRoot);
//  server.on("/on", []() {
//    digitalWrite(LED, HIGH);
//    server.send(200, "text/plain", "LED ON");
//  });
//  server.on("/off", []() {
//    digitalWrite(LED, LOW);
//    server.send(200, "text/plain", "LED OFF");
//  });
//
//  server.begin();
//}
//
//void loop() {
//  server.handleClient();
//}
