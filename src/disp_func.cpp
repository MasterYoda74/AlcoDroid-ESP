#include <Wire.h>
#include "disp_func.h"
#include "images.h"

DisplayClass::DisplayClass(){
    Adafruit_SSD1306 display(128,64,&Wire,OLED_RESET);
}

void DisplayClass::init() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.cp437(true);
}

void DisplayClass::clear() {
    display.clearDisplay();
}

void DisplayClass::showLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, AlcoBot_Logo_FS, 128, 64, WHITE);
    display.setCursor(1,1);
    display.setTextColor(WHITE);
    display.print(VERSION);
    display.display();
}

void DisplayClass::printToBar(String str) {
    display.fillRect(0,56,128,8,BLACK);
    display.setCursor(0,56);
    display.print(str);
    display.display();
}