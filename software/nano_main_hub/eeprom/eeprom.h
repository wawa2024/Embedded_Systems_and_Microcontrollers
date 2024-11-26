#pragma once

#include <stdint.h>

// Contains the addresses and
// the data stored in eeprom
typedef struct
{
    uint8_t addr;
    uint8_t data;
} eeprom_t ;


// Reads a byte from eeprom memory
// and places it inside the given struct
void eeprom_read(eeprom_t &d);

// Writes a byte to eeprom memory
void eeprom_write(eeprom_t &d);

