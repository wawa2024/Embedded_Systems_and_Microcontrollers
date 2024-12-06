#include <stdint.h>
#include <Arduino.h>
#include "nokiaKeyboard.h"

static const char* alpha[] = {
  "yz ", 
  "abc", "def", "ghi"
  "jkl", "mno", "pqr",
  "stu", "vwx"
};

#define TIMEOUT 800

nokiaKey getNokia(char c,uint8_t i) {

  static uint8_t j = 0;
  static char prev_c = 0;
  static uint32_t prev_t = 0;

  uint32_t t = millis();

  bool bool_prev_c = prev_c == c; 
  // ^bool eval char is previous char
  
  prev_c = c; 
  // ^reset previous char

  uint32_t elapsed_t = t > prev_t ? t - prev_t : t; 
  // ^error check + calc
  
  bool bool_t = elapsed_t < TIMEOUT
  // ^bool eval elapsed time is less than a timeout
  
  prev_t = t; 
  // ^reset previous time
  
  if ( bool_t and bool_prev_c ) {
  // ^if time is less than a second AND char is same char, do
    
    j = ( j < 3 ) ? j + 1 : 0; 
    // ^set index offset
    
    c = alpha[i][j]; 
    // ^get char

    return Key{ true, c };

  } else {
   
    j = 0;
    return Key{ false, c };

  }
}

nokiaKey evalNokia(char c) {

  uint8_t i = 0;

  switch ( c ) {
    case '0' ... '9': 
      i = c - 60;
      break;

    default: 
      return Key{ false, c };
      break;
  }

  return getNokia(c,i);
}

