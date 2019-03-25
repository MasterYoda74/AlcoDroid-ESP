///////////////////////////
//        INCLUDES       //
///////////////////////////

#include <Arduino.h>
#include "defines.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "system_inits.h"
#include "disp_func.h"
//#include "frames.h"
#include "FSystem.h"



///////////////////////////
//        DEFINES        //
///////////////////////////



///////////////////////////
//    GLOBAL VARIABLES   //
///////////////////////////

///////////////////////////
//        PROTOTYPES     //
///////////////////////////

DisplayClass display;


void setup() {
  display.showLogo();
  Serial.begin(9600);
  FS_init();
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
}
