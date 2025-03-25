#ifndef FRAME_H
#define FRAME_H

#include "types.h"
#include "constant.h"
#include "command.h"

#include <Arduino.h>

class FrameParam
{
public:
    FrameParam(uint8_t *data, int size) : _data(data), _size(size) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    uint8_t *_data;
    int *_size;
};
class Frame
{
public:
    Frame();
    ~Frame();

    void setBuffer(CommandType, FrameParam *params = NULL);
    uint8_t *getBuffer();
    void resetBuffer();
    int getBufferSize();

private:
    uint8_t getParityByte();

    uint8_t *_buffer;
    int _bufferSize;
};

#endif