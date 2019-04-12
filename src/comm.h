#ifndef _COMM_H_
#define _COMM_H_
#include <Arduino.h>
#include "globals.h"
Comm readCom() {
  Comm out;// v1,v2;  
  if(Serial.available() > 0) {  
        String str = Serial.readStringUntil('\n');
        char* frag1, *frag2;
        char buf[30];
        
        str.toCharArray(buf,30);
        frag1 = strtok(buf,":");
        frag2 = strtok(NULL,":");
        if (frag1) out.code=(String)frag1;
        if (frag2) out.value=(String)frag2;
        out.code.trim();
        out.value.trim();
        return out;
        //Serial.print("-> ");
        //Serial.println(v1+ " *** "+v2);

        /* OLD
        if (v1 == "M9") {
          //option.servoMAX = v2.toInt();
          jsonWrite(configSetup,"servoMIN",v2.toInt());
          sendCom("M9","OK");
        }
        
        if (v1 == "M10") {
          //option.servoMIN = v2.toInt();
          jsonWrite(configSetup,"servoMIN",v2.toInt());
          sendCom("M10","OK");
        }

        if (v1.toInt()) {
          DSEvent(v1.toInt(), v2);
        }
        
      if (curFrame == F_ACTION) {
        if (v1== "M5" && v2 == "OK" && curMPos == 5) {
          doAction = 0;
          curFrame = F_MENU;          
        }

        if (v1== "M8" && v2 == "OK" && curMPos == 22) {
          doAction = 0;
          curFrame = F_MENU;          
        }
        if (v1== "M4" && v2 == "OK" && (curMPos == 20 || curMPos == 21)) {
          doAction = 0;
          curFrame = F_MENU;          
        }
      }*/
  }
  out.code="";
  out.value="";
  return out;
}

Comm formComm(String code, String value) {
    Comm ret{code,value};
    return ret;
}

void sendCom(Comm send) {
    Serial.println(send.code + ":" + send.value);
}
void sendCom(String code, String value) {
    Serial.println(code + ":" + value);
}
bool reqAnsComm(Comm send, Comm request, int time) {
    bool wait = true;
    sendCom(send);
    uint t = millis();
    while(wait){
        Comm ans = readCom();
        if (ans.code == request.code && ans.value == request.value) return true;
        if (t+time < millis()) wait=false;
    }
    return false;
}

bool startComm(){
    state.isArduinoConnected = false;
    //sendCom();
    while(!state.isArduinoConnected){
        if (reqAnsComm(formComm("RESET","0"),formComm("INIT","ARDU"),3000)){
            //sendCom("ESP","0");
            state.isArduinoConnected = true;
        }
    }
    if (reqAnsComm(formComm("ESP","0"),formComm("READY","0"),15000)) return true;

    return false;
    
}

#endif