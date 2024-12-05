#include <stdint.h>

extern volatile uint8_t armed_state;
extern volatile bool alarm_state;
extern volatile long long alarm_time;
extern volatile bool login_state;

extern uint8_t interrupt_pin;
