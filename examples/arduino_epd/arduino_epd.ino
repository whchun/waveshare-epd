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

    display->rotateDisplay(ORIENTATION_0);

    // Draw shape
    Line *line = new Line({100, 100}, {200, 200});
    display->drawShape(LINE, line);

    Rectangle *rect = new Rectangle({300, 300}, {350, 350});
    display->drawShape(RECTANGLE, rect, true);

    Circle *circle = new Circle({100, 100}, 25);
    display->drawShape(CIRCLE, circle);

    Triangle *triangle = new Triangle({300, 10}, {275, 60}, {325, 60});
    display->drawShape(TRIANGLE, triangle);

    // Draw text
    display->drawText(300, 200, "Hello World", SIZE_64);

    // Update display
    display->updateDisplay();
}

void loop(void)
{
}