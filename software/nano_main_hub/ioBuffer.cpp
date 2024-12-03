#include <stdint.h>
#include "ioBuffer.h"
#define BUFFER_SIZE 80
constexpr int BUFFER_LIMIT = ( BUFFER_SIZE - 2 );

static uint8_t buf[BUFFER_SIZE];
// ^common buffer

uint8_t* pointBuf(void) {
  return buf;
}

bool pushBuf(uint8_t c, uint16_t i) {
// ^safe buffer push method

  if ( i > BUFFER_LIMIT ) {

    return true;

  } else {

    buf[i] = c;
    return false;

  }

}

uint8_t getBuf(uint16_t i) {
// ^safe buffer get method
  
  if ( i < BUFFER_LIMIT ) {

    return buf[i];

  } else { 

    return false;

  }

}
