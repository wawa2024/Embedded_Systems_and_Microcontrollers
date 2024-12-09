#Muxpragma once

#include <stdint.h>

// Used to pole the keypad
// NOTE! This function should 
// be called often ( 100-1000Hz )
void readKeypad(void);

// Returns the pressed key
// in the form of a character
// based on the keymap
uint8_t getKey(void);
