#pragma once

#include <Arduino.h>

/*
 * Command from command look-up table
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 */
enum CommandType
{
    SLEEP,
    UPDATE_DISPLAY,
    CLEAR,
    SET_FONT,
    DISPLAY_TEXT,
};

enum FontSize
{
    SIZE_32 = 1,
    SIZE_48 = 2,
    SIZE_64 = 3,
};