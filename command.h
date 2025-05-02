/**
 * @file command.h
 * @brief Command and its byte date related.
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-05-01
 */
#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <Arduino.h>

// These are fixed size (except param)
#define NUM_FRAME_BYTES 9
#define NUM_FRAME_LENGTH_BYTES 2

class Command
{
public:
    Command(CommandType, uint8_t);

    CommandType getCommandType();

    int getCommandFrameSize();
    int getFrameLengthSize();
    uint8_t getCommandByte();
    uint8_t *getFrameLengthBytes();
    void setParamSize(int);

private:
    CommandType _commandType;
    uint8_t _commandByte;
    int _paramSize;
};

#endif