#include "system.h"

#include "../watchdog/watchdog.h"
#include "../../userPassword.h"


static char initialPassword[PASSWORD_SIZE];


void initialPassword_init( char *password )
{   
    if(password == NULL){ return; }

    for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
    {
        initialPassword[i] = password[i];
    }
}


void system_init(void)
{
    // Initialize the initial password variable
    // so that when the device is reset the password
    // can be compared with the current one
    initialPassword_init( getPassword() );
}


void system_reboot(void)
{
    // Save values to eeprom
    system_saveChanges();
    
    // Initialize wdt so it can
    // perform the reset
    wdt_init();

    // Restart using wdt
    while(true)
    {
        __asm__ ("nop");
    }
}


void system_saveChanges(void)
{
    char *tmp = getPassword();
    for(uint8_t i = 0; i < PASSWORD_SIZE; i++)
    {   
        // If both of the passwords match then don't save it
        if( initialPassword[i] == '\0' && tmp[i] == '\0' ){ break; }

        // if passwords don't match then save current 
        // password to eeprom
        if( initialPassword[i] != tmp[i] )
        { 
            savePassword();
            break;
        }
    } 
}
