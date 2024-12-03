#include <Arduino.h>
#include "procSerial.h"
#include "ioBuffer.h"

#define BAUD_RATE 115200
#define BUFFER_SIZE 80

static unsigned int i = 0;

void mirrorSerial(void) {

  if (Serial.available() > 0) {

    char c = (char)Serial.read();
    
    if (c == '\n') {

      digitalWrite(LED_BUILTIN, HIGH);

      setBuf(0,i++);

      Serial.write((char*)pointBuf());
      Serial.write("\n");

      i = 0;

      digitalWrite(LED_BUILTIN, LOW);
    } else {

      setBuf(c,i++);

    }
  }
  
}
