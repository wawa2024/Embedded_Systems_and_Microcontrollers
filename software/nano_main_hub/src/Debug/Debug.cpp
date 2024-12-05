#include "Arduino.h"
#include "Debug.h"

void memdump(uint8_t *target, uint16_t &&begin, uint16_t &&end) {
  for ( uint16_t i = begin ; i < end ; i++ ) {
    Serial.print("memdump[");
    Serial.print(i);
    Serial.print("]=");
    Serial.println(target[i]);
  }
}
