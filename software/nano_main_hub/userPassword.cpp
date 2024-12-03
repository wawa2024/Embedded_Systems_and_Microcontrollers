#include <stdint.h>
#include <Arduino.h>
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/eeprom/eeprom.h"

bool tryPassword(char* str) {
  // ^Try string with eeprom string

  for ( uint16_t i = 0 ; i < 256 ; i++ ) {
    eeprom_t cell;
    cell.addr = i;
    eeprom_read(cell);

    if ( cell.data != str[i] )
      return false;

    if ( cell.data == '\0' )
      return true;
    
  }

  return false;
}

void setPassword(char* str) {
  // ^Read string and write into eeprom

  for ( uint16_t i = 0 ; i < 256 ; i++ ) {
    eeprom_t cell;
    cell.addr = i;
    cell.data = str[i];
    eeprom_write(cell);

    if ( cell.data == '\0' )
      break;

  }
}

char* getPassword(void) {
  // ^Read eeprom and return string

  for ( uint16_t i = 0 ; i < 256 ; i++ ) {
    eeprom_t cell;
    cell.addr = i;
    eeprom_read(cell);
    pushBuf(cell.data,i);
    Serial.println(getBuf(i));
    
    if ( cell.data == '\0' )
      return pointBuf();

  }

  return NULL;
}
