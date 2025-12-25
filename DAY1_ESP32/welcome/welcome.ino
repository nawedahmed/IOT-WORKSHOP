/*
 * Connect ESP32 to WiFi
 * Open the shown IP address in browser
 * ESP32 + phone/laptop must be on SAME WiFi
 */

#include <WiFi.h>

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";

WiFiServer server(80);   // HTTP server on port 80

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();   // Start server
  Serial.println("HTTP Server started");
}

void loop() {
  WiFiClient client = server.available();  // Check for client

  if (client) {
    Serial.println("New Client Connected");

    while (!client.available()) {
      delay(1);
    }

    client.readStringUntil('\r');  // Read request
    client.flush();

    // HTML response
    String html =
      "<!DOCTYPE html><html><head><title>IoT Workshop</title></head>"
      "<body style='display:flex;justify-content:center;align-items:center;height:100vh;'>"
      "<h1><b>Welcome to IoT Workshop by Electrical Club at Pulchowk Campus</b></h1>"
      "</body></html>";

    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Content-Type: text/html\r\n");
    client.print("Connection: close\r\n\r\n");
    client.print(html);

    client.stop();   // Close connection
    Serial.println("Client Disconnected");
  }
}
