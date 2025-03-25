/**
 * @file constant.h
 * @brief Constant variables used in the library.
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-03-24
 */
#ifndef CONSTANT_H
#define CONSTANT_H

#include "types.h"
#include "command.h"
#include <Arduino.h>

#define COMMAND_SIZE 15

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