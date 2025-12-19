//  This is code for controlling single motor in station mode means esp8266 is connected with wifi.

#include <ESP8266WiFi.h>

const char* ssid = "realme 12x 5G";
const char* password = "12345678mm";


// Motor pins
const int IN1 = D1; // GPIO5
const int IN2 = D2; // GPIO4
const int ENA = D3; // GPIO0 (PWM)

WiFiServer server(80);
int motorSpeed = 512; // default speed (0-1023)

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Motor direction control
    if (request.indexOf("/FWD") != -1) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, motorSpeed);
      Serial.println("Motor Forward");
    }
    if (request.indexOf("/BWD") != -1) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, motorSpeed);
      Serial.println("Motor Backward");
    }
    if (request.indexOf("/STOP") != -1) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      Serial.println("Motor Stopped");
    }

    // Motor speed control via slider
    if (request.indexOf("/SPEED?value=") != -1) {
      int index = request.indexOf("=") + 1;
      String val = request.substring(index);
      int speedPercent = val.toInt(); // 0-100
      motorSpeed = map(speedPercent, 0, 100, 0, 1023); // map to PWM
      analogWrite(ENA, motorSpeed);
      Serial.print("Motor Speed: ");
      Serial.println(speedPercent);
    }

    // Send web page with buttons + slider
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print("<!DOCTYPE html><html><head><title>DC Motor Control</title></head><body>");
    client.print("<h1>DC Motor Control</h1>");
    client.print("<p><a href=\"/FWD\">Forward</a></p>");
    client.print("<p><a href=\"/BWD\">Backward</a></p>");
    client.print("<p><a href=\"/STOP\">Stop</a></p>");
    client.print("<p>Speed: <input type='range' min='0' max='100' value='50' oninput='updateSpeed(this.value)'></p>");
    client.print("<script>");
    client.print("function updateSpeed(val){");
    client.print("var xhttp = new XMLHttpRequest();");
    client.print("xhttp.open('GET','/SPEED?value='+val,true);");
    client.print("xhttp.send();}");
    client.print("</script>");
    client.print("</body></html>");
    client.stop();
  }
}
