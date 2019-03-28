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
#include "wifi.h"
#include "globals.h"



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
ConfigClass config;

void setup() {
  display.init();
  config.init();
  display.showLogo();
  Serial.begin(9600);
  
  WiFi_init(config,display);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
}

