#include "leds.h"

LedsClass::LedsClass() {

}

void LedsClass::init() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}