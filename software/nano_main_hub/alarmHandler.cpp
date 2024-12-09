#include <Arduino.h>

#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"
#include "procLogin.h"
#include "guiMessage.h"

uint32_t buzzer_time = 0;

void init_alarm() {
  pinMode(interrupt_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), register_alarm, RISING);
}

void armAlarm() {
  armed_state = 1;
  Serial.write("Alarm armed\n");
  lcdSuccess("Alarm armed");
}

void disarmAlarm() {
  armed_state = 0;
  alarm_state = false;
  alarm_activated = false;
  buzzer_state = false;
  digitalWrite(buzzer_pin, buzzer_state);
  Serial.write("Alarm disarmed\n");
  lcdSuccess("Alarm disarmed");
}

void disableAlarm() {
  alarm_state = false;
  alarm_activated = false;
  buzzer_state = false;
  digitalWrite(buzzer_pin, buzzer_state);
  Serial.write("Alarm dis abled successfully\n");
  lcdSuccess("Alarm disabled");
}

void register_alarm() {
  if (alarm_state == false) {
    alarm_time = millis();
    buzzer_time = 0;
  }

  if (armed_state == 1 && alarm_state == false) {
    alarm_state = true;
    Serial.write("Opening detected, you have thirty seconds\n");
  }
}

void trigger_alarm() {
  Serial.write("Intrusion alert!\n");
}

bool poll_alarm_state() {
  if (alarm_state == false) {}
    return false;
  }

  if (alarm_activated == false) {
    if (buzzer_state == true && millis() - alarm_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 200;
      buzzer_state = !buzzer_state;
    }

    if (buzzer_state == false && millis() - alarm_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 800;
      buzzer_state = !buzzer_state;
    }

    if (millis() - alarm_time >= alarm_delay) {
      alarm_time = millis();
      trigger_alarm();
      alarm_activated = true;
      buzzer_state = false;
      buzzer_time = 0;
    }
  }

  if (alarm_activated == true) {
    if (millis() - alarm_time >= alert_cadence) {
      alarm_time = millis();
      trigger_alarm();
    }
    
    if (buzzer_state == true && millis() - alarm_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 100;
      buzzer_state = !buzzer_state;
    }

    if (buzzer_state == false && millis() - alarm_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 400;
      buzzer_state = !buzzer_state;
    }
  }

  return true;
}
