#include "matrixKeyboard.h"
#include <Arduino.h>


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//              INPUTS
//              COL1    COL2    COL3    COL4
//              PB0     PB1     PB2     PB3
//   OUTPUTS    ----------------------------
//   ROW1 PC0  | 1       2       3       A
//   ROW2 PC1  | 4       5       6       B
//   ROW3 PC2  | 7       8       9       C
//   ROW4 PC3  | *       0       #       D
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

static const uint8_t historyLength = 3;

static uint8_t keymap[] = { '1', '2', '3', 'A',
                          '4', '5', '6', 'B',
                          '7', '8', '9', 'C',
                          '*', '0', '#', 'D' };


static const uint8_t numberOfKeys = 16;

static uint8_t keyHistory[historyLength];

static uint8_t pressedKey = ' ';


uint8_t getPressedKey()
{
    return pressedKey;
}


int8_t readLines(void)
{
    uint16_t temp = 0;
    
    // PORT B init (COLS)
    // Input
    DDRB &= 0xF0;
    PORTB &= 0xF0;

    // PORT C init (ROWS)
    // Output
    PORTC &= 0xF0;
    DDRC |= 0x0F;
    
    // Set first row HIGH
    PORTC |= 0x01; 
    _delay_us(1);
    // Read the columns
    temp = (PINB & 0x0F);
    
    for(uint8_t row = 1; row < 4; row++)
    {
        // Clear the rows and
        // Set the next row HIGH
        PORTC &= 0xF0;
        PORTC |= (1 << row);
        _delay_us(1); 
        // Read the columns 
        temp |= (PINB & 0x0F) << (row*4);
    }
  
    // Set all row pins LOW
    PORTC &= 0xF0;

    uint8_t count = 0;
    for(uint8_t mask = 0x01; mask != 0; mask<<=1)
    {
        if(temp & mask)
        {
            // Count the button presses
            count++;
            // If more than 1 button press
            // has been detected
            if(count > 1)
            {
                // Clear the pressed button bits
                temp = 0x00;
                break;
            }
        }
    }

    // If a button is pressed
    if(temp != 0)
    {
        // Convert a bit location to an integer
        for(uint8_t i = 0; i < 16; i++)
        {
            if( (temp >> i) == 1 )
            {
                temp = i;    
            }
        }
    }
    else
    {
        // No button has been pressed.
        // Value 0 is used to index an array
        // so a -1 is returned to indicate null value
        temp = -1;
    }

    return temp;
} 

uint8_t getCharacter(void)
{
    // Read the keypress to temp variable
    int8_t temp = readLines();

    // -1 indicated no button is pressed
    if(temp == -1){ return ' '; }
    // map the given input to a character
    else{ return keymap[temp]; }
}

uint8_t uniformHistory(void)
{
    for(uint8_t i = 0; i < historyLength; i++)
    {
        // If true then all values aren't equal
        if( keyHistory[0] != keyHistory[i] ){ return false; }
    }
    
    // All values are equal
    return true;
}

void readKey(void)
{   
    keyHistory[2] = keyHistory[1];
    keyHistory[1] = keyHistory[0];
    keyHistory[0] = getCharacter();

    // Are all previous values equal
    if( uniformHistory() )
    {
        // pressed key
        pressedKey = keyHistory[0];
    }
    else
    {
        // "no input"
        pressedKey = ' ';
    }

}






