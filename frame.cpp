#include "frame.h"

Frame::Frame()
{
    buffer = NULL;
    bufferLength = 0;
}

Frame::~Frame()
{
    delete[] buffer;
    buffer = nullptr;
}

void Frame::setBuffer(uint8_t command)
{
    bufferLength = 9;
    buffer = new uint8_t[bufferLength];
    
    buffer[0] = Constant::frameHeader;
    // // Fix 1, 2
    buffer[1] = 0x00;
    buffer[2] = 0x09;
    buffer[3] = (uint8_t)command;
    memcpy(buffer+4, Constant::frameEnd, Constant::frameEndSize*sizeof(uint8_t));

    buffer[8] = getParityByte();
}

unsigned char* Frame::getBuffer()
{
    return &buffer[0];
}

uint8_t Frame::getParityByte()
{
    // Add error checking
    if (bufferLength <= 0)
        return 0x00;

    uint8_t parityByte = buffer[0];
    for (int i = 1; i < bufferLength-1; i++) {
        parityByte ^= buffer[i];
    }
    return parityByte;
}

int Frame::getCommandParameterLength(uint8_t command)
{
    return 0;
}