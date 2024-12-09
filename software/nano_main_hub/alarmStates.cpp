#include "alarmStates.h"

volatile bool armed_state = true;
volatile bool alarm_state = false;
volatile bool login_state = false;
bool alarm_activated = false;
bool buzzer_state = false;
volatile long long alarm_time = 0;
const uint16_t alarm_delay = 6000;
const uint16_t alert_cadence = 3000;
uint8_t alarm_countdown = 5;

bool inside_menu = false;
