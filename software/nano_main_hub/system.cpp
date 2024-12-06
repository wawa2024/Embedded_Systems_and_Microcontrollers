#include "system.h"
#include "src/I2C_LCD/I2C_LCD.h"

void system_init( void (*timer1_callback)(void), void (*timer2_callback)(void) )
{
    timer1_setCallback(timer1_callback);
    timer2_setCallback(timer2_callback)
    
    timer1_init();
    timer2_init();
    
    // init I2C lcd
    lcd.init(); 
    
    // read saved eeprom2 password and save to register
  // initPassword(); 
  
    init_alarm();
}


void system_reboot(void)
{
    // Initialize wdt so it can
    // perform the reset
    wdt_init();

    // Save values to eeprom
    system_saveChanges();

    // Restart using wdt
    while(true)
    {
        __asm__ ("nop");
    }
}


void system_saveChanges(void)
{
    
}
