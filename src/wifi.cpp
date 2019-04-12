#include "wifi.h"

#include <Arduino.h>

#include "globals.h"


WiFi_state WiFi_init(ConfigClass &config, DisplayClass &display){
    if (!config.getValToBool("isAP")){
        // Попытка подключения к точке доступа
        WiFi.mode(WIFI_STA);
        String _ssid = config.getVal("wifiSSID");
        String _password = config.getVal("wifiPASS");
        if (_ssid.length() > 1) {
            if (connectToWiFi(_ssid,_password,display)) {
                //connected
                state.isAP=false;
                return IS_STA;
            }
        } else {
            // not connected
            int n = WiFi.scanNetworks();
            for (int i = 0; i < n; ++i) {
                String _password = config.findWiFiSetting(WiFi.SSID(i));
                if (_password.length()>6) {
                    if (connectToWiFi(WiFi.SSID(i), _password, display)) {
                        if (WiFi.SSID(i) != config.getVal("wifiSSID")) {
                            config.setVal("wifiSSID",WiFi.SSID(i));
                            config.setVal("wifiPASS",_password);
                            config.saveConfig();
                        }
                        state.isAP=false;
                        return IS_STA;
                    }
                }
            }
            StartAPMode(config.getVal("APSSID"),config.getVal("APPASS"));
            display.printToBar("AP mode: " + state.IPAddress);
            state.isAP=true;
            return IS_AP;
        }
    } else {
        StartAPMode(config.getVal("APSSID"),config.getVal("APPASS"));
        display.printToBar("AP mode: " + state.IPAddress);
        state.isAP=true;
        return IS_AP;
    }
    return IS_ERROR;
}

bool connectToWiFi(String _ssid, String _pass, DisplayClass &display) {
        byte tries = 11;
        if (_ssid == "" && _pass == "") {
            WiFi.begin();
        }
        else {
            WiFi.begin(_ssid.c_str(), _pass.c_str());
        }
    // Делаем проверку подключения до тех пор пока счетчик tries
    // не станет равен нулю или не получим подключение
        display.printToBar(_ssid);
        int bar = tries;
        while (--tries && WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            display.printToBar(_ssid, bar-tries, bar);
        }
        if (WiFi.status() != WL_CONNECTED)
        {
            display.printToBar(_ssid + " Failed !");
            delay(500);
            return false;
        } else {
        // Иначе удалось подключиться отправляем сообщение
        // о подключении и выводим адрес IP
            display.printToBar(_ssid + " OK");
            delay(500);
            state.IPAddress = IpAddress2String(WiFi.localIP());
            state.curSSID = _ssid;
            state.curPass = _pass;
            return true;
        }
}


bool StartAPMode(String _ssidAP, String _passwordAP) {
  IPAddress apIP(192, 168, 4, 1);
  // Отключаем WIFI
  WiFi.disconnect();
  // Меняем режим на режим точки доступа
  WiFi.mode(WIFI_AP);
  //WiFi.getMode();
  // Задаем настройки сети
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  // Включаем WIFI в режиме точки доступа с именем и паролем
  // хронящихся в переменных _ssidAP _passwordAP
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  state.IPAddress = IpAddress2String(apIP);
  state.curSSID = _ssidAP;
  state.curPass = _passwordAP;
  return true;
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}