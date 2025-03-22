#ifndef WAVESHAREEPD_H
#define WAVESHAREEPD_H
class WaveshareEPD
{
    public:
        void init(int, int);
    
    private:
        int wakeupPin;
        int resetPin;
};

#endif