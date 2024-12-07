#include <stdint.h>
#include <Arduino.h>
#include "procLogin.h"
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/matrixKeyboard/matrixKeyboard.h"
#include "src/keyGuard/keyGuard.h"
#include "src/Debug/Debug.h"
#include "guiMessage.h"
#include "storePassword.h"
#include "alarmStates.h"

#define PASSWORD_LENGTH 8
#define SCREEN_OFFSET 4
#define BG_COLOR WHITE
#define MSG_TIMEOUT 3000

void changePassword(void) {
// ^change password program

  if ( not procLogin() )
    return;

  lcd.setColor(BG_COLOR);
  lcd.clear();
  lcd.blink();
  lcd.print("pin:");

  uint8_t i = 0;
  char* str = pointBuf();
  bool debounce = true;
  bool repeat = false;
  char prev_c = 0;
  char tmp_c = 0;

  delay(100); // initial debounce delay

  while ( true ) {

    if (alarm_state) return;

    char c = getKey();

    if ( c != ' ' ) {

      tmp_c = prev_c;
      prev_c = c;
      
      if ( keyDebounce( tmp_c == c, repeat, debounce) )
        continue;

      switch ( c ) {

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': // password pins

        if ( i < PASSWORD_LENGTH ) { 
          
          setBuf(c,i);

          lcd.setCursor(SCREEN_OFFSET + i,0);
          lcd.write(c);
          lcd.setCursor(SCREEN_OFFSET + i + 1,0);         
          
          i++;
        }

        break;

      case 'D': // delete char

        if ( i ) i--;

        lcd.setCursor(SCREEN_OFFSET + i,0);
        setBuf(0,i);
        lcd.write(' ');
        lcd.setCursor(SCREEN_OFFSET + i,0);

        break;
      
      case '#': // enter

        setBuf(0,PASSWORD_LENGTH + 1);

        setPassword(str);

        lcdSuccess("Password changed");

        storePassword();

        return;

        break;

      default: break;

      }
    }

    delay(10); // 100 Hz refresh

  }
  
}
