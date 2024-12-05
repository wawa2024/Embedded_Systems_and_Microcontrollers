#include <stdint.h>
#include <Arduino.h>
#include "procLogin.h"
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/matrixKeyboard/matrixKeyboard.h"
#include "src/Debug/Debug.h"

#define PASSWORD_LENGTH 8
#define SCREEN_OFFSET 6
#define BG_COLOR WHITE
#define REFRESH_RATE 300
#define MAX_TRIALS 3
#define MSG_TIMEOUT 3000

bool procLogin(void) {

  lcd.setColor(BG_COLOR);
  lcd.clear();
  lcd.blink();
  lcd.setCursor(0,1); lcd.print("pin="); lcd.print(getPassword()); lcd.setCursor(0,0);
  lcd.print("login:");

  uint8_t attempts = 0;
  uint16_t i = 0;
  char* str = pointBuf();
  bool flag = false;
  bool error = false;
  bool debounce = true;
  bool repeat = false;
  uint32_t prev_time = millis();
  char prev_c = 0;

  char c;
  uint32_t cur_time;
  
  while ( true ) {

    c = getKey();
    cur_time = millis();

    DEBUG("error=",error);
    DEBUG("( cur_time > ( prev_time + 500 )=",( cur_time > ( prev_time + 500 )));
    DEBUG("cur_time=",cur_time);
    DEBUG("prev_time=",prev_time);
    DEBUG("millis()=",millis());
    
    // remove error red screen
    if ( error and ( cur_time > ( prev_time + 500 ) ) )
    {
      lcd.setColor(BG_COLOR);
      error = false;
    }
    
    if ( c != ' ' ) {

      Serial.print("keyPress:");
      Serial.print(c);
      Serial.println(" <-- keyPress debugger");

      if ( prev_c == c ) {

        if ( debounce ) {

          debounce = false;
          repeat = true;
          delay(100); // debounce timeout
          continue;

        }

        if ( repeat ) {

          delay(REFRESH_RATE); // refresh rate

        }

      } else {

        debounce = true;
        repeat = false;

      }

      prev_c = c;

      switch ( c ) {

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': // password pin chars

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
      
      case '#': // enter password

        setBuf(0,PASSWORD_LENGTH + 1);

        flag = tryPassword(str);

        if ( flag ) {

          lcd.clear();

          lcd.setColor(GREEN);
          lcd.stopBlink();

          delay(MSG_TIMEOUT);

          lcd.stopBlink();

          return true;

        } else {

          lcd.setColor(RED);
          prev_time = cur_time;
          error = true;

          if ( attempts == MAX_TRIALS ) {

            lcd.clear();
            lcd.print("Login failed");

            delay(MSG_TIMEOUT); // Display message MSG_TIMEOUT

            resetBuf(); // Reset string ioBuffer

            lcd.stopBlink();

            return false;
          }

          attempts++;
          
        }

        break;

      default: break;

      }
    }

    delay(10); // 100 Hz refresh

  }
  
}
