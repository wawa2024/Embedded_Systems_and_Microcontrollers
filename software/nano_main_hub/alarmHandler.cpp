#include <Arduino.h>

#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"
#include "procLogin.h"
#include "guiMessage.h"

void init_alarm() {
  pinMode(interrupt_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), register_alarm, RISING);
}

void armAlarm() {
  armed_state = 1;
  lcdSuccess("Alarm armed");
//  procLogin();
}

void disarmAlarm() {
  armed_state = 0;
  alarm_state = 0;
  lcdSuccess("Alarm disarmed");

}

void disableAlarm() {
  alarm_state = false;
  lcdSuccess("Alarm disabled");
}

void register_alarm() {
  if (alarm_state == false) {
    alarm_time = millis();
  }

  if (armed_state == 1 && alarm_state == false) {
    alarm_state = true;
    Serial.write("Opening detected, you have 30 seconds\n");
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

  if (alarm_state == true && millis() - alarm_time >= 7000) {
    alarm_time = millis();
    trigger_alarm();
  }
}
