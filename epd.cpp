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

void WaveshareEPD::clearDisplay()
{
    Frame *frame = new Frame();
    frame->setBuffer(CLEAR_DISPLAY);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::rotateDisplay(Orientation orientation)
{
    uint8_t data = static_cast<uint8_t>(orientation);
    FrameParam *params = new FrameParam(&data, 1);

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

// void WaveshareEPD::render(CommandType commandType, void *param)
// {
//     Frame *frame = new Frame();
//     FrameParam *params = NULL;
//     if (param != NULL)
//     {
//         uint8_t *data = static_cast<uint8_t *>(param);
//         params = new FrameParam(data, 1);
//     }

//     frame->setBuffer(commandType, params);
//     _serial->write(frame->getBuffer(), frame->getBufferSize());
// }

void WaveshareEPD::renderText(FontSize fontSize, int x, int y, const char *text)
{
    Frame *frame = new Frame();

    // Set Font
    FrameParam *fontParam = new FrameParam(new uint8_t[1]{(uint8_t)fontSize}, 1);
    frame->setBuffer(SET_FONT, fontParam);
    _serial->write(frame->getBuffer(), frame->getBufferSize());

    frame->resetBuffer();

    // Display text
    FrameParam *params = getTextParamBuffer(x, y, text);
    frame->setBuffer(DISPLAY_TEXT, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

void WaveshareEPD::renderImage(int x, int y, const char *fileName)
{
    Frame *frame = new Frame();

    // Image use same as text
    FrameParam *params = getTextParamBuffer(x, y, fileName);
    frame->setBuffer(DISPLAY_IMAGE, params);
    _serial->write(frame->getBuffer(), frame->getBufferSize());
}

FrameParam *WaveshareEPD::getTextParamBuffer(int x, int y, const char *str)
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