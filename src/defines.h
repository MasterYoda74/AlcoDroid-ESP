#ifndef _DEFINES_H_
#define _DEFINES_H_

#define OLED_RESET      LED_BUILTIN

#define VERSION         "0.1.1"
#define VERSION_SPIFF   "0.1.1"
#define CONFIG_VERSION  "v03"
// Количество светодиодов в цепи
#define NUM_LEDS_IN        7
// Пин подключения светодиодов
#define LED_DATA_PIN        8
// Пины клавиатуры
#define LEFT_PIN        D5
#define OK_PIN          D6
#define RIGHT_PIN       D7
// Пины шаговика
#define DIR_PIN         D4
#define STEP_PIN        D3
#define ENABLE_PIN      D0
// Шагов на оборот
#define TOTAL_STEPS     200

#endif