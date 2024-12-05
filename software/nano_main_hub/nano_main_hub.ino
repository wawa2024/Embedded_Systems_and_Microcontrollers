#include "procSerial.h"
#include "procLogin.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "alarmHandler.h"

#define BAUD_RATE 115200

void setup() {

  lcd.init(); // init I2C lcd
  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial
  init_alarm();
}

void loop(void) {

  procLogin();

  for(;;) {
    mirrorSerial();
  }

}
