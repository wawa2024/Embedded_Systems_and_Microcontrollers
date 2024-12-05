#include <stdint.h>
#include "ioBuffer.h"
#define BUFFER_SIZE 80
const uint16_t BUFFER_LIMIT = ( BUFFER_SIZE - 2 );

static uint8_t ioBuffer[BUFFER_SIZE];
// ^common buffer

uint8_t* pointBuf(void) {
  return ioBuffer;
}

bool setBuf(uint8_t c, uint16_t i) {
// ^safe buffer set method

  if ( i > BUFFER_LIMIT ) {

    return true;

  } else {

    ioBuffer[i] = c;
    return false;

  }

}

uint8_t getBuf(uint16_t i) {
// ^safe buffer get method
  
  if ( i < BUFFER_LIMIT ) {

    return ioBuffer[i];

  } else { 

    return false;

  }

}

void resetBuf(void) {
  for ( uint8_t i = 0 ; i < BUFFER_SIZE ; i++ )
    ioBuffer[i] = 0;
}
