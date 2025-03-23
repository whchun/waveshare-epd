#include "command.h"

Command::Command(CommandType commandType, uint8_t commandByte, ParamType paramType) :
    _commandType(commandType), _commandByte(commandByte), _paramType(paramType)
{

}

uint8_t Command::getCommandByte()
{
    return _commandByte;
}

CommandType Command::getCommandType()
{
    return _commandType;
}

int Command::getCommandSize()
{
    // Frame header + length + command + param + frame end + parity
    int paramLength = getParamLength();
    return 9 + paramLength;
}

int Command::getParamLength()
{
    switch(_paramType) {
        case NONE:
            return 0;
        case BYTE:
            return 1;
        case SHORT:
            return 2;
        case DWORD:
            return 4;
        default:
            return 100; // TODO: Fix string
    }
}

int Command::getFrameLength()
{
    return 2; // TODO: Fix this
}

uint8_t *Command::getFrameLengthByte()
{
    int frameLength = getFrameLength();
    if (_paramType == NONE) {
        return new uint8_t[frameLength]{0x00, 0x09};
    }
    // TODO: ADD
    return {};
}

int Command::getOffset()
{
    return 2 + getFrameLength() + getParamLength();
}