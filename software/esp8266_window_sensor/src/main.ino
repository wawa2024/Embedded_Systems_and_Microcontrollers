
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 imu;

const char* ssid = "main_hub";
const char* password = "12345678";
uint32_t lastMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(D1, D2);
  WiFi.begin(ssid, password);

  if (!imu.begin()) {
    Serial.println("Didn't detect MPU6050");
    while (imu.begin() == false) {
      delay(10);
    }
  }
  Serial.println("MPU6050 detected");

  imu.setAccelerometerRange(MPU6050_RANGE_2_G);
  imu.setGyroRange(MPU6050_RANGE_250_DEG);
  
  imu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
/*  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
*/
}

void loop() {
  sensors_event_t a, g, temp;
  imu.getEvent(&a, &g, &temp);

  if ((millis() - lastMillis) % 50 == 0) {
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    Serial.println("");
  }


/*
  if (millis() - lastMillis >= 5000 && 
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
*/
}
