///////////////////////////
//        INCLUDES       //
///////////////////////////

#include <Arduino.h>
#include "defines.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "disp_func.h"
#include "FSystem.h"
#include "wifi.h"
#include "globals.h"
#include "http_func.h"
#include "leds.h"
#include "buttons.h"



///////////////////////////
//        DEFINES        //
///////////////////////////



///////////////////////////
//    GLOBAL VARIABLES   //
///////////////////////////

///////////////////////////
//        PROTOTYPES     //
///////////////////////////

//--Подключение хэндлеров на HTTP
void http_on();

DisplayClass display;
ConfigClass config;
HttpClass server;
LedsClass leds;

void setup() {
  display.init();
  config.init();
  display.showLogo();
  Serial.begin(9600);
  WiFi_init(config,display);
  http_on();
  server.init();
  leds.init();
  

}

void loop() {
  server.HTTP.handleClient();
  
}

//--Подключение хэндлеров на HTTP
void http_on(){
    // -------------------Прокачка системы
  server.HTTP.on("/start", HTTP_GET, []() {
    //startProc();
    server.HTTP.send(200, "text/plain", "OK");
  });
    // -------------------Выдаем данные configSetup
  server.HTTP.on("/config.json", HTTP_GET, []() {
    server.HTTP.send(200, "application/json", config.getConfigString());
  });
    // -------------------Выдаем данные users
  server.HTTP.on("/users.json", HTTP_GET, []() {    
    server.HTTP.send(200, "application/json", config.getUsersString());
  });
  // server.HTTP.on("/wifi.json", HTTP_GET, []() {    
  //   server.HTTP.send(200, "application/json", config.getWiFiString());
  // });  
    // -------------------Сохранение users js json
  server.HTTP.on("/saveusers", HTTP_GET, []() {
    String jstr= server.HTTP.arg("json");
    config.setUsersString(jstr);
    server.HTTP.send(200, "text/plain", "OK");
    //SocketData("userreload","1","99");
  });
  server.HTTP.on("/saveconfig", HTTP_GET, []() {
    String jstr= server.HTTP.arg("json");
    config.setConfigString(jstr);
    ////saveConfig();
    //FastLED.setBrightness(jsonReadtoInt(configSetup, "ledbright"));
    server.HTTP.send(200, "text/plain", "OK");
  });
  server.HTTP.on("/saveshot", HTTP_GET, []() {
    String jstr= server.HTTP.arg("json");
    config.setShotsString(jstr);
    server.HTTP.send(200, "text/plain", "OK");
  });
  server.HTTP.on("/savewifi", HTTP_GET, []() {
    String jstr= server.HTTP.arg("json");
    config.setWiFiString(jstr);
    server.HTTP.send(200, "text/plain", "OK");
  });  
    //------------------Перезапуск системы  
  server.HTTP.on("/restart", HTTP_GET, []() {
    String restart = server.HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      server.HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      server.HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
  server.HTTP.onNotFound([]() {
    if (!server.handleFileRead(server.HTTP.uri()))
      server.HTTP.send(404, "text/plain", "FileNotFound");
  });
}



