#include "http_func.h"

#include "globals.h"


HttpClass::HttpClass() {
  ESP8266WebServer HTTP;
  ESP8266HTTPUpdateServer httpUpdater;
}
void HttpClass::init (ConfigClass &conf) {
  config = conf;
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&HTTP);
  // Запускаем HTTP сервер
  HTTP.begin();
}

// Здесь функции для работы с файловой системой
String HttpClass::getContentType(String filename) {
  if (HTTP.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool HttpClass::handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    //size_t sent = 
    HTTP.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

//###############################################################
//   WEBSOCKET ##################################################
//###############################################################

void HttpClass::webSocket_init() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
void HttpClass::loop() {
  webSocket.loop();
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:  // Событие происходит при отключени клиента 
      //Serial.println("web Socket disconnected");
      state.isWS=false;
      break;
    case WStype_CONNECTED: // Событие происходит при подключении клиента
      {
        //Serial.println("web Socket Connected"); 
        state.isWS=true;
        //webSocket.sendTXT(num, configJson); // Отправим в всю строку с данными используя номер клиента он в num
      }
      break;
    case WStype_TEXT: // Событие происходит при получении данных текстового формата из webSocket
      // webSocket.sendTXT(num, "message here"); // Можно отправлять любое сообщение как строку по номеру соединения
      // webSocket.broadcastTXT("message here");
      break;
    case WStype_BIN:      // Событие происходит при получении бинарных данных из webSocket
      // webSocket.sendBIN(num, payload, length);
      break;
    case WStype_ERROR:
      break;
    case WStype_FRAGMENT_TEXT_START:
      break;
    case WStype_FRAGMENT_BIN_START:
      break;
    case WStype_FRAGMENT:
      break;
    case WStype_FRAGMENT_FIN:
      break;
  }
}
// Отправка данных в Socket всем получателям
// Параметры Имя ключа, Данные, Предыдущее значение
void HttpClass::SocketData ( String key, String data, String data_old)  {
  if (data_old != data && state.isWS) {
    String broadcast = "{}";
    config.jsonWrite(broadcast, key, data);
    webSocket.broadcastTXT(broadcast);
  }
}
void HttpClass::SocketSend (String broadcast)  {
  if (state.isWS){
    webSocket.broadcastTXT(broadcast); 
  }
}
void SocketSendDock(int pos) {
  if (state.isWS){
    // DynamicJsonDocument jsonBuffer(1024);
    // //JsonObject& root = jsonBuffer.createObject();
    // JsonArray dockNode = jsonBuffer.createNestedArray("dock");
    // JsonObject dock0 = dockNode.createNestedObject();
    // dock0["pos"] = pos;
    // dock0["state"] = dock[pos].state;
    // dock0["user"] = dock[pos].user;
    // if (dock[pos].user >= 0) dock0["id"] = users[dock[pos].user].id;
    // String send;
    // serializeJson(jsonBuffer, send);
    // SocketSend(send);
  }
}