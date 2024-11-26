
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "main_hub";
const char* password = "12345678";
uint32_t lastMillis = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();

  if (millis() - lastMillis() >= 5000 && 
        WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    
    http.begin(client, "http://192.168.4.1/hello");
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Received: " + payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();

    lastMillis = millis();
  }
}
