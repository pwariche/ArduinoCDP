#ifndef _LCD_CONTROL_H_
#define _LCD_CONTROL_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>


#include "lcd_info.h"

/////////////////////////

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x
#define VIOLET 0x5
#define WHITE 0x7

////////////////////////

#define LCD_CHAR_MORE_LEFT 0x3c
#define LCD_CHAR_MORE_RIGHT 0x3e
#define LCD_CHAR_DELTA 0x5e
#define LCD_LINE_WIDTH 16

void lcd_control_init();
void lcd_control_done();
void lcd_control_update();
void lcd_bt_press();


#endif
