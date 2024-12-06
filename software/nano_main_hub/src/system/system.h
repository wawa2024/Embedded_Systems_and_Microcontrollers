#pragma once

// Initializes the system modules
void system_init( void (*timer1_callback)(void), void (*timer2_callback)(void) );

// Reboots the system after 500ms
void system_reboot(void);

// Eeprom variables whose values have
// been changed are saved to eeprom
void system_saveChanges(void);
