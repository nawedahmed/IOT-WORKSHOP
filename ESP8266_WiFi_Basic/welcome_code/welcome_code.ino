/* 
 *  Welcome by connecting to wifi and its give ip address copy that to the browser.
 *  Note: esp8266 and laptop or mobile whatever you are using should connected to the same wifi to see the welcome message.
 */


#include <ESP8266WiFi.h>

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";


WiFiServer server(80); // HTTP server on port 80

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password); // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  

  server.begin(); // Start HTTP server
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming client

  if (client) {
    String request = client.readStringUntil('\r'); // Read request
    client.flush();

    // HTML content
    String html = "<!DOCTYPE html><html><head><title>IoT Workshop</title></head>"
                  "<body style='display:flex;justify-content:center;align-items:center;height:100vh;'>"
                  "<h1><b>Welcome to IoT Workshop by Electrical Club at Pulchowk Campus </b></h1>"
                  "</body></html>";

    // Send HTTP response
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print(html);

    client.stop(); // Close connection
  }
}
