#include <Wire.h>
#include "disp_func.h"
#include "images.h"
#include "menu.h"
#include "globals.h"


DisplayClass::DisplayClass(){
    Adafruit_SSD1306 display(128,64,&Wire,OLED_RESET);
}

void DisplayClass::init(ConfigClass &cc) {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.cp437(true);
    config = cc;
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
void DisplayClass::printToBar(String str, int set, int total) {
    display.fillRect(0,50,128,14,BLACK);
    display.drawRoundRect(0,50,128,6,1,WHITE);
    display.drawRect(2,52,(124/total)*set,2,WHITE);
    display.setCursor(0,56);
    display.print(str);
    display.display();
}
void DisplayClass::printToBar(String str) {
    display.fillRect(0,50,128,14,BLACK);
    display.setCursor(0,56);
    display.print(str);
    display.display();
}

void DisplayClass::p_MainMenu() {
    if (curMLevel == 0) {
        display.setCursor(1,1);
        display.setTextColor(WHITE);
        display.print(menu[curMLevel].name);
        display.drawFastHLine(0,10, 128, WHITE);
        int xx=(128-menu[curMPos].w)/2;
        int yy=(64-menu[curMPos].h)/2;
        display.drawBitmap(xx, yy, menu[curMPos].logo, menu[curMPos].w, menu[curMPos].h, WHITE);
        int16_t  x1, y1;
        uint16_t w, h;
        display.getTextBounds(menu[curMPos].name, 0, 55, &x1, &y1, &w, &h);
        display.setCursor((128-w)/2,55);
        display.print(menu[curMPos].name);
    }
}

void DisplayClass::p_subMenu() {
    if (curMLevel != 0) {
        display.setCursor(1,1);
        display.setTextColor(WHITE);
        display.print(menu[curMLevel].name);
        display.drawFastHLine(0,10, 128, WHITE);
        yoff = 13;
        for (int i = 0; i < menuCounts; i++) {
            if (curMenuItems[i] != 99) {
            display.setCursor(5,yoff);
            display.print(menu[curMenuItems[i]].name);
        if (menu[curMenuItems[i]].action == A_ACTION) {
          display.fillTriangle(110, yoff, 110, yoff+8, 128, yoff+4, WHITE);
        }
        switch (curMenuItems[i]) {
          case 7:
            //drawText(String(option.stepPerMl));
            drawText(String(config.getValToInt("stepPerMl")));
          break;         
          case 9:
            //drawText(String(option.servoMAX));
            drawText(String(config.getValToInt("servoMAX")));
          break;  
          case 10:
            //drawText(String(option.servoMIN));
            drawText(String(config.getValToInt("servoMIN")));
          break; 
          case 13:
            //drawText(String(option.startMl)+" ml");
            drawText(String(config.getValToInt("startMl"))+ " ml");
          break;                          
          case 14:
            //drawSwitch(option.isAP);
            drawSwitch(state.isAP);
          break;
          case 15:
            drawText(state.curSSID);
            break;
          case 16:
            drawText(state.curPass);//wifi pass
          break;
          case 17:
            //drawText(String(option.feedback)+" ml");
            drawText(String(config.getValToInt("feedback"))+ " ml");
          break;          
          case 18:
              drawText(state.IPAddress);//ip
           break;           
          default:
          break;
          
        }
        yoff=yoff+8;
      } else {
        display.setCursor(5,yoff);
        display.print(utf8rus("Назад"));
      }
    }

    //if (doAction == 2 && curMPos == 7) drawChangeDig(menu[curMPos].name, "");
    //if (doAction == 2 && curMPos == 13) drawChangeDig(menu[curMPos].name, " ml");
//    if (doAction == 2 ) drawChangeDig(menu[curMPos].name);
    display.fillRect(0,12+(8*curAPos),4,8,WHITE);
  }
}



void DisplayClass::menuCount () {
  int x=0, i=0;
  while (i < MENU_TOTAL) {
    if (curMLevel == menu[i].parent) {
      curMenuItems[x] = menu[i].idx;
      x++;
    }
    i++;
  }
  menuCounts=x;
  if (curMLevel != 0) {
    curMenuItems[menuCounts]=99;  //Добавили НАЗАД в список подменю начиная с 1 уровня
    menuCounts++;
  }      
}

void DisplayClass::drawText(String str) {
  uint16_t w, h;
  int16_t  x1, y1;
  display.getTextBounds(str, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128-w),yoff);
  display.print(str);  
}

void DisplayClass::drawSwitch(bool state){
  if (state) {
    display.drawRoundRect(110, yoff, 18, 9, 4, WHITE);
    display.fillCircle(122, yoff+4, 2, WHITE);
  } else {
    display.drawRoundRect(110, yoff, 18, 9, 4, WHITE);
    display.drawCircle(114, yoff+4, 2, WHITE);
  }
}

void DisplayClass::drawChangeDig (String cap) {
  display.fillRoundRect(16, 15, 96, 34,5, BLACK);
  display.drawRoundRect(18, 17, 92, 30,5, WHITE);
  uint16_t w, h;
  int16_t  x1, y1;
  display.getTextBounds(cap, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128-w)/2,22);
  display.print(cap);
  String suff="";
  if (curMPos == 17 || curMPos == 13) suff = " ml"; 
  display.getTextBounds(String(changingVal)+suff, 0, 0, &x1, &y1, &w, &h);  
  display.setCursor((128-w)/2,33);
  display.print(changingVal+suff);
  display.fillTriangle(25,33,25,41,20,37,WHITE);  
  display.fillTriangle(102,33,102,41,107,37,WHITE);   
}

// Wait frame
void DisplayClass::p_Wait() {
  //display.clearDisplay();
  docksDraw();
  //display.setTextSize(1);
  //display.setCursor(0,12);
  display.setTextColor(WHITE);
  String str="";
  for (int i = 0; i < totalUsers; i++) {
        display.setCursor(0,12+(i*8));
        str = utf8rus(users[curUsers[i]].name); 
        display.print(str);
        display.setCursor(75,12+(i*8));
        str = String(users[curUsers[i]].total) + " ml";
        display.print(str);  
     
  }
  //display.println("Waiting...");
  //if (isWS) display.println("WebSocket ON...");
  //display.println(WiFi.status());
  /*  // Вывод LED на экран
  String rs,gs,bs;
  for (int i=0; i<6; i++ ){
    rs += String(leds[i].r);
    rs +=" ";
    gs += String(leds[i].g);
    gs +=" "; 
    bs += String(leds[i].b);
    bs +=" ";       
  }
  display.println("R: "+ String(rs));
  display.println("G: "+ String(gs));
  display.println("B: "+ String(bs));*/
  if (!isOn){
    display.fillRoundRect(20,20,88,24,5,WHITE);
    uint16_t w, h;
    int16_t  x1, y1;
    //display.setFont(&FreeSans12pt7b);
    display.getTextBounds(utf8rus("ПАУЗА"), 0, 0, &x1, &y1, &w, &h);
    display.setCursor((128-w)/2,28);
    display.setTextColor(BLACK);
    display.print(utf8rus("ПАУЗА"));
    display.setFont();    
  }
  display.display();
}
void DisplayClass::docksDraw() {
  if (isStart) {
    int x = 4;
    int y = 4;
    int shift = 10;
    for (int i = 0; i < 6; i++){
      if (dock[i].user == -1) {
        display.drawCircle(x, y, 1, WHITE);
        //ledDraw(i,CRGB::Black);
      }
      if (dock[i].user != -1 && dock[i].state == 0) {
        display.drawCircle(x, y, 4, WHITE);
        //ledDraw(i,CRGB::Green);
        }
      if (dock[i].user != -1 && dock[i].state == 1) {
        display.fillCircle(x, y, 4, WHITE);
        //ledDraw(i,CRGB::Red);
        }
      if (dock[i].user != -1 && dock[i].state == 2) {
        display.fillCircle(x, y, 2, WHITE);
        //ledDraw(i,CRGB::Yellow);
        }
      x = x + shift;
    }
  } else {
    display.fillRoundRect(0,0,70,9,3,WHITE);
    display.setCursor(4,1);
    display.setTextColor(BLACK);
    display.print(utf8rus("Прокачать !"));
  }

  
    if (WiFi.getMode() ==WIFI_AP) {
      display.drawBitmap( 74, 0,ap_ico,13, 9, WHITE);
    } else {
      display.drawBitmap( 74, 0,wifi_ico,13, 9, WHITE);
    }
  
  //Рисуем каплю с общим объемом налитого
  // display.drawBitmap( 70, 0, drop,7, 9, WHITE);
  // display.setCursor(82,2);
  // display.setTextColor(WHITE);
  // display.print(String(totalDrink)+" ml");


}