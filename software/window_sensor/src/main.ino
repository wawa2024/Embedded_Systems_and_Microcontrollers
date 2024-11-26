
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 imu;

const char* ssid = "main_hub";
const char* password = "12345678";
uint32_t lastMillis = 0;

struct AccelData {
  float x, y, z;
};

struct GyroData {
  float x, y, z;
};

const int max_history = 10;
AccelData accelHistory[max_history];
GyroData gyroHistory[max_history];
int currentIndex = 0;

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

  for (int i = 0; i < max_history; i++) {
    accelHistory[i] = {0, 0, 0};
    gyroHistory[i] = {0, 0, 0};
  }
  
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

  accelHistory[currentIndex] = {a.acceleration.x, a.acceleration.y, a.acceleration.z};
  gyroHistory[currentIndex] = {g.gyro.x, g.gyro.y, g.gyro.z};

  currentIndex++;
  
  AccelData averageAccel;
  GyroData averageGyro;

  for (int i = 0; i < max_history; i++) {
    averageAccel.x += accelHistory[i].x;
    averageAccel.y += accelHistory[i].y;
    averageAccel.z += accelHistory[i].z;
    averageGyro.x += gyroHistory[i].x;
    averageGyro.y += gyroHistory[i].y;
    averageGyro.z += gyroHistory[i].z;
  }

    averageAccel.x /= max_history;
    averageAccel.y /= max_history;
    averageAccel.z /= max_history;
    averageGyro.x /= max_history;
    averageGyro.y /= max_history;
    averageGyro.z /= max_history;

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
