#pragma once
#include <stdint.h>

bool pushBuf(uint8_t c,uint16_t i);
// ^Safe push buffer

uint8_t getBuf(uint16_t i);
// ^Safe read buffer

uint8_t* pointBuf(void);
// ^Get buffer location
