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
    // TODO: Fix this
    bufferLength = 9;
    buffer = new uint8_t[bufferLength];

    buffer[0] = 0xA5;
    // // Fix 1, 2
    buffer[1] = 0x00;
    buffer[2] = 0x09;
    buffer[3] = (uint8_t)command;
    // // Fix this param
    buffer[4] = 0xCC;
    buffer[5] = 0x33;
    buffer[6] = 0xC3;
    buffer[7] = 0x3C;
    buffer[8] = getParityByte();
}

unsigned char* Frame::getBuffer()
{
    return &buffer[0];
}

uint8_t Frame::getParityByte()
{
    // Add error checking
    // if (bufferLength <= 0)
    //     return 0x00;

    uint8_t parityByte = buffer[0];
    for (int i = 1; i < bufferLength; i++) {
        parityByte ^= buffer[i];
    }
    return parityByte;
}

int Frame::getCommandParameterLength(uint8_t command)
{
    return 0;
}