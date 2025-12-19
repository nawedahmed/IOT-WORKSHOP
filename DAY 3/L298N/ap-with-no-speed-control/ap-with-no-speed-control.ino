/*

INPUT 1  	  INPUT 2 	    DIRECTION
LOW  (0)    LOW  (0)	    Motor Off
HIGH (1)	  LOW  (0)	    Forward
LOW  (0)	  HIGH (1)	    Reverse
HIGH (1)	  HIGH (1)	    Motor Off


*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Motor pins
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D6
#define ENB D7

int speedMotor = 200;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  WiFi.softAP("ESP_CAR", "12345678");

  server.on("/", handleRoot);
  server.on("/F", forward);
  server.on("/B", backward);
  server.on("/L", leftTurn);
  server.on("/R", rightTurn);
  server.on("/S", stopMotors);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ESP8266 CAR</title>
<style>
button{width:90px;height:90px;font-size:20px;margin:10px;}
</style>
</head>
<body align="center">
<h2>WiFi Joystick</h2>
<button onclick="fetch('/F')">UP</button><br>
<button onclick="fetch('/L')">LEFT</button>
<button onclick="fetch('/S')">STOP</button>
<button onclick="fetch('/R')">RIGHT</button><br>
<button onclick="fetch('/B')">DOWN</button>
</body>
</html>
)rawliteral");
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
  server.send(200, "text/plain", "F");
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
  server.send(200, "text/plain", "B");
}

void leftTurn() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
  server.send(200, "text/plain", "L");
}

void rightTurn() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
  server.send(200, "text/plain", "R");
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "S");
}