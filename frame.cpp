#include "frame.h"

Frame::Frame()
{
    _buffer = NULL;
    _bufferLength = 0;
}

Frame::~Frame()
{
    delete[] _buffer;
    _buffer = nullptr;
}

void Frame::setBuffer(CommandType commandType)
{
    Command *command = Constant::getCommandData(commandType);
    _bufferLength = command->getCommandSize();
    int offset = command->getOffset();
    _buffer = new uint8_t[_bufferLength];

    _buffer[0] = Constant::frameHeader;
    // // // Fix 1, 2
    _buffer[1] = 0x00;
    _buffer[2] = 0x09;
    _buffer[3] = command->getCommandByte();
    // TODO: Add param
    memcpy(_buffer+offset, Constant::frameEnd, Constant::frameEndSize*sizeof(uint8_t));

    _buffer[8] = getParityByte();
}

unsigned char* Frame::getBuffer()
{
    return &_buffer[0];
}

uint8_t Frame::getParityByte()
{
    // Add error checking
    if (_bufferLength <= 0)
        return 0x00;

    uint8_t parityByte = _buffer[0];
    for (int i = 1; i < _bufferLength-1; i++) {
        parityByte ^= _buffer[i];
    }
    return parityByte;
}