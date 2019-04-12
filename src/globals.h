#ifndef _GLOBALS_H_
#define _GLOBALS_H_

struct {
  String IPAddress;
  bool isAP;
  bool isWS;
  bool isArduinoConnected;
  bool isPumped;
  bool canFill;
  String curSSID;
  String curPass;
} state;

struct Comm{
  String code;
  String value;
};

#endif