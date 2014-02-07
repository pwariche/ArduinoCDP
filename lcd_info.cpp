#include "lcd_info.h"

menu_item menu[] = {
  {
    LABEL_MAC,
    ("Mac Address:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_MY_IP,
    ("My IP address:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_DEVICE_ID,
    ("Device ID:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_ADDRESS,
    ("IP Address:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_PORT_ID,
    ("Interface:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_SOFTWARE,
    ("Software:"),
    NULL,
    INVISIBLE
  },
  {
    LABEL_PLATFORM,
    "Platform:",
    NULL,
    INVISIBLE
  },
  {
    LABEL_NATIVE_VLAN,
    "Native Vlan:",
    NULL,
    INVISIBLE
  },
  {
    LABEL_DUPLEX,
    "Duplex:",
    NULL,
    INVISIBLE
  },
};

size_t menu_size = sizeof(menu)/sizeof(*menu);

unsigned int menu_current = 0;
unsigned int lcd_more_offset = 0;

volatile unsigned long last_cdp_received = 0;
volatile unsigned long cdp_packets_received = 0;

void set_menu(label_type type, const char* value) {
  unsigned int i;
  for(i = 0; i < menu_size; ++i) {
    if(menu[i].type == type) {
      menu[i].value = value;
      menu[i].visible = VISIBLE;
    }
  }
}


void lcd_info_next() {
  size_t menu_next = menu_current + 1;
  if(menu_next > menu_size) menu_next = 0;
  while(menu[menu_next].visible != VISIBLE &&
    menu_next != menu_current
  ) {
    if(++menu_next > menu_size) {
      menu_next = 0;
    }
  }
  menu_current = menu_next;
  lcd_more_offset = 0;
}

void lcd_info_prev() {
  size_t menu_prev = menu_current - 1;
  if(menu_prev > menu_size) menu_prev = 0;
  while(menu[menu_prev].visible != VISIBLE &&
    menu_prev != menu_current
  ) {
    if(++menu_prev > menu_size) {
      menu_prev = 0;
    }
  }
  menu_current = menu_prev;
  lcd_more_offset = 0;
}

void lcd_info_more() {
  // If first offset add an extra offset to scroll even though prefixing with a char
  if(lcd_more_offset == 0)
    lcd_more_offset = 1;

  if(++lcd_more_offset > strlen(menu[menu_current].value))
    lcd_more_offset = 0;
}
void lcd_info_less() {
  // If first offset add an extra offset to scroll even though prefixing with a char
  if(lcd_more_offset == 0)
    lcd_more_offset = 1;

  if(--lcd_more_offset > strlen(menu[menu_current].value))
    lcd_more_offset = 0;
}
