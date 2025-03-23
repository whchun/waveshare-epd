#include "command.h"

Command::Command(CommandType commandType, uint8_t commandByte, ParamType paramType, int paramByteSize) :
    _commandType(commandType), _commandByte(commandByte), _paramType(paramType), _paramByteSize(paramByteSize)
{

}

CommandType Command::getCommandType()
{
    return _commandType;
}

uint8_t Command::getCommandByte()
{
    return _commandByte;
}

uint8_t *Command::getFrameLengthBytes()
{
    uint8_t *frameLengthBytes = new uint8_t[NUM_FRAME_LENGTH_BYTES];
    int frameLength = getCommandFrameSize();
    frameLengthBytes[0] = (frameLength & 0x0000FF00) >> 8;
    frameLengthBytes[1] = (frameLength & 0x000000FF);
    
    return frameLengthBytes;
}

int Command::getCommandFrameSize()
{
    return 9 + _paramByteSize;
}

int Command::getFrameLengthSize()
{
    return NUM_FRAME_LENGTH_BYTES;
}

int Command::getFrameEndOffset()
{
    // TODO: Fix for string
    return 2 + getFrameLengthSize() + _paramByteSize;
}