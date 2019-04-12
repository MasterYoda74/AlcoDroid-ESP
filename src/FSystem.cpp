#include "FSystem.h"
#include "defines.h"

#include <ArduinoJson.h>


ConfigClass::ConfigClass(){
  
}

void ConfigClass::makeNewConfig(){
  //configString = '{"config_version":"v03","wifiSSID":"","wifiPASS":"","APSSID":"AlcoDroid","APPASS":"12345678","isAP":true,"servoMAX": 100,"servoMIN": 7,"stepPerMl": 94,"feedback": 3,"startMl": 20,"ledbright": 60,"p_microstep": 32,"p_maxSpeed": 400,"p_accel": 3000}';
  const size_t capacity = JSON_OBJECT_SIZE(15);
  DynamicJsonDocument doc(capacity);

  doc["config_version"] = CONFIG_VERSION;
  doc["wifiSSID"]       = "";
  doc["wifiPASS"]       = "";
  doc["APSSID"]         = "AlcoDroid";
  doc["APPASS"]         = "12345678";
  doc["isAP"]           = true;
  doc["servoMAX"]       = 100;
  doc["servoMIN"]       = 7;
  doc["stepPerMl"]      = 94;
  doc["feedback"]       = 3;
  doc["startMl"]        = 20;
  doc["ledbright"]      = 60;
  doc["p_microstep"]    = 32;
  doc["p_maxSpeed"]     = 400;
  doc["p_accel"]        = 3000;
  configString ="";
  serializeJson(doc, configString);
  
  writeFile("config_" CONFIG_VERSION ".json",configString);
}

String ConfigClass::getConfigString() {
  return configString;
}

bool ConfigClass::setConfigString(String &json) {
  configString = json; 
  writeFile("config_" CONFIG_VERSION ".json", configString );
  return true;
}

String ConfigClass::getShotsString() {
  return shotsString;
}

bool ConfigClass::setShotsString(String &json) {
  shotsString = json;
  writeFile("shots.json", shotsString );
  return true;
}

String ConfigClass::getOldUsersString() {
  return oldUsersString;
}

String ConfigClass::getUsersString() {
  return usersString;
}

bool ConfigClass::setUsersString(String &json) {
  usersString = json;
  return true;
}

String ConfigClass::getWiFiString() {
  return wifiString;
}

bool ConfigClass::setWiFiString(String &json) {
  wifiString = json;
  writeFile("wifi.json", wifiString );
  return true;
}

String ConfigClass::getVal(String param) {
  return jsonRead(configString, param);
}
int ConfigClass::getValToInt(String param) {
  return jsonReadtoInt(configString, param);
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

bool ConfigClass::setVal(String name, String val) {
  jsonWrite(configString,name,val);
  return true;
}

void ConfigClass::saveConfig() {
  writeFile("/config_" CONFIG_VERSION ".json", configString);
}

// Работа с файловой системой

// FS init
void ConfigClass::init() {
  SPIFFS.begin();
  configString = readFile("config_" CONFIG_VERSION ".json", 4096);
  if (configString == "Failed" || jsonRead(configString,"config_version") != CONFIG_VERSION) makeNewConfig();
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

// bool ConfigClass::isExistFile(String name) {
//   return SPIFFS.exists(name);
// }

// File ConfigClass::getFile(String name) {
//   return SPIFFS.open(name, "r");
// }



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
    jstr = "{\"shots\":[]}";
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
    jstr = "{\"wifi\":[]}";
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

