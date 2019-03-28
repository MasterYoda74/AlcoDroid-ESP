#ifndef _DISP_FUNC_H_
#define _DISP_FUNC_H_
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "defines.h"


class DisplayClass {
    private:
    Adafruit_SSD1306 display;

    public:
    // Constructor
    DisplayClass();
    void init();
    void clear();
    void showLogo();
    void printToBar(String);

};
//void display_init(Adafruit_SSD1306 &d);
#endif