#include <timer2.h>
#include <stdint.h>
#include <Arduino.h>


static const uint8_t preload = 0xFF - 125; 


void (*timer2_Callback)(void);


ISR(TIMER2_OVF_vect)
{
    // If callback is not set then leave
    if(timer2_Callback == NULL){ break; }
    // Call users callback
    timer2_Callback();
}   


// Timer is initialized to generate 
// a 1kHz overflow interrupt
void initTimer2(void)
{
    TCCR2A = 0x00;

    // 128 prescaler
    TCCR2B = 0x05;

    // Overflow interrupt enabled
    TIMSK2 |= ( 1 << TOIE2 );
    
    // Preloaded for 1kHz overflow
    TCNT2 = preLoad; 
}


// Sets the timer2 interrupt callback
void setTimer2_Callback( void (*userCallback)(void) )
{
    // Alustetaan timer2 callback
    timer2_Callback = userCallback;
}
