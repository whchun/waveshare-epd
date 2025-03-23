#ifndef EPD_H
#define EPD_H

#include "types.h"
#include "frame.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

class WaveshareEPD
{
    public:
        WaveshareEPD(uint8_t, uint8_t, uint8_t, uint8_t);

        void init();
        void wakeup();
        void reset();

        void test();

    private:
        SoftwareSerial *serial;
        uint8_t wakeupPin;
        uint8_t resetPin;
};
#endif