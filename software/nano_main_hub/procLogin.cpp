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
#include "alarmHandler.h"
#include "alarmStates.h"

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
  bool alarm_screen = false;

  uint32_t prev_time = millis();

  char prev_c = 0;
  char tmp_c = 0;

  bool debounce = true;
  bool repeat = false;

  delay(100); // initial debounce delay
  
  while ( true ) {

    if ( alarm_state and inside_menu ) return; // return if inside menu and alarm is on

    char c = getKey();
    uint32_t cur_time = millis();

    // error red feedback
    if ( error )
      lcd.setColor(RED);

    // timelapse feedback
    if ( cur_time > prev_time + 500 ) {

      if ( alarm_state ) {

        if ( alarm_screen )
          lcd.setColor(RED);
        else
          lcd.setColor(BG_COLOR);

        alarm_screen = not alarm_screen;

      } else {
        
        lcd.setColor(BG_COLOR);

        error = false;

      }

      prev_time = cur_time;
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

          if ( not alarm_state )
            Serial.write("Password accepted\n");

          lcdSuccess("Login accepted");

          resetBuf(); // clean ioBuffer with zeroes

          return true;

        } else {

          if ( attempts == MAX_TRIALS ) {

            Serial.write("Password rejected\n");
            lcdFail("Login rejected");

            resetBuf(); // clean ioBuffer with zeroes

            return false;

          }

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
