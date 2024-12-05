#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "main_hub";
const char* password = "12345678";

uint32_t lastMillis = 0;
uint32_t alarmMillis = 0;

ESP8266WebServer server(80);

void handleRoot();

void setup() {
  Serial.begin(115200);

  pinMode(D1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  WiFi.softAP(ssid, password);
  
  IPAddress server_IP = WiFi.softAPIP();
  Serial.print("Main hub IP address: ");
  Serial.println(server_IP);
  
  server.on("/", handle_root);
  server.on("/alarm", handle_alarm);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (millis() - alarmMillis >= 80) {
    digitalWrite(D1, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    alarmMillis = millis();
  }

  if (millis() - lastMillis >= 10000) {
    Serial.println("Server online");
    lastMillis = millis();
  }
}

void handle_root() {
  server.send(200, "text/html", "<h1>Main hub server</h1>");
}

void handle_alarm() {
  Serial.println("Alarm received");
  digitalWrite(D1, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "Alarm received");
  alarmMillis = millis();
}
