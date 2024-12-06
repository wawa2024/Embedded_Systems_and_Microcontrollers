#include "system.h"
#include "src/I2C_LCD/I2C_LCD.h"
#include "userPassword.h"

static char initialPassword[PASSWORD_SIZE];

void initialPassword_init( char* password )
{   
    if(password == NULL){ return; }

    for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
    {
        initialPassword[i] = password[i];
    }
}

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
    
    // Initialize the initial password variable
    // so that when the device is reset the password
    // can be compared with the current one
    initialPassword_init( getPassword() );

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
