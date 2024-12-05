#include "procSerial.h"
#include "procLogin.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "alarmHandler.h"
#include "userPassword.h"

#define BAUD_RATE 115200

#include "src/Debug/Debug.h"

void setup() {

  lcd.init(); // init I2C lcd
  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial
  init_alarm();
  // initPassword(); // read saved eeprom2 password and save to register
}

void loop(void) {

  if( procLogin() ) {
    for(;;) {
      mirrorSerial();
    }
  }

}
