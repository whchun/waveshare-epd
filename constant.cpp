#include "constant.h"

const uint8_t Constant::frameEnd[FRAME_END_SIZE] = {0xCC, 0x33, 0xC3, 0x3C};

const Command Constant::commands[COMMAND_SIZE] = {
    Command(SLEEP, 0x08),
    Command(CLEAR_DISPLAY, 0x2E),
    Command(ROTATE_DISPLAY, 0x0D),
    Command(UPDATE_DISPLAY, 0x0A),
    Command(SET_FONT, 0x1E),
    Command(DRAW_LINE, 0x22),      // 2 coord
    Command(DRAW_RECTANGLE, 0x25), // 2 coord (Fill is 24)
    Command(DRAW_CIRCLE, 0x26),    // 1 coord + 1 short (Fill is 27)
    Command(DRAW_TRIANGLE, 0x28),  // 3 coord (Fill is 29)
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