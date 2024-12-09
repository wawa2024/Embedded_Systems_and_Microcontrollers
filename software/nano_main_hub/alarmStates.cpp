#include "alarmStates.h"

volatile uint8_t armed_state = 1;
volatile bool alarm_state = false;
volatile bool login_state = false;
bool alarm_activated = false;
bool buzzer_state = false;
volatile uint32_t alarm_start_time = 0;
const uint16_t alarm_delay = 7700;
const uint16_t alert_cadence = 3000;

bool inside_menu = false;
