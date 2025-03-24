#include "constant.h"

const uint8_t Constant::frameEnd[FRAME_END_SIZE] = {0xCC, 0x33, 0xC3, 0x3C};

const Command Constant::commands[COMMAND_SIZE] = {
    Command(SLEEP, 0x08),
    Command(UPDATE_DISPLAY, 0x0A),
    Command(CLEAR, 0x2E),
    Command(SET_FONT, 0x1E),
    Command(DISPLAY_TEXT, 0x30),
    Command(DISPLAY_IMAGE, 0x70)};

Command *Constant::getCommandData(CommandType commandType)
{
    Command *ptr = &Constant::commands[0];
    while (ptr != NULL)
    {
        if (ptr->getCommandType() == commandType)
            return ptr;
        ptr++;
    }
    return NULL;
}