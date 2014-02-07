#include "lcd_control.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


void lcd_control_init() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setBacklight(GREEN);
  lcd.setCursor(0,0);
  lcd.print("CDP Sniffino ");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
}

void lcd_control_done() {
  lcd.clear();
  lcd.setBacklight(WHITE);
  lcd.setCursor(0,0);
  lcd.print("Init Done");
  lcd.setCursor(0,1);
  lcd.print("Waiting for CDP");
  }

void lcd_bt_press() { 
uint8_t buttons = lcd.readButtons();
  if (buttons) {
   if(buttons & BUTTON_DOWN) {
     lcd_info_next();
   }
   if(buttons & BUTTON_UP) {
     lcd_info_prev();
   }
   if(buttons & BUTTON_LEFT) {
     lcd_info_more();
    }
   if(buttons & BUTTON_RIGHT) {
     lcd_info_less();
    }
  }
}

void lcd_control_update() {
  unsigned int i;
  boolean complete = 0;
  lcd.setCursor(0,0);
  menu_item* curr = &menu[menu_current];
  char lcd_line0[LCD_LINE_WIDTH + 1]; // LCD_LINE_WIDTH + \0
  char lcd_line1[LCD_LINE_WIDTH + 1]; // LCD_LINE_WIDTH + \0
  for(i=0; i<LCD_LINE_WIDTH; ++i) lcd_line1[i] = ' ';
  if(curr != NULL && curr->visible) {
    size_t label_length = strlen(curr->label);
    strncpy(lcd_line0, curr->label, LCD_LINE_WIDTH);
    for(i = 0; i<LCD_LINE_WIDTH; ++i) {
      if(lcd_line0[i] == '\0') {
        complete = 1;
      }
      if(complete)
        lcd.print(' ');
      else
        lcd.print(lcd_line0[i]);
    }
    i=0;
    lcd.setCursor(0,1);
    if(lcd_more_offset > 0) {
      lcd_line1[i++] = LCD_CHAR_MORE_LEFT;
    }
    size_t value_length = strlen(curr->value);
    if((value_length - lcd_more_offset) > (LCD_LINE_WIDTH - i)) {
      value_length = LCD_LINE_WIDTH - i - 1;
      lcd_line1[LCD_LINE_WIDTH - 1] = LCD_CHAR_MORE_RIGHT;
    } else {
      value_length -= lcd_more_offset;
    }
    strncpy(&lcd_line1[i], &curr->value[lcd_more_offset], value_length);
  } else {
    for(i=0; i<LCD_LINE_WIDTH; ++i) lcd_line1[i] = ' ';
  }
  lcd_line0[LCD_LINE_WIDTH] = '\0';
  lcd_line1[LCD_LINE_WIDTH] = '\0';
  complete = 0;
  for(i = 0; i<LCD_LINE_WIDTH; ++i) {
    if(lcd_line1[i] == '\0') complete = 1;
    if(complete)
      lcd.print(' ');
    else
      lcd.print(lcd_line1[i]);
  }
}
