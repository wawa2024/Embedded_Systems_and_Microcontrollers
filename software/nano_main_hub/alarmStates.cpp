#include "alarmStates.h"

volatile uint8_t armed_state = 1;
volatile bool alarm_state = false;
volatile bool login_state = false;
bool alarm_activated = false;
bool buzzer_state = false;
volatile long long alarm_time = 0;
const uint16_t alarm_delay = 6000;
const uint16_t alert_cadence = 3000;
uint8_t alarm_countdown = 5;

const uint8_t interrupt_pin = 2;
const uint8_t buzzer_pin = 8;

bool inside_menu = false;
