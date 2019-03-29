#include "buttons.h"
#include "defines.h"


void Buttons_init() {
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

void onRepeat(int id){

}
void onClick(int id){

}
void onHold(int id){
    
}