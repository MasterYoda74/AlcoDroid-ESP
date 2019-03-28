#ifndef _WIFI_H_
#define _WIFI_H_
#include <ESP8266WiFi.h>
#include "FSystem.h"
#include "disp_func.h"

enum WiFi_state {
    IS_AP,
    IS_STA,
    IS_ERROR
};

WiFi_state WiFi_init(ConfigClass&, DisplayClass&);
bool connectToWiFi(String _ssid, String _pass, DisplayClass &display);
String IpAddress2String(const IPAddress& ipAddress);
bool StartAPMode(String _ssidAP, String _passwordAP);


#endif