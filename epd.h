#ifndef EPD_H
#define EPD_H

#include "types.h"
#include "shape.h"
#include "frame.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

class WaveshareEPD
{
public:
    WaveshareEPD(uint8_t, uint8_t, uint8_t, uint8_t);

    void init();
    void wakeup();
    void reset();

    // Screen related
    void clearDisplay();
    void rotateDisplay(Orientation orientation = ORIENTATION_0);
    void updateDisplay();

    // Render
    void drawShape(ShapeType, Shape *, bool fill = false);
    void drawText(int, int, const char *, FontSize fontSize = SIZE_32);
    void drawImage(int, int, const char *);

private:
    SoftwareSerial *_serial;
    uint8_t _wakeupPin;
    uint8_t _resetPin;

    FrameParam *getTextParamBuffer(int, int, const char *);
};
#endif