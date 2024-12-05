#include "Arduino.h"

bool keyDebounce(bool keysEqual, bool& repeat, bool& debounce) {
// ^Debounce key function, with inbuilt repeat delay

  if ( keysEqual ) {

    if ( debounce ) {

      debounce = false;
      repeat = true;

      delay(100); // debounce timeout

      return true; // use this value to reset scan

    }

    if ( repeat ) {

      delay(300); // repeat rate

    }

  } else {

    debounce = true;
    repeat = false;

  }

  return false;
  
}
