#ifndef _FSYSTEM_H_
#define _FSYSTEM_H_

#include <Arduino.h>

void FS_init();
void saveConfig ();
String readFile(String fileName, size_t len );
String writeFile(String fileName, String strings );

#endif