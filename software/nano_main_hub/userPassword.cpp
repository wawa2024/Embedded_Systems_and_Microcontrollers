#include <stdint.h>
#include "userPassword.h"
#include "src/eeprom/eeprom.h"

#define PASSWORD_SIZE 10

static char password[PASSWORD_SIZE];

bool tryPassword(char* str) {
// ^Try password

  for ( uint8_t i = 0 ; i < PASSWORD_SIZE ; i++ ) {

    if ( password[i] != str[i] )
      break;

    if ( password[i] == '\0' and str[i] == '\0' )
      return true;

    if ( password[i] == '\0' or str[i] == '\0' )
      break;
    
  }

  return false;
}

void setPassword(char* str) {
// ^Set password on device
  for ( uint8_t i = 0 ; i < PASSWORD_SIZE ; i++ ) {
    
    password[i] = str[i];
    
    if ( str[i] == '\0' )
      break;

  }
}

char* getPassword(void) {
  // ^Get password on device
  return password;
}

void savePassword(void) {
  // ^Save password into eeprom
  buffer2eeprom(0,PASSWORD_SIZE,password);
}

void initPassword(void) {
  // ^Get password register from eeprom
  eeprom2buffer(0,PASSWORD_SIZE,password);
}
