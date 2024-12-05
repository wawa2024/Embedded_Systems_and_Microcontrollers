#pragma once

#define DEBUG(PREFIX,TARGET) Serial.print(PREFIX);Serial.println(TARGET)

void memdump(uint8_t *target, uint16_t &&begin, uint16_t &&end);
// ^Memdump a region to serial
