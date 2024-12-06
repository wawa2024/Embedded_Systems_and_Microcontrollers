#include <stdint.h>
#include <Arduino.h>
#include "userPassword.h"
#include "src/I2C_LCD/I2C_LCD.h"

#define MSG_TIMEOUT 3000

void storePassword(void) {
// ^store Password program

  savePassword();

  lcd.clear();
  lcd.noCursor();
  lcd.print("Password stored");
  lcd.setColor(GREEN);
  delay(MSG_TIMEOUT);

  lcd.cursor();
  
}
