
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <cmath>

Adafruit_MPU6050 imu;

const char* sensor_type = "window";
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

AccelData averageAccel = {0, 0, 0};
GyroData averageGyro = {0, 0, 0};

AccelData previousStableAccel = {0, 0, 0};
GyroData previousStableGyro = {0, 0, 0};

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

  averageAccel = {0, 0, 0};
  averageGyro = {0, 0, 0};
  
  set_averages();

  previousMagnetValue = magnetValue;
  magnetValue = digitalRead(magnetPin);
  
  currentIndex++;
  if (currentIndex >= max_history) {
    currentIndex = 0;
    initialized = true;
  }

  if (millis() - lastMillis >= 500) {
    log_values();
    lastMillis = millis();
  }

  if (initialized == true) {
    if (std::abs(a.acceleration.x - averageAccel.x) > 1) {
      register_alarm(1);
    }

    if (std::abs(a.acceleration.y - averageAccel.y) > 1) {
      register_alarm(2);
    }

    if (std::abs(a.acceleration.z - averageAccel.z) > 1) {
      register_alarm(3);
    }

    if (std::abs(g.gyro.x - averageGyro.x) > 0.1) {
      register_alarm(4);
    }

    if (std::abs(g.gyro.y - averageGyro.y) > 0.1) {
      register_alarm(5);
    }

    if (std::abs(g.gyro.z - averageGyro.z) > 0.1) {
      register_alarm(6);
    }

    if (magnetValue != previousMagnetValue) {
      register_alarm(7);
    }
  }

  if (alarm == true && (millis() - alarmMillis) % 100 == 0) {
    send_alarm();

    if (millis() - alarmMillis >= 2000) {
      Serial.print("Alarm timeout ");
      Serial.println(identifier);
      alarm = false;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

void register_alarm(uint8_t identifier) {
  alarm = true;
  previousStableAccel = averageAccel;
  previousStableGyro = averageGyro;
  identifier = identifier;
  alarmMillis = millis();

  send_alarm();
}

void send_alarm() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);

    HTTPClient http;
    WiFiClient client;
    
    http.begin(client, "http://192.168.4.1/alarm");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(sensor_type);

    Serial.print("Alarm ");
    
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Received: " + response);
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();

    Serial.println(identifier);
  }
}

void set_averages() {
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
}

void log_values() {
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