#include "frame.h"

Frame::Frame()
{
    _buffer = NULL;
    _bufferSize = 0;
}

Frame::~Frame()
{
    delete[] _buffer;
    _buffer = nullptr;
    _bufferSize = 0;
}

void Frame::setBuffer(CommandType commandType)
{
    Command *command = Constant::getCommandData(commandType);
    _bufferSize = command->getCommandFrameSize();

    _buffer = new uint8_t[_bufferSize];

    _buffer[0] = Constant::frameHeader;
    memcpy(
        _buffer+1,
        command->getFrameLengthBytes(),
        command->getFrameLengthSize()+sizeof(uint8_t)
    );
    _buffer[3] = command->getCommandByte();
    // TODO: Add param
    memcpy(
        _buffer+command->getFrameEndOffset(),
        Constant::frameEnd,
        Constant::frameEndSize*sizeof(uint8_t)
    );
    _buffer[8] = getParityByte();
}

unsigned char* Frame::getBuffer()
{
    return &_buffer[0];
}

uint8_t Frame::getParityByte()
{
    if (_bufferSize <= 0)
        return 0x00;

    uint8_t parityByte = _buffer[0];
    for (int i = 1; i < _bufferSize-1; i++) {
        parityByte ^= _buffer[i];
    }
    return parityByte;
}