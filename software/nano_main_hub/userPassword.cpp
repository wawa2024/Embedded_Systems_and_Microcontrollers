#include <stdint.h>
#include <Arduino.h>
#include "userPassword.h"
#include "ioBuffer.h"
#include "src/eeprom/eeprom.h"

static char password[PASSWORD_SIZE];
const int PASSWORD_LIMIT = PASSWORD_SIZE - 1;

void string2eeprom(char* str) {
// ^Read string and write into eeprom

  for ( uint16_t i = 0 ; i < PASSWORD_LIMIT ; i++ ) {
    eeprom_t cell;
    cell.addr = i;
    cell.data = str[i];
    eeprom_write(cell);

    if ( cell.data == '\0' )
      break;

  }
}

char* eeprom2string(void) {
// ^Read eeprom and return string

  char* str = pointBuf();

  for ( uint16_t i = 0 ; i < PASSWORD_LIMIT ; i++ ) {
    eeprom_t cell;
    cell.addr = i;
    eeprom_read(cell);
    setBuf(cell.data,i);
    
    if ( cell.data == '\0' )
      break;
  }

  return str;
}

bool tryPassword(char* str) {
// ^Try password

  for ( uint16_t i = 0 ; i < PASSWORD_LIMIT ; i++ ) {

    if ( password[i] != str[i] )
      break;

    if ( password[i] == '\0' )
      return true;
    
  }

  return false;
}

void setPassword(char* str) {
// ^Set password on device
  for ( uint16_t i = 0 ; i < PASSWORD_LIMIT ; i++ ) {
    
    password[i] = str[i];
    
    if ( str[i] == '\0' ) {
      break;
    }

  }
}

char* getPassword(void) {
// ^Get password on device
  return password;
}

void savePassword(void) {
// ^Save password into eeprom
  string2eeprom(password);
}

void initPassword(void) {
// ^Get password register from eeprom
  char* str = eeprom2string();
  if( str )
    setPassword(str);
}
