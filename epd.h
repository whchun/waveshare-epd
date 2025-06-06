/**
 * @file epd.h
 * @brief E-paper display object used in Arduino.
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-05-01
 */
#ifndef EPD_H
#define EPD_H

#include "types.h"
#include "shape.h"
#include "frame.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

#define BAUD_RATE 115200

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
    void sleep();

    // Render
    void drawShape(ShapeType, Shape *, bool fill = false);
    void drawText(int, int, const char *);
    void drawImage(int, int, const char *);

    // Config
    void setFontSize(FontSize);
    void setColor(Color, Color);

private:
    SoftwareSerial *_serial;
    uint8_t _wakeupPin;
    uint8_t _resetPin;

    FrameParam *getTextParamBuffer(int, int, const char *);
};
#endif