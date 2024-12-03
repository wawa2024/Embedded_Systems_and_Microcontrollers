#include <stdint.h>
#include <Arduino.h>
#include "procLogin.h"
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/matrixKeyboard/matrixKeyboard.h"

#define PASSWORD_LENGTH 7
#define SCREEN_OFFSET 6

void procLogin(void) {

  lcd.setColor(BLUE);
  lcd.clear();
  lcd.blink();
  lcd.print("login:");

  uint16_t i = 0;
  char* buf = pointBuf();
  bool flag = false;
  bool error = false;
  uint32_t time = 0;

  while ( true ) {

    readKeypad();
    char c = getPressedKey();

    switch ( c ) {

    case '0' ... '9': // password pin chars

      setBuf(c,i);
      lcd.write(c);

      if ( i != PASSWORD_LENGTH ) i++;

      break;

    case 'D': // delete char

      setBuf(0,i);
      lcd.write(' ');
      if ( i ) i--;
      lcd.setCursor(SCREEN_OFFSET + i,0);

      break;
      
    case '#': // enter password

      setBuf(0,PASSWORD_LENGTH + 1);

      flag = tryPassword(buf);

      if ( flag ) {

        lcd.clear();
        lcd.setColor(GREEN);
        lcd.stopBlink();
        return;

      } else {

        lcd.setColor(RED);
        time = millis();
        error = true;

      }

      break;

    default: break;

    }

    if ( error ) // error feedback
      if ( millis() > time + 3000 ) {
        error = false;
        lcd.setColor(BLUE);
      }
    
  }

}
