#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <Arduino.h>

#define NUM_FRAME_LENGTH_BYTES 2

class Command
{
    public:
        Command(CommandType, uint8_t);

        CommandType getCommandType();

        uint8_t getCommandByte();
        uint8_t* getFrameLengthBytes();

        int getCommandFrameSize();
        int getFrameLengthSize();
        int getParamSize();
        void setParamSize(int);

    private:
        CommandType _commandType;
        uint8_t _commandByte;
        int _paramSize;
};

#endif