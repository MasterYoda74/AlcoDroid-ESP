#ifndef _LEDS_H_
#define _LEDS_H_
#include "defines.h"
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>



class LedsClass {
    public:
    LedsClass();
    void init();
    void setBright(int);
    void clear();


    private:
    CRGB leds[NUM_LEDS_IN];

};


#endif