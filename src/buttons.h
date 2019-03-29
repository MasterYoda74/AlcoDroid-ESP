#ifndef _BUTTONS_H_
#define _BUTTONS_H_
#include <AceButton.h>

using namespace ace_button;
ButtonConfig menuConfig;
AceButton bLeft(&menuConfig);
AceButton bRight(&menuConfig);
AceButton bOk(&menuConfig);

void Buttons_init();
void handleMenuEvent(AceButton*, uint8_t, uint8_t);
void onRepeat(int id);
void onClick(int id);
void onHold(int id);
#endif