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

    display->clearDisplay();

    display->rotateDisplay(ORIENTATION_180);

    Line *line = new Line({100, 100}, {200, 200});
    display->drawShape(LINE, line);
    display->drawText(SIZE_64, 300, 200, "Hello World");

    display->updateDisplay();

}

void loop(void)
{
}