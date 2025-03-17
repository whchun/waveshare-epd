#ifndef EPD_H
#define EPD_H

#define    CMD_SIZE                           512

/*
frame format
*/
#define    FRAME_B                            0xA5
#define    FRAME_E0                           0xCC
#define    FRAME_E1                           0x33
#define    FRAME_E2                           0xC3
#define    FRAME_E3                           0x3C


/*
color define
*/
#define    WHITE                              0x03
#define    GRAY                               0x02
#define    DARK_GRAY                          0x01
#define    BLACK                              0x00

/*
command define
*/
#define    CMD_HANDSHAKE                      0x00
#define    CMD_SET_BAUD                       0x01
#define    CMD_READ_BAUD                      0x02
#define    CMD_MEMORYMODE                     0x07
#define    CMD_STOPMODE                       0x08
#define    CMD_UPDATE                         0x0A
#define    CMD_SCREEN_ROTATION                0x0D
#define    CMD_LOAD_FONT                      0x0E
#define    CMD_LOAD_PIC                       0x0F

#define    CMD_SET_COLOR                      0x10
#define    CMD_SET_EN_FONT                    0x1E

#define    CMD_DRAW_PIXEL                     0x20
#define    CMD_DRAW_LINE                      0x22
#define    CMD_FILL_RECT                      0x24
#define    CMD_DRAW_CIRCLE                    0x26
#define    CMD_FILL_CIRCLE                    0x27
#define    CMD_DRAW_TRIANGLE                  0x28
#define    CMD_FILL_TRIANGLE                  0x29
#define    CMD_CLEAR                          0x2E

#define    CMD_DRAW_STRING                    0x30

#define    CMD_DRAW_BITMAP                    0x70


/*
FONT
*/
#define    GBK32                              0x01
#define    GBK48                              0x02
#define    GBK64                              0x03

#define    ASCII32                            0x01
#define    ASCII48                            0x02
#define    ASCII64                            0x03



/*
Memory Mode
*/
#define    MEM_NAND                           0
#define    MEM_TF                             1

/*
set screen rotation
*/
#define    EPD_NORMAL                         0
#define    EPD_INVERSION                      1

class WaveshareEPD
{
    public:
        WaveshareEPD();
        ~WaveshareEPD();
};

#endif