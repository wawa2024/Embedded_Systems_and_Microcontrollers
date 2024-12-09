#include <stdint.h>
#include <Arduino.h>
#include "src/system/system.h"
#include "src/I2C_LCD/I2C_LCD.h"

void procReboot(void) {
// ^Reboot program

  lcd.clear();
  lcd.noCursor();
  lcd.print("Rebooting...");
  Serial.write("rebooting\n");

  delay(500); // message delay
  
  system_reboot();

}
