#ifndef FRAME_H
#define FRAME_H

#include "types.h"
#include "constant.h"
#include "command.h"

#include <Arduino.h>

struct FrameParam
{
    uint8_t *data = NULL;
    int size = 0;
    FrameParam(uint8_t *_data, int _size) : data(_data), size(_size) {};
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