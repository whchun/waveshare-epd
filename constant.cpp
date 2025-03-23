#include "constant.h"

const uint8_t Constant::frameEnd[Constant::frameEndSize] = {0xCC, 0x33, 0xC3, 0x3C};

const Command Constant::commands[1] = {
    Command(UPDATE_DISPLAY, 0x0A, NONE)
};

Command* Constant::getCommandData(CommandType commandType)
{
    Command *ptr = &Constant::commands[0];
    while(ptr != NULL) {
        if (ptr->getCommandType() == commandType)
            return ptr;
        ptr ++;
    }
    return NULL;
}