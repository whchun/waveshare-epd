#ifndef FRAME_H
#define FRAME_H

#include "types.h"
#include "constant.h"
#include "command.h"

#include <Arduino.h>

class Frame
{
    public:
        Frame();
        ~Frame();

        void setBuffer(CommandType, uint8_t * params=NULL);
        uint8_t *getBuffer();
        int getBufferSize();

    private:
        uint8_t getParityByte();

        uint8_t *_buffer;
        int _bufferSize;
        
};

#endif