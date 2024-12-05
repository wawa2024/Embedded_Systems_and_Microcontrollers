#pragma once

// Timer is initialized to generate 
// a 1kHz overflow interrupt
void timer1_init(void);


// Sets the timer2 interrupt callback
void timer1_setCallback( void (*userCallback)(void) );


// Timer is initialized to generate 
// a 1kHz overflow interrupt
void timer2_init(void);


// Sets the timer2 interrupt callback
void timer2_setCallback( void (*userCallback)(void) );
