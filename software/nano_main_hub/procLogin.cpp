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

#define PASSWORD_LENGTH 8
#define SCREEN_OFFSET 6
#define BG_COLOR WHITE
#define REPEAT_RATE 300
#define MAX_TRIALS 3
#define MSG_TIMEOUT 3000

bool procLogin(void) {

  lcd.setColor(BG_COLOR);
  lcd.clear();
  lcd.blink();
  lcd.cursor();
  lcd.setCursor(0,1); lcd.print("pin="); lcd.print(getPassword()); lcd.setCursor(0,0); // comment out this section when used
  lcd.print("login:");

  uint8_t attempts = 0;
  uint16_t i = 0;

  char* str = pointBuf();
  bool error = false;

  uint32_t prev_time = millis();

  char prev_c = 0;
  char tmp_c = 0;

  bool debounce = true;
  bool repeat = false;

  while ( true ) {

    char c = getKey();
    uint32_t cur_time = millis();

    // remove error red screen
    if ( error and ( cur_time > ( prev_time + 500 ) ) )
    {
      lcd.setColor(BG_COLOR);
      error = false;
    }
    
    if ( c != ' ' ) {

      tmp_c = prev_c;
      prev_c = c;
      
      if ( keyDebounce( tmp_c == c, repeat, debounce) )
        continue;

      switch ( c ) {

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': // input pins

        if ( i < PASSWORD_LENGTH ) { 
          
          setBuf(c,i);

          lcd.setCursor(SCREEN_OFFSET + i,0);
          lcd.write(c);
          lcd.setCursor(SCREEN_OFFSET + i + 1,0);         
          
          i++;
        }

        break;

      case 'D': // delete

        if ( i ) i--;

        lcd.setCursor(SCREEN_OFFSET + i,0);
        setBuf(0,i);
        lcd.write(' ');
        lcd.setCursor(SCREEN_OFFSET + i,0);

        break;
      
      case '#': // enter 

        setBuf(0,PASSWORD_LENGTH + 1);

        if ( tryPassword(str) ) {

          lcdSuccess("Login accepted");

          return true;

        } else {

          if ( attempts == MAX_TRIALS ) {

            lcdFail("Login rejected");

            resetBuf(); // Reset string ioBuffer

            return false;

          }

          lcd.setColor(RED);
          prev_time = cur_time;
          error = true;
          attempts++;
          
        }

        break;

      default: break;

      }
    }

    delay(10); // 100 Hz refresh

  }
  
}
