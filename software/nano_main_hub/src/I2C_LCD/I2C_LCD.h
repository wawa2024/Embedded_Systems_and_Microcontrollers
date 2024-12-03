#pragma once
#include "DFRobot_RGBLCD1602.h"

/*
Change the RGBaddr value based on the hardware version
-----------------------------------------
       Moudule        | Version| RGBAddr|
-----------------------------------------
  LCD1602 Module      |  V1.0  | 0x60   |
-----------------------------------------
  LCD1602 Module      |  V1.1  | 0x6B   |
-----------------------------------------
  LCD1602 RGB Module  |  V1.0  | 0x60   |
-----------------------------------------
  LCD1602 RGB Module  |  V2.0  | 0x2D   |
-----------------------------------------
*/

DFRobot_RGBLCD1602 lcd(/*RGBAddr*/0x60 ,/*lcdCols*/16,/*lcdRows*/2); //16 characters and 2 lines of show

  /**
   *  @brief initialize the LCD and master IIC
   */ 
// void init();

  /**
   *  @brief clear the display and return the cursor to the initial position (position 0)
   */
// void clear();

  /**
   *  @brief return the cursor to the initial position (0,0)
   */
// void home();

  /**
   *  @brief Turn off the display
   */
// void noDisplay();

  /**
   *  @brief Turn on the display
   */
// void display();

  /**
   *  @brief Turn  off the blinking showCursor
   */
// void stopBlink();

  /**
   *  @brief Turn on  the blinking showCursor
   */
// void blink();

  /**
   *  @brief Turn off the underline showCursor 
   */
// void noCursor();

  /**
   *  @brief Turn on the underline showCursor 
   */
// void cursor();

  /**
   *  @brief scroll left to display
   */
// void scrollDisplayLeft();

  /**
   *  @brief scroll right to display
   */
// void scrollDisplayRight();
 
  /**
   *  @brief This is for text that flows Left to Right
   */
// void leftToRight();
 
  /**
   *  @brief This is for text that flows Right to Left
   */
// void rightToLeft();

  /**
   *  @brief This will 'left justify' text from the showCursor
   */
// void noAutoscroll();
 
  /**
   *  @brief This will 'right justify' text from the showCursor
   */
// void autoscroll();
   
  /**
   *  @brief Allows us to fill the first 8 CGRAM locations with custom characters
   *  @param location substitute character range（0-7）
   *  @param charmap  character array the size is 8 bytes
   */
// void customSymbol(uint8_t location, uint8_t charmap[]);

  /**
   *  @brief set cursor position
   *  @param col columns optional range 0-15
   *  @param row rows optional range 0-1，0 is the first row, 1 is the second row
   */
// void setCursor(uint8_t col, uint8_t row);
  
  /**
   *  @brief set RGB
   *  @param r  red   range(0-255)
   *  @param g  green range(0-255)
   *  @param b  blue  range(0-255)
   */
// void setRGB(uint8_t r, uint8_t g, uint8_t b);

  /**
   *  @brief set backlight PWM output
   *  @param color  backlight color  Preferences：REG_RED\REG_GREEN\REG_BLUE
   *  @param pwm  color intensity   range(0-255)
   */
// void setPWM(uint8_t color, uint8_t pwm);

  /**
   *  @brief backlight color
   *  @param color  backlight color  Preferences： WHITE\RED\GREEN\BLUE
   */
// void setColor(uint8_t color);

  /**
   *  @brief close backlight
   */
// void closeBacklight();

  /**
   *  @brief set color to white
   */
// void setColorWhite();

  /**
   *  @brief write character
   *  @param data the written data
   */
// virtual size_t write(uint8_t data);

  /**
   *  @brief send command
   *  @param data the sent command 
   */
// void command(uint8_t data);

  /**
   *  @brief set backlight
   *  @param mode  true indicates the backlight is turned on and set to white，false indicates the backlight is turned off
   */
// void setBacklight(bool mode);
