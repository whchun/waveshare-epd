#ifndef CONSTANT_H
#define CONSTANT_H

#include "types.h"
#include "command.h"
#include <Arduino.h>

#define COMMAND_SIZE 11

#define FRAME_HEADER 0xA5
#define FRAME_END_SIZE 4

class Constant
{
public:
    static const uint8_t frameEnd[FRAME_END_SIZE];
    static const Command commands[COMMAND_SIZE];

    static Command *getCommandData(CommandType);
};

#endif