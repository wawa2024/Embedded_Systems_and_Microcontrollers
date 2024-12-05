#include <Arduino.h>

#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"
#include "procLogin.h"

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
    Serial.write("Opening detected, you have 30 seconds\n");
    bool login_state = procLogin();
  }
}

void trigger_alarm() {
  Serial.write("Intrusion alert!\n");
}

void countdown() {
  if (login_state == true) {
    alarm_state = false;
  }

  if (alarm_state = true && millis() - alarm_time >= 3000 && alarm_state == true) {
    trigger_alarm();
  }
}
