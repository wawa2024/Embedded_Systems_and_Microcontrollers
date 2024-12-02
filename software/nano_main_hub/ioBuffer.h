#pragma once
#include <stdint.h>

bool pushBuf(unsigned int i, char c);
uint8_t getBuf(unsigned int i);
uint8_t* pointBuf(void);
