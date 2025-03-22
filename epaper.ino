#include "epd.h"

#define WAKEUP_PIN 2
#define RESET_PIN 3
#define RX_PIN 0
#define TX_PIN 1

WaveshareEPD *display = new WaveshareEPD(RESET_PIN, WAKEUP_PIN, RX_PIN, TX_PIN);

void setup(void)
{
    display->init();                                   // Initialize comunication with device
    display->wakeup();                                       // Wake up device
    display->reset();                                        // Reset device

    display->test();
    // display->updateScreen();                                 // Update screen
    // display->goSleep();    

}

void loop(void)
{

}
