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
    uint8_t tt[10] = {0xA5, 0x00, 0x0A, 0x1E, 0x03, 0xCC, 0x33, 0xC3, 0x3C, 0xB2};
    _serial->write(tt, 10);
    // frame->setBuffer(SET_FONT, {0x03}, 1);
    // _serial->write(frame->getBuffer(), frame->getBufferSize());

    frame->resetBuffer();

    // Send Text
    int textLength = strlen(text);
    int paramSize = 4 + textLength;
    uint8_t *params = new uint8_t[paramSize];
    params[0] = (x >> 8) & 0xFF;
    params[1] = x & 0xFF;
    params[2] = (y >> 8) & 0xFF;
    params[3] = y & 0xFF;
    memcpy(params + 4, text, textLength * sizeof(uint8_t));
    frame->setBuffer(DISPLAY_TEXT, params, paramSize);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}