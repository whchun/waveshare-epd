#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <Arduino.h>

class Command
{
    public:
        Command(CommandType, uint8_t, ParamType);

        CommandType getCommandType();
        int getCommandSize();
        uint8_t getCommandByte();
        uint8_t* getFrameLengthByte();
        int getOffset();

    private:
        CommandType _commandType;
        uint8_t _commandByte;
        ParamType _paramType;

        int getFrameLength();
        int getParamLength();
};

#endif