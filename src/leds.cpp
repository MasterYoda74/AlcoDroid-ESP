#include "leds.h"

LedsClass::LedsClass() {

}

void LedsClass::init() {
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS_IN);
    //FastLED.addLeds<NEOPIXEL,LED_DATA_PIN
}
void LedsClass::clear() {
    FastLED.clear();
}
void LedsClass::setBright(int val) {
    FastLED.setBrightness(val);//option.ledbright);
}