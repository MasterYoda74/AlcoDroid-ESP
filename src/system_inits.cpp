#include "system_inits.h"


void display_init(Adafruit_SSD1306 &d) {
  
  d.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  d.cp437(true);    
}

void ddd (Adafruit_SSD1306 &d) {
    
}