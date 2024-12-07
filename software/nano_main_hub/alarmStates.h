#pragma once
#include <stdint.h>

extern volatile uint8_t armed_state;
extern volatile bool alarm_state;
extern volatile bool login_state;
extern bool alarm_activated;
extern bool buzzer_state;
extern volatile long long alarm_time;
extern const uint16_t alarm_delay;
extern const uint16_t alert_cadence;
extern uint8_t alarm_countdown;

extern const uint8_t interrupt_pin;
extern const uint8_t buzzer_pin;
