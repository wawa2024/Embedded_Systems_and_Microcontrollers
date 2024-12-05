#include "alarmStates.h"

volatile uint8_t armed_state = 0;
volatile bool alarm_state = false;
volatile long long alarm_time = 0;
volatile bool login_state = false;

uint8_t interrupt_pin = 2;
