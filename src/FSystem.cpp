#include "FSystem.h"
#include <FS.h>
#include <ArduinoJson.h>


ConfigClass::ConfigClass(){
  
}

void ConfigClass::makeNewConfig(){
  configString = '{"config_version":"v03","wifiSSID":"","wifiPASS":"","APSSID":"AlcoDroid","APPASS":"12345678","isAP":true,"servoMAX": 100,"servoMIN": 7,"stepPerMl": 94,"feedback": 3,"startMl": 20,"ledbright": 60,"p_microstep": 32,"p_maxSpeed": 400,"p_accel": 3000}';
  writeFile("config.json",configString);
}

String ConfigClass::getConfigString() {
  return configString;
}

String ConfigClass::getShotsString() {
  return shotsString;
}

String ConfigClass::getOldUsersString() {
  return oldUsersString;
}

String ConfigClass::getUsersString() {
  return usersString;
}

String ConfigClass::getWiFiString() {
  return wifiString;
}

String ConfigClass::getVal(String param) {
  return jsonRead(configString, param);
}

bool ConfigClass::getValToBool(String param) {
  return jsonReadtoBool(configString, param);
}

WiFiSett ConfigClass::getWiFiSetting(int index){
  WiFiSett set;
  String jstr = readFile("wifi.json", 2048);
  DynamicJsonDocument jsonBuffer(1024);
  // Parse the JSON input
  deserializeJson(jsonBuffer, jstr);
  // Parse succeeded?
  JsonArray j =jsonBuffer["wifi"];
  JsonObject s = j[index];
  set.id = s["ID"];
  set.SSSID = s["SSID"].as<String>();
  set.Pass = s["PASS"].as<String>();
  return set;
}

// Работа с файловой системой

// FS init
void ConfigClass::init() {
  SPIFFS.begin();
  configString = readFile("config.json", 4096);
  if (configString == "Failed") makeNewConfig();
}

// ------------- Чтение файла в строку
String ConfigClass::readFile(String fileName, size_t len ) {
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}

// ------------- Запись строки в файл
String ConfigClass::writeFile(String fileName, String strings ) {
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}



// Работа с JSON


// ------------- Чтение значения json
String ConfigClass::jsonRead(String &json, String name) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer,json);
  return jsonBuffer[name].as<String>();
}

// ------------- Чтение значения json
int ConfigClass::jsonReadtoInt(String &json, String name) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer, json);
  return jsonBuffer[name];
}
// ------------- Чтение значения json bool
bool ConfigClass::jsonReadtoBool(String &json, String name) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer, json);
  return jsonBuffer[name].as<bool>();
}

// ------------- Запись значения json String
String ConfigClass::jsonWrite(String &json, String name, String volume) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer, json);
  jsonBuffer[name] = volume;
  json = "";
  serializeJson(jsonBuffer, json);
  return json;
}

// ------------- Запись значения json int
String ConfigClass::jsonWrite(String &json, String name, int volume) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer, json);
  jsonBuffer[name] = volume;
  json = "";
  serializeJson(jsonBuffer, json);
  return json;
}
// ------------- Запись значения json bool
String ConfigClass::jsonWriteBool(String &json, String name, bool volume) {
  DynamicJsonDocument jsonBuffer(1024);
  deserializeJson(jsonBuffer, json);
  jsonBuffer[name] = volume;
  json = "";
  serializeJson(jsonBuffer, json);
  return json;
}
// ------------- Поиск цвета по ID в shots.json
String ConfigClass::findColor(String id){
  String jstr = readFile("shots.json", 2048);
  if (jstr == "Failed") {
    jstr = "{shots:[]}";
    writeFile("shots.json",jstr);
  }
  DynamicJsonDocument jsonBuffer(1024);
  // Parse the JSON input
  deserializeJson(jsonBuffer, jstr);
  // Parse succeeded?
  JsonArray jshots =jsonBuffer["shots"];
  if (jshots.size()) {
  // Yes! We can extract values.
    //for (int i; i< jusers.size; i++) {
    for (JsonObject shot : jshots) {  
      String shotID = shot["ID"].as<String>();
      if (shotID == id) return shot["color"].as<String>();
    }
  } else {
  // No!
  // The input may be invalid, or the JsonBuffer may be too small.
  return "Error";
  }
  return "grey";
}

String ConfigClass::findWiFiSetting(String _ssid) {
  String jstr = readFile("wifi.json", 2048);
  if (jstr == "Failed") {
    jstr = "{wifi:[]}";
    writeFile("wifi.json",jstr);
  }
  DynamicJsonDocument jsonBuffer(1024);
  // Parse the JSON input
  deserializeJson(jsonBuffer, jstr);
  // Parse succeeded?
  JsonArray jshots =jsonBuffer["wifi"];
  if (jshots.size()) {
  // Yes! We can extract values.
    //for (int i; i< jusers.size; i++) {
    for (JsonObject shot : jshots) {  
      String shotID = shot["SSID"].as<String>();
      if (shotID == _ssid) return shot["PASS"].as<String>();
    }
  } else {
  // No!
  // The input may be invalid, or the JsonBuffer may be too small.
  return "";
  }
  return "";  
}

