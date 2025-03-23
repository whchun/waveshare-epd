#pragma once

#include <Arduino.h>

enum CommandType {
    HANDSHAKE,
    UPDATE_DISPLAY
};

enum ParamType {
    NONE,
    BYTE,
    SHORT,
    DWORD,
    STRING
};