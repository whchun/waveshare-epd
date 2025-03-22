#include "epd.h"

#define WAKEUP_PIN 7
#define RESET_PIN 6
WaveshareEPD display;

void setup(void)
{
  display.init(WAKEUP_PIN, RESET_PIN);
}

void loop(void)
{

}
