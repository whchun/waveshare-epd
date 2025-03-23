#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <Arduino.h>

#define NUM_FRAME_LENGTH_BYTES 2

class Command
{
    public:
        Command(CommandType, uint8_t, ParamType, int);

        CommandType getCommandType();

        uint8_t getCommandByte();
        uint8_t* getFrameLengthBytes();

        int getCommandFrameSize();
        int getFrameLengthSize();
        int getParamSize();

    private:
        CommandType _commandType;
        uint8_t _commandByte;
        ParamType _paramType;
        int _paramSize;
};

#endif