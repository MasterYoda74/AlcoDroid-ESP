#ifndef _FSYSTEM_H_
#define _FSYSTEM_H_

#include <Arduino.h>
#include <FS.h>
enum ConfStrings
{
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
    bool   setConfigString(String &json);
    String getWiFiString();
    bool   setWiFiString(String &json);
    String getUsersString();
    bool   setUsersString(String &json);
    String getShotsString();
    bool   setShotsString(String &json);
    String getOldUsersString();
    String getVal(String Param);
    int    getValToInt(String Param);
    bool   getValToBool(String Param);
    bool   setVal(String,String);
    void   saveConfig();
    WiFiSett getWiFiSetting(int index);
    String findWiFiSetting(String);
    void init();
    String jsonWrite(String &json, String name, String volume);
    String jsonWrite(String &json, String name, int volume);
    //bool isExistFile(String);
   // File getFile(String);

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

    String jsonWriteBool(String &json, String name, bool volume);
    String findColor(String id);


};

#endif