#include "Arduino.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "guiMessage.h"

#define MSG_TIMEOUT 1000

void lcdFail(char* msg) {
  // ^Display a visual fail message
  lcd.clear();
  lcd.setColor(RED);
  lcd.noCursor();
  lcd.print("Fail");
  lcd.setCursor(0,1);
  lcd.print(msg);
  delay(MSG_TIMEOUT);
}

void lcdSuccess(char* msg) {
  // ^Display a visual success message
  lcd.clear();
  lcd.setColor(GREEN);
  lcd.noCursor();
  lcd.print("Success");
  lcd.setCursor(0,1);
  lcd.print(msg);
  delay(MSG_TIMEOUT);
}
