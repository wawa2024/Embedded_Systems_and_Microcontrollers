
#include "eeprom.h"


// Reads a byte from eeprom memory
// and places it inside the given struct
void eeprom_read(eeprom_t &d)
{
    // Can't read while write in progress
    while(EECR & (1 << EEPE)){};
    
    // Set the address that you want to read from
    EEARL = d.addr;

    // Disable interrupts for the read operation
    __asm__ ("cli");
    
    // Start the read operation
    EECR |= (1 << EERE);

    // Enable interrupts after the read operation
    __asm__ ("sei");
    
    // Put the read data into the given struct
    d.data = EEDR;
}


// Writes a byte to eeprom memory
void eeprom_write(eeprom_t &d)
{

    // Can't write while another write is in progress
    while(EECR & (1 << EEPE)){};
    
    // Set the address that you want to write to
    EEARL = d.addr;
  
    // Set the data that you want to write
    EEDR = d.data; 

    // Disable interrupts for the read operation
    __asm__ ("cli");

    // Enable eeprom write
    EECR |= (1 << EEMPE); 

    // Start the write process
    EECR |= (1 << EEPE);

    // Enable interrupts after the read operation
    __asm__ ("sei");

}
