#include "alarmHandler.h"
#include "states.h"
#include "userPassword.h"
#include "procLogin.h"
#include <Arduino.h>

bool init_alarm() {
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), register_alarm, RISING);
}

void poll_alarm() {
  countdown();
}

void register_alarm() {
  if (alarm_state == false) {
    alarm_time = millis();
  }

  if (armed_state == 1) {
    alarm_state = true;
    Serial.println("Opening detected, you have 30 seconds");
    Serial.write("Opening detected, you have 30 seconds");
    bool login_state = procLogin();
  }
}

void trigger_alarm() {
  Serial.println("Intrusion alert!");
  Serial.write("Intrusion alert!");
}

void countdown() {
  if (login_state == true) {
    alarm_state = false;
  }

  if (alarm_state = true && millis() - alarm_time >= 3000 && alarm_state == true) {
    trigger_alarm();
  }
}
