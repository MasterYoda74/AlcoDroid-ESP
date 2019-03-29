#ifndef _HTTP_FUNC_H_
#define _HTTP_FUNC_H_
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>



class HttpClass {
    public:
    ESP8266WebServer HTTP;
    HttpClass();

    void init();
    bool handleFileRead(String path);
    String getContentType(String filename);


    private:
        
        ESP8266HTTPUpdateServer httpUpdater;
};


#endif