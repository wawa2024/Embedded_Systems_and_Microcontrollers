#include "Arduino.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/timer/timer.h"
#include "src/system/system.h"

#include "ioBuffer.h"
#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"

#include "procSerial.h"
#include "procLogin.h"
#include "procMenu.h"

#include "changePassword.h"
#include "storePassword.h"

#define BAUD_RATE 115200

#include "src/Debug/Debug.h"

void setup() {

  // v Maybe not put too many abstraction onto init process? 
  // system_init(/*void (*timer1_callback) (void)*/ PUT_FUNC1_HERE, /*void (*timer2_callback) (void)*/ PUT_FUNC2_HERE); // Init system 
  timer1_init();
  timer1_setCallback( ( void(*) (void) ) poll_alarm_state);

  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial
  lcd.init(); // init lcd
  init_alarm(); // solo nano test setting
  // initPassword(); // init password
  Serial.write("\n");

}

void loop(void) {

  if( not procLogin() ) // Exit if failed login
    return;

  if (alarm_state == true || alarm_activated == true) {
    disableAlarm();
  }

  for (uint8_t i = procMenu() ; true ; i = procMenu() ) {
    // ^Main menu program loop

    switch(i) {

    case 0: armAlarm(); break;
    case 1: disarmAlarm(); break;
    case 2: changePassword(); break;
    case 3: storePassword(); break;
    case 4: return; break;

    default: break;

    }
    
    resetBuf(); // clean ioBuffer with zeroes

  }

}
