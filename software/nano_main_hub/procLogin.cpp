#include <stdint.h>
#include <Arduino.h>
#include "procLogin.h"
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/matrixKeyboard/matrixKeyboard.h"

#define PASSWORD_LENGTH 7
#define SCREEN_OFFSET 6
#define BG_COLOR WHITE
#define REFRESH_RATE 300
#define MAX_TRIALS 3

bool procLogin(void) {

  lcd.setColor(BG_COLOR);
  lcd.clear();
  lcd.blink();
  lcd.print("login:");

  uint8_t attempts = 0;
  uint16_t i = 0;
  char* buf = pointBuf();
  bool flag = false;
  bool error = false;
  uint32_t time = 0;
  char prev_c = 0;
  
  while ( true ) {

    readKeypad();
    char c = getPressedKey();
    
    if ( c != ' ' ) {

      Serial.print("keyPress:");
      Serial.println(c);

      if ( prev_c == c ) {
        delay(REFRESH_RATE); // refresh rate
      } 
      
      prev_c = c;

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
          delay(1000);
          lcd.clear();
          lcd.stopBlink();
          return true;

        } else {

          lcd.setColor(RED);
          time = millis();
          error = true;

          if ( attempts == MAX_TRIALS ) {
            lcd.clear();
            lcd.print("Login failed");
            delay(1000);
            lcd.clear();
            lcd.stopBlink();
            return false;
          }
          attempts++;
          
        }

        break;

      default: break;

      }

      if ( error ) // error feedback
        if ( millis() > time + 3000 ) {
          error = false;
          lcd.setColor(BG_COLOR);
        }
      Serial.print("ioBuffer:");
      Serial.println(buf);
    }

  }
  
}
