#include "epd.h"

WaveshareEPD::WaveshareEPD(uint8_t resetPin, uint8_t wakeupPin, uint8_t rx, uint8_t tx) : _resetPin(resetPin), _wakeupPin(wakeupPin)
{
    // TODO: Try serial not software serial
    _serial = new SoftwareSerial(rx, tx);
}

void WaveshareEPD::init()
{
    _serial->begin(115200);
    // TODO: Update to digitalwrite
    pinMode(_wakeupPin, HIGH);
    pinMode(_resetPin, HIGH);
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

void WaveshareEPD::render(CommandType commandType)
{
    Frame *frame = new Frame();
    frame->setBuffer(commandType);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::renderText(FontSize fontSize, int x, int y, const char *text)
{
    Frame *frame = new Frame();

    // Set Font
    FrameParam *fontParam = new FrameParam(new uint8_t[1]{(uint8_t)fontSize}, 1);
    frame->setBuffer(SET_FONT, fontParam);
    _serial->write(frame->getBuffer(), frame->getBufferSize());

    frame->resetBuffer();

    // Display text
    FrameParam *params = getParamBuffer(x, y, text);
    frame->setBuffer(DISPLAY_TEXT, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::renderImage(int x, int y, const char *fileName)
{
    Frame *frame = new Frame();

    FrameParam *params = getParamBuffer(x, y, fileName);
    frame->setBuffer(DISPLAY_TEXT, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

FrameParam *WaveshareEPD::getParamBuffer(int x, int y, const char *str)
{
    int strLength = strlen(str);
    Coordinate coord = {x, y};

    int coordBytesSize = coord.getShortBytesSize();
    int paramSize = coordBytesSize + strLength;

    uint8_t *param = new uint8_t[paramSize];
    memcpy(param, coord.getShortBytes(), coordBytesSize * sizeof(uint8_t));
    memcpy(param + coordBytesSize, str, strLength * sizeof(uint8_t));

    return new FrameParam(param, paramSize);
}