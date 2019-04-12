#ifndef _DISP_FUNC_H_
#define _DISP_FUNC_H_
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "defines.h"
#include "FSystem.h"

class DisplayClass {
    private:
    Adafruit_SSD1306 display;
    ConfigClass config;
    int curMLevel = 0;
    int curMPos;
    int curAPos;
    int changingVal;
    int yoff;
    int curMenuItems[10];
    int menuCounts;
    // Подготовить к показу главное меню
    void p_MainMenu();
    void p_subMenu();
    void menuCount();
    void drawText(String);
    void drawSwitch(bool);
    void drawChangeDig(String);
    void p_Wait();
    void docksDraw();
    

    public:
    // Constructor
    DisplayClass();
    void init(ConfigClass&);
    void clear();
    void showLogo();
    void printToBar(String, int, int);
    void printToBar(String);
};
//void display_init(Adafruit_SSD1306 &d);
#endif