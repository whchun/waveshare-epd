#include "frame.h"

Frame::Frame(): _buffer(NULL), _bufferSize(0)
{
}

Frame::~Frame()
{
    delete[] _buffer;
    _buffer = nullptr;
    _bufferSize = 0;
}

void Frame::setBuffer(CommandType commandType, uint8_t *params)
{
    Command *command = Constant::getCommandData(commandType);
    _bufferSize = command->getCommandFrameSize();

    int offset = 0;
    _buffer = new uint8_t[_bufferSize];

    // Frame header
    _buffer[0] = Constant::frameHeader;
    offset += 1;

    // Frame Length
    int frameLengthSize = command->getFrameLengthSize();    
    memcpy(
        _buffer + offset,
        command->getFrameLengthBytes(),
        frameLengthSize * sizeof(uint8_t)
    );
    offset += frameLengthSize;

    // Command
    _buffer[offset] = command->getCommandByte();
    offset += 1;

    // Params
    if (params != NULL) {
        int paramSize = command->getParamSize();
        memcpy(
            _buffer + offset,
            params,
            paramSize * sizeof(uint8_t)
        );
        offset += paramSize;
    }

    // Frame end
    memcpy(
        _buffer + offset,
        Constant::frameEnd,
        Constant::frameEndSize * sizeof(uint8_t)
    );
    offset += Constant::frameEndSize;

    // Parity byte
    _buffer[offset] = getParityByte();
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

int Frame::getBufferSize()
{
    return _bufferSize;
}