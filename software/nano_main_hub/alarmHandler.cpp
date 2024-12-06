#include <Arduino.h>

#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"
#include "procLogin.h"

bool init_alarm() {
  pinMode(interrupt_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), register_alarm, RISING);
}

void register_alarm() {
  if (alarm_state == false) {
    alarm_time = millis();
  }

  if (armed_state == 1 && alarm_state == false) {
    alarm_state = true;
    Serial.write("Opening detected, you have 30 seconds\n");
//    bool login_state = procLogin(); // doesn't work on solo nano
  }
}

void trigger_alarm() {
  Serial.write("Intrusion alert!\n");
}

void poll_alarm_state() {
  if (login_state == true) {
    alarm_state = false;
    Serial.write("Alarm disabled\n");
  }

  if (alarm_state == true && millis() - alarm_time >= 3000) {
    alarm_time = millis();
    trigger_alarm();
  }
}
