#include "epd.h"

WaveshareEPD::WaveshareEPD(uint8_t resetPin, uint8_t wakeupPin, uint8_t rx, uint8_t tx) :
    resetPin(resetPin), wakeupPin(wakeupPin)
{
    // TODO: Try serial not software serial
    serial = new SoftwareSerial(rx, tx);
}

void WaveshareEPD::init()
{
    serial->begin(115200);
    // TODO: Update to digitalwrite
    pinMode(wakeupPin, HIGH);
    pinMode(resetPin, HIGH);
}

void WaveshareEPD::wakeup()
{
    digitalWrite(wakeupPin, LOW);
    delayMicroseconds(10);

    digitalWrite(wakeupPin, HIGH);
    delayMicroseconds(500);

    digitalWrite(wakeupPin, LOW);
    delay(10);
}

void WaveshareEPD::reset()
{
    digitalWrite(resetPin, LOW);
    delayMicroseconds(10);

    digitalWrite(resetPin, HIGH);
    delayMicroseconds(500);

    digitalWrite(resetPin, LOW);
    delay(3000);
}

void WaveshareEPD::test()
{
    //A5 00 09 00 CC 33 C3 3C AC 
    // Frame frame = new Frame(0x00);
    // serial->write(frame.getBuffer(), 9);
    Frame *frame = new Frame();
    frame->setBuffer(0x0A);
    serial->write(frame->getBuffer(), 9);

    serial->println("TEST");
    delete frame;
    // unsigned char buf[9] = {0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C, 0xAC };
    // // unsigned char  buf[9] = {0xA5, 0x00, 0x09, 0x2E, 0xCC, 0x33, 0xC3, 0x3C, 0x82};
    // serial->write(buf, 9);  
    // unsigned char buf1[9] = {0xA5, 0x00, 0x09, 0x0A, 0xCC, 0x33, 0xC3, 0x3C, 0xA6};
    // serial->write(buf1, 9);
}