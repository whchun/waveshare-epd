#include "epd.h"

WaveshareEPD::WaveshareEPD(uint8_t resetPin, uint8_t wakeupPin, uint8_t rx, uint8_t tx) :
    _resetPin(resetPin), _wakeupPin(wakeupPin)
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

void WaveshareEPD::test()
{
    Frame *frame = new Frame();
    frame->setBuffer(SET_FONT, {0x01}); // FIX
    _serial->write(frame->getBuffer(), frame->getBufferSize());

    Frame *frame1 = new Frame();
    uint8_t t1 = (300 >> 8) & 0xFF;
    uint8_t t2 = 300 & 0xFF;
    int x = 300;
    int y = 250;

    //uint8_t ch[8] = {0x00, 0x0A, 0x00, 0x0A, 0x40, 0x40, 0x40, 0x40};
    const char *text = "HELLO";
    int textLength = strlen(text);
    int paramSize = 4 + textLength;
    uint8_t *ch = new uint8_t[paramSize];
    ch[0] = 0x00;
    ch[1] = 0x0A;
    ch[2] = 0x00;
    ch[3] = 0x0A;
    memcpy(ch+4, text, textLength * sizeof(uint8_t));
    frame1->setBuffer(DISPLAY_TEXT, ch, paramSize); // FIX
    _serial->write(frame1->getBuffer(), frame1->getBufferSize());
}