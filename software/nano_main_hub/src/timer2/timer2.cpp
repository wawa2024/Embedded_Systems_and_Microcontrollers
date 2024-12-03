#include "timer2.h"
#include <stdint.h>
#include <Arduino.h>

// counter preload for timer2. Theoretical value is 125, 
// but with experimentation the value 123 was deamed more appropriate
static const uint8_t preload = 0xFF - 123; 


void (*timer2_Callback)(void);


ISR( TIMER2_OVF_vect )
{
    // If callback is not set then leave
    if(timer2_Callback == NULL){ return; }
    
    // Call users callback
    timer2_Callback();

    // Preloaded for 1kHz overflow
    TCNT2 = preload; 
}   


// Timer is initialized to generate 
// a 1kHz overflow interrupt
void timer2_init(void)
{
    TCCR2A = 0x00;

    // 128 prescaler
    TCCR2B = 0x04;

    // Overflow interrupt enabled
    TIMSK2 |= ( 1 << TOIE2 );
    
    // Preloaded for 1kHz overflow
    TCNT2 = preload;
}


// Sets the timer2 interrupt callback
void timer2_setCallback( void (*userCallback)(void) )
{
    // Alustetaan timer2 callback
    timer2_Callback = userCallback;
}
