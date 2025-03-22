#ifndef FRAME_H
#define FRAME_H

// #include "constant.h"
#include <Arduino.h>

// #define FRAME_HEADER 0xA5
// #define FRAME_END {0xCC, 0x33, 0xC3, 0x3C}

class Frame
{
    public:
        Frame();
        ~Frame();

        void setBuffer(uint8_t);
        uint8_t *getBuffer();

    private:
        uint8_t getParityByte();
        int getCommandParameterLength(uint8_t);

        uint8_t *buffer;
        int bufferLength;
        
};

#endif