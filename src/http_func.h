#ifndef _HTTP_FUNC_H_
#define _HTTP_FUNC_H_
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WebSocketsServer.h>
#include "FSystem.h"
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
class HttpClass {
    public:
    ESP8266WebServer HTTP;
    HttpClass();

    void init(ConfigClass&);
    bool handleFileRead(String path);
    String getContentType(String filename);
    void SocketData ( String key, String data, String data_old);
    void SocketSend (String broadcast);
    void loop();

    private:
        ConfigClass config;
        WebSocketsServer webSocket = WebSocketsServer(81);
        ESP8266HTTPUpdateServer httpUpdater;
        void webSocket_init();
        

};


#endif