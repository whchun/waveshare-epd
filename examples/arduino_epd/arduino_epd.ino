#include <epd.h>

#define WAKEUP_PIN 2
#define RESET_PIN 3
#define RX_PIN 0
#define TX_PIN 1

WaveshareEPD *display = new WaveshareEPD(RESET_PIN, WAKEUP_PIN, RX_PIN, TX_PIN);

void setup(void)
{
    display->init();
    display->wakeup();
    display->reset();

    display->render(CLEAR);

    int param = ORIENTATION_180;
    display->render(ROTATE_SCREEN, &param);
    display->renderText(SIZE_64, 300, 200, "Hello World");

    display->render(UPDATE_DISPLAY);

}

void loop(void)
{
}