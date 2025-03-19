#include "epd.h"
#include <Arduino.h>

WaveshareEPD::WaveshareEPD(int wakeupPin, int resetPin) //Adafruit_GFX(800, 600), 
    : wakeupPin(wakeupPin), resetPin(resetPin)
{
}

WaveshareEPD::~WaveshareEPD()
{
}

void WaveshareEPD::init()
{
    Serial.begin(115200);
    digitalWrite(wakeupPin, HIGH);
    digitalWrite(resetPin, HIGH);
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

void WaveshareEPD::update()
{
    unsigned char frameBuffer[9] = {0xA5, 0x00, 0x09, 0x0A, 0xCC, 0x33, 0xC3, 0x3C, 0x00};
    unsigned char parityByte = getParityByte(frameBuffer);
    frameBuffer[8] = parityByte;
    writeSerialPort(frameBuffer);
}

void WaveshareEPD::sleep()
{
    unsigned char frameBuffer[9] = {0xA5, 0x00, 0x09, 0x08, 0xCC, 0x33, 0xC3, 0x3C, 0x00};
    unsigned char parityByte = getParityByte(frameBuffer);
    frameBuffer[8] = parityByte;
    writeSerialPort(frameBuffer);
}

void WaveshareEPD::setMemory()
{
    unsigned char frameBuffer[10] = {0xA5, 0x00, 0x0A, 0x07, 0, 0xCC, 0x33, 0xC3, 0x3C, 0x00};
    unsigned char parityByte = getParityByte(frameBuffer);
    frameBuffer[9] = parityByte;
    writeSerialPort(frameBuffer);
}
void WaveshareEPD::setColor()
{
    int frameBufferSize = 11; // TODO: Fix
    unsigned char *frameBuffer = (unsigned char*)calloc(frameBufferSize, sizeof(unsigned char));
    frameBuffer[0] = 0xA5;
    frameBuffer[1] = 0x00;
    frameBuffer[2] = 0x0B;
    frameBuffer[3] = 0x10;
    // Param
    frameBuffer[4] = 0x01;
    frameBuffer[5] = 0x02;

    // Frame end
    frameBuffer[6] = 0xCC;
    frameBuffer[7] = 0x33;
    frameBuffer[8] = 0xC3;
    frameBuffer[9] = 0x3C;

    // Parity
    unsigned char parityByte = getParityByte(frameBuffer);
    frameBuffer[10] = parityByte;

    writeSerialPort(frameBuffer);
}

void WaveshareEPD::drawCircle(int x0, int y0, int r)
{
    int frameBufferSize = 15; // TODO: Fix
    unsigned char *frameBuffer = (unsigned char*)calloc(frameBufferSize, sizeof(unsigned char));
    frameBuffer[0] = 0xA5;
    // TODO: Fix this
    // Frame length
    frameBuffer[1] = 0x00;
    frameBuffer[2] = 0x1F;
    // Command Type
    frameBuffer[3] = 0x26;

    // Param
    frameBuffer[4] = (x0 >> 8) & 0xFF;
	frameBuffer[5] = x0 & 0xFF;
	frameBuffer[6] = (y0 >> 8) & 0xFF;
	frameBuffer[7] = y0 & 0xFF;
	frameBuffer[8] = (r >> 8) & 0xFF;
	frameBuffer[9] = r & 0xFF;

    // Frame end
    frameBuffer[10] = 0xCC;
    frameBuffer[11] = 0x33;
    frameBuffer[12] = 0xC3;
    frameBuffer[13] = 0x3C;
    
    // Parity
    unsigned char parityByte = getParityByte(frameBuffer);
    frameBuffer[14] = parityByte;

    writeSerialPort(frameBuffer);

    Serial.print("Draw!");
    // Serial.print(frameBuffer);
    // // Delete
    // free(frameBuffer);
    // frameBuffer = NULL;
}

// Private
unsigned char WaveshareEPD::getParityByte(unsigned char *frameBuffer)
{
    unsigned char *ptr = frameBuffer;
    unsigned char parityBit = NULL;

    for (int i = 0; ptr[i] != NULL; i++) {
        parityBit ^= (ptr[i]);
    }
    return parityBit;
}

void WaveshareEPD::writeSerialPort(unsigned char *frameBuffer)
{
    unsigned char *ptr = frameBuffer;
    for (int i = 0; ptr[i] != NULL; i++) {
        Serial.write(ptr[i]);
    }
}