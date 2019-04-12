#ifndef _BUTTONS_H_
#define _BUTTONS_H_
#include <AceButton.h>
#include "defines.h"
using namespace ace_button;
void handleMenuEvent(AceButton*, uint8_t, uint8_t);
void onRepeat(int id);
void onClick(int id);
void onHold(int id); 

ButtonConfig menuConfig;
AceButton bLeft(&menuConfig);
AceButton bRight(&menuConfig);
AceButton bOk(&menuConfig);

void buttons_init() {

        menuConfig.setEventHandler(handleMenuEvent);
        menuConfig.setFeature(ButtonConfig::kFeatureClick);
        menuConfig.setFeature(ButtonConfig::kFeatureRepeatPress);
        menuConfig.setFeature(ButtonConfig::kFeatureSuppressAfterClick);
        menuConfig.setFeature(ButtonConfig::kFeatureSuppressAfterRepeatPress);
        menuConfig.setFeature(ButtonConfig::kFeatureLongPress);
        menuConfig.setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);
        pinMode(LEFT_PIN, INPUT_PULLUP);
        bLeft.init(LEFT_PIN, HIGH, 0 /* id */);
        pinMode(RIGHT_PIN, INPUT_PULLUP);
        bRight.init(RIGHT_PIN, HIGH, 1 /* id */); 
        pinMode(OK_PIN, INPUT_PULLUP);
        bOk.init(OK_PIN, HIGH, 2 /* id */);
        
}

void buttons_check() {
  bLeft.check();
  bRight.check();
  bOk.check();
}

void handleMenuEvent(AceButton* button, uint8_t eventType,
    uint8_t /* buttonState */) {
  switch (eventType) {
    case AceButton::kEventReleased:
      onClick(button->getId());
      break;
    case AceButton::kEventLongPressed:
      onHold(button->getId());
      break;
    case AceButton::kEventRepeatPressed:
      onRepeat(button->getId());
      break;   
  }
}

#endif