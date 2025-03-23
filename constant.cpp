#include "constant.h"

const uint8_t Constant::frameEnd[Constant::frameEndSize] = {0xCC, 0x33, 0xC3, 0x3C};

const Command Constant::commands[Constant::commandSize] = {
    Command(SLEEP, 0x08, NONE, 0),
    Command(UPDATE_DISPLAY, 0x0A, NONE, 0)
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