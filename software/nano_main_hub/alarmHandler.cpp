#include <Arduino.h>

#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"
#include "procLogin.h"
#include "guiMessage.h"
#include "src/eeprom/eeprom.h"

#define PIN_INPUT(REG,PIN) REG &= ~(1 << PIN)
// ^Set pin as input
#define PIN_OUTPUT(REG,PIN) REG |= (1 << PIN)
// ^Set pin as output

const uint8_t interrupt_pin = 2;
const uint8_t buzzer_pin = 8;

uint32_t last_tone_change = 0;
bool tone_increasing = true;
uint16_t tone_frequency = 1000;
uint32_t buzzer_time = 0;

const uint8_t alarm_state_address = 11;
eeprom_t alarm_state_eeprom = {
  alarm_state_address,
  false
};

const uint8_t armed_state_address = 12;
eeprom_t armed_state_eeprom = {
  armed_state_address,
  false
};

void init_alarm() {

  eeprom_read(alarm_state_eeprom);
  alarm_activated = alarm_state = alarm_state_eeprom.data;

  eeprom_read(armed_state_eeprom);
  armed_state = armed_state_eeprom.data;

  PIN_INPUT(DDRD,DDD2);
  // ^pinMode(interrupt_pin, INPUT);

  PIN_OUTPUT(DDRB,DDB0);
  // pinMode(buzzer_pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(interrupt_pin), register_alarm, RISING);
}

void armAlarm() {
  armed_state = true;
  armed_state_eeprom.data = armed_state;
  eeprom_write(armed_state_eeprom);
  Serial.write("Alarm armed\n");
  lcdSuccess("Alarm armed");
}

void disarmAlarm() {
  armed_state = 0;
  armed_state_eeprom.data = armed_state;
  eeprom_write(armed_state_eeprom);
  Serial.write("Alarm disarmed\n");
  lcdSuccess("Alarm disarmed");
}

void disableAlarm() {
  buzzer_state = alarm_activated = alarm_state = false;

  alarm_state_eeprom.data = alarm_state;
  eeprom_write(alarm_state_eeprom);

  digitalWrite(buzzer_pin, buzzer_state);
  Serial.write("Alarm dis abled successfully\n");
  lcdSuccess("Alarm disabled");
}

void register_alarm() {
  if (alarm_state == false) {
    alarm_start_time = millis();
    buzzer_time = 0;
  }

  if (armed_state == true and alarm_state == false) {
    alarm_state = true;
    alarm_state_eeprom.data = alarm_state;
    eeprom_write(alarm_state_eeprom);
    Serial.write("Opening detected, you have thirty seconds\n");
  }
}

void trigger_alarm() {
  Serial.write("Intrusion alert!\n");
}

bool poll_alarm_state() {
  uint32_t current_millis = millis();

  if (alarm_state == false) {
    return false;
  }

  if (alarm_activated == false) {
    if (buzzer_state == true and current_millis - alarm_start_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 200;
      buzzer_state = not buzzer_state;
    }

    if (buzzer_state == false and current_millis - alarm_start_time >= buzzer_time) {
      digitalWrite(buzzer_pin, buzzer_state);
      buzzer_time += 800;
      buzzer_state = not buzzer_state;
    }

    if (current_millis - alarm_start_time >= alarm_delay) {
      alarm_start_time = current_millis;
      trigger_alarm();
      alarm_activated = true;
      buzzer_state = false;
      buzzer_time = 0;
    }
  }

  if (alarm_activated == true) {
    if (current_millis - alarm_start_time >= alert_cadence) {
      alarm_start_time = current_millis;
      trigger_alarm();
    }
    if (current_millis - last_tone_change >= 2) {
      buzzer_state = true;
      last_tone_change = current_millis;
      if (tone_increasing) {
        tone_frequency += 10;
        if (tone_frequency >= 2000) tone_increasing = false;
      } else {
        tone_frequency -= 10;
        if (tone_frequency <= 1000) tone_increasing = true;
      }

      tone(buzzer_pin, tone_frequency);
    }
  }

  return true;
}
