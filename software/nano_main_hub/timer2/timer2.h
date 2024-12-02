#pragma once

// Timer is initialized to generate 
// a 1kHz overflow interrupt
void initTimer2(void);


// Sets the timer2 interrupt callback
void setTimer2_Callback( void (*userCallback)(void) );
