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
    SET_COLOR,
    DRAW_LINE,
    DRAW_RECTANGLE,
    DRAW_CIRCLE,
    DRAW_TRIANGLE,
    FILL_DRAW_RECTANGLE,
    FILL_DRAW_CIRCLE,
    FILL_DRAW_TRIANGLE,
    SET_FONT,
    DISPLAY_TEXT,
    DISPLAY_IMAGE,
};

enum Orientation
{
    ORIENTATION_0 = 0,
    ORIENTATION_90 = 1,
    ORIENTATION_180 = 2,
    ORIENTATION_270 = 3,
};

enum ShapeType
{
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
};

enum Color
{
    BLACK = 0,
    DARK_GRAY = 1,
    LIGHT_GRAY = 2,
    WHITE = 3,
};

enum FontSize
{
    SIZE_32 = 1,
    SIZE_48 = 2,
    SIZE_64 = 3,
};