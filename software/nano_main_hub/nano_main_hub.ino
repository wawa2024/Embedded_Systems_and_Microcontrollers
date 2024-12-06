#include "Arduino.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/timer/timer.h"
#include "system.h"

#include "alarmHandler.h"
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

  // initPassword(); // init password

}

void loop(void) {

  if( not procLogin() ) // Exit if failed login
    return;

  for (uint8_t i ; i = procMenu() ; ) {
    // ^Main menu program loop

    switch(i) {

    case 1: changePassword(); break;
    case 2: storePassword(); break;

    default: break;

    }

  }

}
