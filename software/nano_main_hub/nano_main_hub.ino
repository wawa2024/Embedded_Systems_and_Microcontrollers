#include "Arduino.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/timer/timer.h"
#include "src/system/system.h"

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

  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial
  lcd.init(); // init lcd
  init_alarm(); // solo nano test setting
  // initPassword(); // init password
  Serial.write("\n");

}

void loop(void) {
  poll_alarm_state(); // solo nano test setting, comment rest of loop out

  if( not procLogin() ) // Exit if failed login
    return;

  if (alarm_state == true || alarm_activated == true) {
    disableAlarm();
  }

  for (uint8_t i ; i = procMenu() ; ) {
    // ^Main menu program loop

    switch(i) {

    case 1: armAlarm(); break;
    case 2: disarmAlarm(); break;
    case 3: changePassword(); break;
    case 4: storePassword(); break;

    default: break;

    }

    resetBuf(); // clean ioBuffer with zeroes

  }

}
