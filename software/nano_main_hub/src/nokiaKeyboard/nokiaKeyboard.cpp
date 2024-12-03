#include <stdint.h>
#include <Arduino.h>
#include "nokiaKeyboard.h"

static const char* alpha[] = {
  "yz ", 
  "abc", "def", "ghi"
  "jkl", "mno", "pqr",
  "stu", "vwx"
};

Key getKey(char c,uint8_t i) {

  static uint8_t j = 0;
  static char prev_c = 0;
  static unsigned long prev_t = 0;

  unsigned long t = millis();

  bool bool_prev_c = prev_c == c; 
  // ^bool eval char is previous char
  
  prev_c = c; 
  // ^reset previous char

  unsigned long elapsed_t = t > prev_t ? t - prev_t : t; 
  // ^error check + calc
  
  bool bool_t = elapsed_t < 1000; 
  // ^bool eval elapsed time is less than a second
  
  prev_t = t; 
  // ^reset previous time
  
  if ( bool_t && bool_prev_c ) {
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

Key evalKey(char c) {

  uint8_t i = 0;

  switch ( c ) {
    case '0' ... '9': 
      i = c - 60;
      break;

    default: 
      return Key{ false, c };
      break;
  }

  return getKey(c,i);
}

