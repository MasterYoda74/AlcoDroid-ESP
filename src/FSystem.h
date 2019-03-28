#ifndef _FSYSTEM_H_
#define _FSYSTEM_H_

#include <Arduino.h>
    enum ConfStrings{
        CONFIG,
        WIFI,
        USERS,
        OLDUSERS,
        SHOTS
    };
struct WiFiSett {
    int id;
    String SSSID;
    String Pass;
};

class ConfigClass {
    public:
    
    ConfigClass();
    String getConfigString();
    String getWiFiString();
    String getUsersString();
    String getShotsString();
    String getOldUsersString();
    String getVal(String Param);
    bool getValToBool(String Param);
    WiFiSett getWiFiSetting(int index);
    String findWiFiSetting(String);
    void init();

    private:
    String configString = "{}";
    String wifiString = "{wifi:[]}";
    String oldUsersString = "{oldusers:[]}";
    String shotsString = "{shots:[]}";
    String usersString = "{users:[]}";


    
    void makeNewConfig();
    String readFile(String fileName, size_t len );
    String writeFile(String fileName, String strings );
    String jsonRead(String &json, String name);
    int jsonReadtoInt(String &json, String name);
    bool jsonReadtoBool(String &json, String name);
    String jsonWrite(String &json, String name, String volume);
    String jsonWrite(String &json, String name, int volume);
    String jsonWriteBool(String &json, String name, bool volume);
    String findColor(String id);

};

#endif