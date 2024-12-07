#include <stdint.h>
#include <Arduino.h>
#include "src/I2C_LCD/I2C_LCD.h"
#include "src/matrixKeyboard/matrixKeyboard.h"
#include "src/Debug/Debug.h"
#include "src/keyGuard/keyGuard.h"
#include "alarmHandler.h"

#define BG_COLOR WHITE

enum scrollDirection { scrollUp = 0, scrollDown = 1 };
enum screenItem { screenTop = 0, screenBottom = 1 };

char* items[] = { "Arm alarm"
  , "Disarm alarm"
  , "Change Password"
  , "Store Password"
  , "Exit"
};

const uint8_t amount_items = sizeof(items) / sizeof(char*);

void tailMenu(int8_t i ,uint8_t screenRow) {
  // ^Draw tail item
  if ( 0 <= i and i < amount_items ) {
    lcd.setCursor(0,screenRow);
    lcd.print(" "); lcd.print(items[i]);
  }
}

void headMenu(int8_t i ,uint8_t screenRow) {
  // ^Draw head item
  lcd.setCursor(0,screenRow);
  lcd.print(">"); lcd.print(items[i]);
}

void drawMenu(scrollDirection scrollVal, int8_t i) {
  // ^Draw items on screen

  lcd.clear();
  
  switch(scrollVal) {

  case scrollUp:
    headMenu(i,screenTop);
    tailMenu(i+1,screenBottom);
    break;

  case scrollDown:
    tailMenu(i-1,screenTop);
    headMenu(i,screenBottom);
    break;

  default: break;

  }
  
}

uint8_t procMenu(void) {
// ^Menu program, returns an index of menu item

  lcd.setColor(BG_COLOR);
  lcd.noCursor();
  lcd.stopBlink();
  lcd.clear();

  uint8_t i = 0;

  drawMenu(scrollUp,i);

  bool repeat = false;
  bool debounce = true;

  char prev_c = 0;
  char tmp_c = 0;

  delay(100); // initial debounce delay

  while ( true ) {
    if (poll_alarm_state()) return 4; ; // need to poll the alarm while in infinite loop

    char c = getKey();

    if ( c != ' ' ) {

      tmp_c = prev_c;
      prev_c = c;

      if ( keyDebounce( tmp_c == c, repeat, debounce) )
        continue;

      switch ( c ) {

      case 'A': // scroll up
        if ( i ) i--;
        drawMenu(scrollUp,i);
        break;

      case 'B': // scroll down
        if ( i < amount_items ) i++;
        if ( i == amount_items ) i--;
        drawMenu(scrollDown,i);
        break;

      case '#': // enter
        lcd.clear();
        lcd.cursor();
        return i;
        break;

      default: break;
      }

    }

    delay(10); // 100 Hz

  }
  
}
