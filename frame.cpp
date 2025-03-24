#include "frame.h"

Frame::Frame() : _buffer(NULL), _bufferSize(0)
{
}

Frame::~Frame()
{
    resetBuffer();
}

void Frame::setBuffer(CommandType commandType, FrameParam *params)
{
    Command *command = Constant::getCommandData(commandType);

    if (params != NULL)
    {
        command->setParamSize(params->size);
    }

    int offset = 0;
    _bufferSize = command->getCommandFrameSize();
    _buffer = new uint8_t[_bufferSize];

    // Frame header
    _buffer[0] = FRAME_HEADER;
    offset += 1;

    // Frame Length
    int frameLengthSize = command->getFrameLengthSize();
    memcpy(
        _buffer + offset,
        command->getFrameLengthBytes(),
        frameLengthSize * sizeof(uint8_t));
    offset += frameLengthSize;

    // Command
    _buffer[offset] = command->getCommandByte();
    offset += 1;

    // Params
    if (params != NULL)
    {
        memcpy(
            _buffer + offset,
            params->data,
            params->size * sizeof(uint8_t));
        offset += params->size;
    }

    // Frame end
    memcpy(
        _buffer + offset,
        Constant::frameEnd,
        FRAME_END_SIZE * sizeof(uint8_t));
    offset += FRAME_END_SIZE;

    // Parity byte
    _buffer[offset] = getParityByte();
}

void Frame::resetBuffer()
{
    delete[] _buffer;
    _buffer = NULL;
    _bufferSize = 0;
}

unsigned char *Frame::getBuffer()
{
    return &_buffer[0];
}

uint8_t Frame::getParityByte()
{
    if (_bufferSize <= 0)
        return 0x00;

    uint8_t parityByte = _buffer[0];
    for (int i = 1; i < _bufferSize - 1; i++)
    {
        parityByte ^= _buffer[i];
    }
    return parityByte;
}

int Frame::getBufferSize()
{
    return _bufferSize;
}