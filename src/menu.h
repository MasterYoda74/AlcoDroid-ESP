#ifndef _MENU_H_
#define _MENU_H_


#include <Arduino.h>
#include "utils.h"
#include "images.h"

enum MenuAction {
    A_NOACTION,
    A_CHECK,
    A_DIGVAL,
    A_TEXT,
    A_ACTION,
    A_INFO
};

struct MenuItem {
  int idx;
  int parent;
  String name;
  MenuAction action;
  const uint8_t *logo;
  int w;
  int h;
};

#define MENU_TOTAL 25
MenuItem menu[MENU_TOTAL] = {
  {0  ,-1 ,utf8rus("Главное меню")        ,A_NOACTION        ,NULL   ,0  ,0},
  {1  ,0  ,utf8rus("Пользователи")        ,A_ACTION ,m1     ,24 ,30},
  {2  ,0  ,utf8rus("Настройки")           ,A_NOACTION        ,set_bmp     ,30 ,30},
  {3  ,2  ,utf8rus("WiFi")                ,A_NOACTION        ,NULL   ,0  ,0},
  {4  ,2  ,utf8rus("Калибровка")          ,A_NOACTION        ,NULL   ,0  ,0},
  {5  ,4  ,utf8rus("Головы")              ,A_ACTION ,NULL   ,0  ,0},
  {6  ,0  ,utf8rus("Старт")               ,A_ACTION ,start_bmp,30  ,30},
  {7  ,11 ,utf8rus("Шагов на 1 мл")       ,A_DIGVAL ,NULL   ,10 ,1000}, 
  {8  ,4  ,utf8rus("Вынос подачи")        ,A_NOACTION        ,NULL   ,0  ,0},
  {9  ,8  ,utf8rus("MAX")                 ,A_DIGVAL ,NULL   ,0  ,180},
  {10 ,8  ,utf8rus("MIN")                 ,A_DIGVAL ,NULL   ,0  ,180},
  {11 ,4  ,utf8rus("Насос")               ,A_NOACTION        ,NULL   ,0  ,0},
  {12 ,11 ,utf8rus("Налить 100 мл")       ,A_ACTION ,NULL   ,0  ,0},
  {13 ,11 ,utf8rus("Прокачка")            ,A_DIGVAL ,NULL   ,0  ,100},
  {14 ,3  ,utf8rus("Режим AP")            ,A_CHECK  ,NULL   ,0  ,0},
  {15 ,3  ,utf8rus("SSID")                ,A_TEXT   ,NULL   ,1  ,20},
  {16 ,3  ,utf8rus("Пароль")              ,A_INFO   ,NULL   ,8  ,20},
  {17 ,11 ,utf8rus("Откат")               ,A_DIGVAL ,NULL   ,0  ,50},
  {18 ,3  ,utf8rus("IP")                  ,A_INFO   ,NULL   ,0  ,50},
  {19 ,2  ,utf8rus("Режим")               ,A_NOACTION        ,NULL   ,0  ,50},
  {20 ,19 ,utf8rus("Рабочий")             ,A_ACTION ,NULL   ,0  ,50},  
  {21 ,19 ,utf8rus("Демо")                ,A_ACTION ,NULL   ,0  ,50},
  {22 ,2  ,utf8rus("Яркость LED")         ,A_DIGVAL ,NULL   ,0  ,254},
  {23 ,2  ,utf8rus("Сохранить")           ,A_ACTION ,NULL   ,0  ,50},
  {24 ,11 ,utf8rus("Откат 100 мл")        ,A_ACTION ,NULL   ,0  ,0},
            
};

#endif