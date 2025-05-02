/**
 * @file epd.cpp
 * @brief E-paper display object used in Arduino.
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-05-01
 */
#include "epd.h"

WaveshareEPD::WaveshareEPD(uint8_t resetPin, uint8_t wakeupPin, uint8_t rx, uint8_t tx) : _resetPin(resetPin), _wakeupPin(wakeupPin)
{
    // TODO: Try serial not software serial
    _serial = new SoftwareSerial(rx, tx);
}

void WaveshareEPD::init()
{
    _serial->begin(BAUD_RATE);

    digitalWrite(_wakeupPin, HIGH);
    digitalWrite(_resetPin, HIGH);
}

void WaveshareEPD::wakeup()
{
    digitalWrite(_wakeupPin, LOW);
    delayMicroseconds(10);

    digitalWrite(_wakeupPin, HIGH);
    delayMicroseconds(500);

    digitalWrite(_wakeupPin, LOW);
    delay(10);
}

void WaveshareEPD::reset()
{
    digitalWrite(_resetPin, LOW);
    delayMicroseconds(10);

    digitalWrite(_resetPin, HIGH);
    delayMicroseconds(500);

    digitalWrite(_resetPin, LOW);
    delay(3000);
}

void WaveshareEPD::clearDisplay()
{
    Frame *frame = new Frame();
    frame->setBuffer(CLEAR_DISPLAY);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::rotateDisplay(Orientation orientation)
{
    uint8_t data = static_cast<uint8_t>(orientation);
    FrameParam *params = new FrameParam(&data, sizeof(uint8_t));

    Frame *frame = new Frame();
    frame->setBuffer(ROTATE_DISPLAY, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::updateDisplay()
{
    Frame *frame = new Frame();
    frame->setBuffer(UPDATE_DISPLAY);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::drawShape(ShapeType shapeType, Shape *data, bool fill)
{
    CommandType commandType;
    switch (shapeType)
    {
    case LINE:
        commandType = DRAW_LINE;
        break;
    case RECTANGLE:
        commandType = fill ? FILL_DRAW_RECTANGLE : DRAW_RECTANGLE;
        break;
    case CIRCLE:
        commandType = fill ? FILL_DRAW_CIRCLE : DRAW_CIRCLE;
        break;
    case TRIANGLE:
        commandType = fill ? FILL_DRAW_TRIANGLE : DRAW_TRIANGLE;
        break;
    default:
        break;
    }

    Frame *frame = new Frame();

    FrameParam *shapeParam = new FrameParam(data->getBytes(), data->getBytesSize());
    frame->setBuffer(commandType, shapeParam);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::drawText(int x, int y, const char *text)
{
    Frame *frame = new Frame();
    FrameParam *params = getTextParamBuffer(x, y, text);
    frame->setBuffer(DISPLAY_TEXT, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::drawImage(int x, int y, const char *fileName)
{
    // Image uses same as text parameter
    Frame *frame = new Frame();
    FrameParam *params = getTextParamBuffer(x, y, fileName);
    frame->setBuffer(DISPLAY_IMAGE, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::setFontSize(FontSize fontSize)
{
    Frame *frame = new Frame();

    uint8_t data = static_cast<uint8_t>(fontSize);
    FrameParam *fontParam = new FrameParam(&data, sizeof(uint8_t));
    frame->setBuffer(SET_FONT, fontParam);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::setColor(Color foreground, Color background)
{
    Frame *frame = new Frame();

    int paramSize = 2;
    FrameParam *param = new FrameParam(new uint8_t[paramSize]{foreground, background}, paramSize * sizeof(uint8_t));
    frame->setBuffer(SET_COLOR, param);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

FrameParam *WaveshareEPD::getTextParamBuffer(int x, int y, const char *str)
{
    int strLength = strlen(str);
    Point *point = new Point(x, y);

    int pointBytesSize = point->getBytesSize();
    int paramSize = pointBytesSize + strLength;

    uint8_t *param = new uint8_t[paramSize];
    memcpy(param, point->getBytes(), pointBytesSize * sizeof(uint8_t));
    memcpy(param + pointBytesSize, str, strLength * sizeof(uint8_t));

    return new FrameParam(param, paramSize);
}
