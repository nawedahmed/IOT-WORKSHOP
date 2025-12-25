/* 
 *  Welcome by connecting to wifi and its give ip address copy that to the browser.
 *  Note: esp8266 and laptop or mobile whatever you are using should connected to the same wifi to see the welcome message.
 */

#include <ESP8266WiFi.h>       // For Wi-Fi connection
#include <ESP8266WebServer.h>  // For HTTP server

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";

ESP8266WebServer server(80);  // HTTP server on port 80

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");

  unsigned long startTime = millis();

  // Timeout after 15 sec
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Define root URL handler
    server.on("/", []() {
      server.send(200, "text/html",
        "<html><body style='text-align:center;'>"
        "<h1>Welcome to IoT Workshop<br>Electrical Club, Pulchowk Campus</h1>"
        "</body></html>"
      );
    });

    server.begin();
    Serial.println("HTTP Server started");
  } else {
    Serial.println("\nWi-Fi connection failed!");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();  // Handle incoming clients
  }
}
