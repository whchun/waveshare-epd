/**
 * @file frame.cpp
 * @brief Command frame buffer.
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-03-24
 */
#include "frame.h"

int FrameParam::getBytesSize()
{
    return _size;
}

uint8_t *FrameParam::getBytes()
{
    return _data;
}

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
        command->setParamSize(params->getBytesSize());
    }

    int offset = 0;
    _bufferSize = command->getCommandFrameSize();
    _buffer = new uint8_t[_bufferSize];

    // Frame header
    _buffer[0] = FRAME_HEADER;
    offset += sizeof(uint8_t);

    // Frame Length
    int frameLengthSize = command->getFrameLengthSize();
    memcpy(
        _buffer + offset,
        command->getFrameLengthBytes(),
        frameLengthSize * sizeof(uint8_t));
    offset += frameLengthSize;

    // Command
    _buffer[offset] = command->getCommandByte();
    offset += sizeof(uint8_t);

    // Params
    if (params != NULL)
    {
        memcpy(
            _buffer + offset,
            params->getBytes(),
            params->getBytesSize() * sizeof(uint8_t));
        offset += params->getBytesSize();
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
    for (int i = 1; i < _bufferSize - 1; i += sizeof(uint8_t))
    {
        parityByte ^= _buffer[i];
    }
    return parityByte;
}

int Frame::getBufferSize()
{
    return _bufferSize;
}