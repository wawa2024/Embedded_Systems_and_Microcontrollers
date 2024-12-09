#pragma once
#include <stdint.h>

extern volatile bool armed_state;
extern volatile bool alarm_state;
extern volatile bool login_state;
extern bool alarm_activated;
extern bool buzzer_state;
extern volatile long long alarm_time;
extern const uint16_t alarm_delay;
extern const uint16_t alert_cadence;
extern uint8_t alarm_countdown;

extern bool inside_menu;
