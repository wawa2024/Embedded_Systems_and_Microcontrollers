#include <stdint.h>
#include <Arduino.h>
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/matrixKeyboard/matrixKeyboard.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/keyGuard/keyGuard.h"
#include "guiMessage.h"
#include "alarmStates.h"

#define MSG_TIMEOUT 3000
#define SCREEN_OFFSET 11
#define BG_COLOR WHITE

#define RESPONSE_LENGTH 1

#define PROMPT_ROW 1

void storePassword(void) {
  // ^store Password program

  while ( true ) {

    lcd.clear();
    lcd.cursor();
    lcd.setColor(BG_COLOR);
    lcd.print("Write to eeprom?");
    lcd.setCursor(0,1);
    lcd.print("yes=1,no=0:");

    bool debounce = true;
    bool repeat = false;

    char prev_c = 0;
    char tmp_c = 0;
    uint8_t i = 0;
    
    delay(100); // initial debounce delay

    for ( bool boolScan = true ; boolScan ; ) {
      if (alarm_state) return;

      char c = getKey();

      if ( c != ' ' ) {

        tmp_c = prev_c;
        prev_c = c;
      
        if ( keyDebounce( tmp_c == c, repeat, debounce) )
          continue;

        switch ( c ) {

        case '0': case '1': // response pins

          if ( i < RESPONSE_LENGTH ) { 
          
            setBuf(c,i);

            lcd.setCursor(SCREEN_OFFSET + i,PROMPT_ROW);
            lcd.write(c);
            lcd.setCursor(SCREEN_OFFSET + i + 1,PROMPT_ROW);         
          
            i++;
          }

          break;

        case 'D': // delete char

          if ( i ) i--;

          lcd.setCursor(SCREEN_OFFSET + i,PROMPT_ROW);
          setBuf(0,i);
          lcd.write(' ');
          lcd.setCursor(SCREEN_OFFSET + i,PROMPT_ROW);

          break;
      
        case '#': // enter

          switch( getBuf(0) ) {

          case '0':

            return;

            break;

          case '1':

            savePassword();
            Serial.write("Password stored\n");
            lcdSuccess("Password stored");
            return;

            break;

          default:

            lcdFail("No input");
            boolScan = false;

            break;
          }

          break;

        default:

          lcdFail("Unrecognized key");
          boolScan = false;

          break;

        }
      }
      
      delay(10); // 100 Hz refresh

    }
  
  }

}
