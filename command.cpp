#include "command.h"

Command::Command(CommandType commandType, uint8_t commandByte) : _commandType(commandType), _commandByte(commandByte), _paramSize(0)
{
}

CommandType Command::getCommandType()
{
    return _commandType;
}

int Command::getCommandFrameSize()
{
    return NUM_FRAME_BYTES + _paramSize;
}

int Command::getFrameLengthSize()
{
    return NUM_FRAME_LENGTH_BYTES;
}
uint8_t Command::getCommandByte()
{
    return _commandByte;
}

uint8_t *Command::getFrameLengthBytes()
{
    uint8_t *frameLengthBytes = new uint8_t[NUM_FRAME_LENGTH_BYTES];
    int frameLength = getCommandFrameSize();
    frameLengthBytes[0] = (frameLength >> 8) & 0xFF;
    frameLengthBytes[1] = frameLength & 0XFF;

    return frameLengthBytes;
}

void Command::setParamSize(int paramSize)
{
    _paramSize = paramSize;
}