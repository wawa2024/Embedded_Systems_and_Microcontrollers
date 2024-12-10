
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <cmath>

Adafruit_MPU6050 imu;

const char* ssid = "main_hub";
const char* password = "12345678";
uint32_t lastMillis = 0;
uint32_t alarmMillis = 0;
uint8_t magnetPin = D3;

bool alarm = false;
bool initialized = false;
uint8_t identifier = 0;
uint8_t magnetValue = 0;
uint8_t previousMagnetValue = 0;

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

void send_alarm();

void setup() {
  Serial.begin(115200);
  Wire.begin(D1, D2);
  WiFi.begin(ssid, password);
  pinMode(magnetPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

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

  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < max_history; i++) {
    accelHistory[i] = {0, 0, 0};
    gyroHistory[i] = {0, 0, 0};
  }
}

void loop() {
  sensors_event_t a, g, temp;
  imu.getEvent(&a, &g, &temp);

  accelHistory[currentIndex] = {a.acceleration.x, a.acceleration.y, a.acceleration.z};
  gyroHistory[currentIndex] = {g.gyro.x, g.gyro.y, g.gyro.z};

  previousMagnetValue = magnetValue;
  magnetValue = digitalRead(magnetPin);
  
  currentIndex++;
  if (currentIndex >= max_history) {
    currentIndex = 0;
    initialized = true;
  }
  
  AccelData averageAccel = {0, 0, 0};
  GyroData averageGyro = {0, 0, 0};

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


  if ((millis() - lastMillis) % 500 == 0) {
    Serial.print("Acceleration X: ");
    Serial.print(averageAccel.x);
    Serial.print(", Y: ");
    Serial.print(averageAccel.y);
    Serial.print(", Z: ");
    Serial.print(averageAccel.z);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(averageGyro.x);
    Serial.print(", Y: ");
    Serial.print(averageGyro.y);
    Serial.print(", Z: ");
    Serial.print(averageGyro.z);
    Serial.println(" rad/s");

    Serial.print("Magnet state: ");
    Serial.println(magnetValue);

    Serial.println("");
  }

  uint32_t currentMillis = millis();

  if (initialized == true) {
    if (std::abs(a.acceleration.x - averageAccel.x) > 1) {
      alarm = true;
      identifier = 1;
      alarmMillis = currentMillis;
    }

    if (std::abs(a.acceleration.y - averageAccel.y) > 1) {
      alarm = true; 
      identifier = 2; 
      alarmMillis = currentMillis;
    }

    if (std::abs(a.acceleration.z - averageAccel.z) > 1) {
      alarm = true;
      identifier = 3;
      alarmMillis = currentMillis;
    }

    if (std::abs(g.gyro.x - averageGyro.x) > 0.1) {
      alarm = true;
      identifier = 4;
      alarmMillis = currentMillis;
    }

    if (std::abs(g.gyro.y - averageGyro.y) > 0.1) {
      alarm = true;
      identifier = 5;
      alarmMillis = currentMillis;
    }

    if (std::abs(g.gyro.z - averageGyro.z) > 0.1) {
      alarm = true;
      identifier = 6;
      alarmMillis = currentMillis;
    }

    if (magnetValue != previousMagnetValue) {
      alarm = true;
      identifier = 7;
      alarmMillis = currentMillis;
    }

  }

  if (alarm == true && (currentMillis - alarmMillis) % 100 == 0) {
    Serial.print("Alarm ");
    send_alarm();
    Serial.println(identifier);
    digitalWrite(LED_BUILTIN, LOW);
    if (millis() - alarmMillis >= 2000) {
      Serial.print("Alarm timeout ");
      Serial.println(identifier);
      alarm = false;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

void send_alarm() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    
    http.begin(client, "http://192.168.4.1/alarm");
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Received: " + payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();
  }
}