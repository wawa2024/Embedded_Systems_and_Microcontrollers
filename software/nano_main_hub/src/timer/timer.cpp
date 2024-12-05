#include "timer.h"
#include <stdint.h>
#include <Arduino.h>


// counter preload for timer1 (1kHz). Theoretical value is 250, 
// but with experimentation the value 246 was deamed more appropriate
static const uint16_t timer1_preload = 0xFFFF - 246; 
// counter preload for timer2 (1kHz). Theoretical value is 125, 
// but with experimentation the value 123 was deamed more appropriate
static const uint8_t timer2_preload = 0xFF - 123; 


void (*timer1_Callback)(void);
void (*timer2_Callback)(void);

//////////////////////////////////
//-----------Timer1-------------//
//////////////////////////////////

ISR( TIMER1_OVF_vect )
{
    // If callback is not set then leave
    if(timer1_Callback == NULL){ return; }
    
    // Call users callback
    timer1_Callback();

    // Preloaded for 1kHz overflow
    TCNT1 = timer1_preload; 
}   

// Timer is initialized to generate 
// a 1kHz overflow interrupt
void timer1_init(void)
{
    TCCR1A = 0x00;

    // 64 prescaler
    TCCR1B = 0x03;

    // Overflow interrupt enabled
    TIMSK1 |= ( 1 << TOIE1 );
    
    // Preloaded for 1kHz overflow
    TCNT1 = timer1_preload;
}

// Sets the timer2 interrupt callback
void timer1_setCallback( void (*userCallback)(void) )
{
    // Alustetaan timer2 callback
    timer1_Callback = userCallback;
}


//////////////////////////////////
//-----------Timer2-------------//
//////////////////////////////////

ISR( TIMER2_OVF_vect )
{
    // If callback is not set then leave
    if(timer2_Callback == NULL){ return; }
    
    // Call users callback
    timer2_Callback();

    // Preloaded for 1kHz overflow
    TCNT2 = timer2_preload; 
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
    TCNT2 = timer2_preload;
}

// Sets the timer2 interrupt callback
void timer2_setCallback( void (*userCallback)(void) )
{
    // Alustetaan timer2 callback
    timer2_Callback = userCallback;
}

