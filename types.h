#pragma once

#include <Arduino.h>

/*
 * Command from command look-up table
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 */
enum CommandType
{
    SLEEP,
    CLEAR_DISPLAY,
    UPDATE_DISPLAY,
    ROTATE_DISPLAY,
    // Set color
    SET_FONT,
    DRAW_LINE,
    DRAW_RECTANGLE,
    DRAW_CIRCLE,
    DRAW_TRIANGLE,
    DISPLAY_TEXT,
    DISPLAY_IMAGE,
};

enum FontSize
{
    SIZE_32 = 1,
    SIZE_48 = 2,
    SIZE_64 = 3,
};

enum Orientation
{
    ORIENTATION_0 = 0,
    ORIENTATION_90 = 1,
    ORIENTATION_180 = 2,
    ORIENTATION_270 = 3,
};

struct Coordinate
{
    int x;
    int y;

    int getShortBytesSize()
    {
        // 2 bytes for x, y
        return 4;
    }

    uint8_t *getShortBytes()
    {
        int bytesSize = getShortBytesSize();
        uint8_t *bytes = new uint8_t[bytesSize];
        bytes[0] = (x >> 8) & 0xFF;
        bytes[1] = x & 0xFF;
        bytes[2] = (y >> 8) & 0xFF;
        bytes[3] = y & 0xFF;

        return bytes;
    }
};
