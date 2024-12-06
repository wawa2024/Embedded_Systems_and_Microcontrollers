#include <stdint.h>
#include "ioBuffer.h"

#define BUFFER_SIZE 80

static uint8_t ioBuffer[BUFFER_SIZE];
// ^common fifo buffer

uint8_t* pointBuf(void) {
  // ^Get ioBuffer location
  return ioBuffer;
}

bool setBuf(uint8_t c, uint8_t i) {
// ^safe buffer set method

  if ( i < BUFFER_SIZE ) {

    ioBuffer[i] = c;
    return true;

  } else {

    return false;

  }

}

uint8_t getBuf(uint8_t i) {
// ^safe buffer get method
  
  if ( i < BUFFER_SIZE ) {

    return ioBuffer[i];

  } else { 

    return false;

  }

}

void resetBuf(void) {
  // ^Fill ioBuffer with zeros
  for ( uint8_t i = 0 ; i < BUFFER_SIZE ; i++ )
    ioBuffer[i] = 0;
}

uint8_t sizeBuf(void) {
  // ^Return size of ioBuffer
  return BUFFER_SIZE;
}
