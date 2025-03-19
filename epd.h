#ifndef EPD_H
#define EPD_H

// #include <Adafruit_GFX.h>

// https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module

// #define    CMD_SIZE                           512
#define CMD_SIZE 1033

// Commands
#define CMD_HANDSHAKE [0x00, 0x09, 0x00]
#define CMD_SET_BAUD [0x00, 0x0D, 0x01]
#define CMD_READ_BAUD [0x00, 0x09, 0x02]
#define CMD_MEMORYMODE [0x00, 0x0A, 0x07]
#define CMD_STOPMODE [0x00, 0x09, 0x08]
#define CMD_UPDATE [0x00, 0x09, 0x0A]
// #define CMD_SCREEN_ROTATION                0x0D
// #define CMD_LOAD_FONT                      0x0E
// #define CMD_LOAD_PIC                       0x0F

#define CMD_DRAW_FILLRECTANGLE [0x00, 0x11, 0x24]
#define CMD_DRAW_RECTANGLE [0x00, 0x11, 0x25]

#define FRAME_HEADER 0xA5
#define FRAME_END [0xCC, 0x33, 0xC3, 0x3C]

class WaveshareEPD //: public Adafruit_GFX
{
    public:
        WaveshareEPD(int wakeupPin, int resetPin);
        ~WaveshareEPD();

        void init();
        void wakeup();
        void update();
        void sleep();

        void setMemory();
        void setColor(); // Update param
        void drawCircle(int x0, int y0, int r);
    
    private:
        int wakeupPin;
        int resetPin;

        unsigned char getParityByte(unsigned char *);
        void writeSerialPort(unsigned char *);

};

#endif;