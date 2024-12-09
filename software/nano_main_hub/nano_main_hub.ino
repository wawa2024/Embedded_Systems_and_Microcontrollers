#include "Arduino.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/timer/timer.h"
#include "src/system/system.h"
#include "src/matrixKeyboard/matrixKeyboard.h"

#include "ioBuffer.h"
#include "alarmHandler.h"
#include "alarmStates.h"
#include "userPassword.h"

#include "procSerial.h"
#include "procLogin.h"
#include "procMenu.h"
#include "procReboot.h"

#include "changePassword.h"
#include "storePassword.h"

#define BAUD_RATE 115200

#include "src/Debug/Debug.h"

void setup() {
  // ^Arduino nano init

  timer1_init();
  timer1_setCallback( ( void (*) (void) ) poll_alarm_state );

  timer2_init();
  timer2_setCallback( ( void (*) (void) ) readKeypad );

  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial
  Serial.write("\nSystem Booted\n"); // start Serial com esp32
  lcd.init(); // init lcd
  init_alarm(); // solo nano test setting
  initPassword(); // init password

}

void loop(void) {
  // ^Arduino nano main loop

  inside_menu = false;
  
  if( not procLogin() ) // Exit if failed login
    return;

  if (alarm_state == true || alarm_activated == true) {
    disableAlarm();
  }

  for (uint8_t i = procMenu() ; true ; i = procMenu() ) {
    // ^Main menu program loop

    inside_menu = true;

    switch(i) {

    case 0: armAlarm(); break;
    case 1: disarmAlarm(); break;
    case 2: changePassword(); break;
    case 3: storePassword(); break;
    case 4: procReboot(); break;
    case 5: return; break;

    default: break;

    }
    
    resetBuf(); // clean ioBuffer with zeroes

  }

}
