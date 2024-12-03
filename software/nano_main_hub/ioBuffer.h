#pragma once
#include <stdint.h>

bool setBuf(uint8_t c,uint16_t i);
// ^Safe set buffer

uint8_t getBuf(uint16_t i);
// ^Safe get buffer

uint8_t* pointBuf(void);
// ^Get buffer location
