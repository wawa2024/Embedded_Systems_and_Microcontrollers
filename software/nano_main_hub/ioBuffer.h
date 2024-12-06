#pragma once
#include <stdint.h>

bool setBuf(uint8_t c,uint8_t i);
// ^Safe set buffer

uint8_t getBuf(uint8_t i);
// ^Safe get buffer

uint8_t* pointBuf(void);
// ^Get buffer location

void resetBuf(void);
// ^Fill buffer with zeroes

uint8_t sizeBuf(void);
// ^Return size of ioBuffer
