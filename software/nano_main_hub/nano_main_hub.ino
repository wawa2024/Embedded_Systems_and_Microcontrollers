#include "procSerial.h"
#include "procLogin.h"
#include "src/I2C_LCD/I2C_LCD.h"

#define BAUD_RATE 115200

void setup() {

  lcd.init(); // init I2C lcd
  Serial.begin(BAUD_RATE,SERIAL_8N1); // init Serial

}

void loop(void) {
  if( procLogin() ) {
    for(;;) {
      mirrorSerial();
    }
  }
}
