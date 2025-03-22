#ifndef CONSTANT_H
#define CONSTANT_H

#include <Arduino.h>

class Constant
{
    public:
        static const uint8_t frameHeader = 0xA5;
        static constexpr uint8_t frameEnd[] = {0xCC, 0x33, 0xC3, 0x3C};
};

#endif