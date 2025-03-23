#ifndef CONSTANT_H
#define CONSTANT_H

#include "types.h"
#include "command.h"
#include <Arduino.h>

class Constant
{
    public:
        static const uint8_t frameHeader = 0xA5;
        static const int frameEndSize = 4;
        static const uint8_t frameEnd[frameEndSize];

        static const int commandSize =  4;
        static const Command commands[commandSize];

        static Command* getCommandData(CommandType);

};

#endif