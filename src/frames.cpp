#include "frames.h"
#include "images.h"
#include "defines.h"

//#include "system_inits.h"
// LOGO display
void fLogo(Adafruit_SSD1306 &d)
{
  d.clearDisplay();
  d.drawBitmap(0, 0, AlcoBot_Logo_FS, 128, 64, WHITE);
  d.setCursor(1,1);
  d.setTextColor(WHITE);
  d.print(VERSION);
  d.display();
}