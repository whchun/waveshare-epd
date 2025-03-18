#include "epd.h"
#include <Arduino.h>

WaveshareEPD::WaveshareEPD(int wakeupPin, int resetPin) //Adafruit_GFX(800, 600), 
    : wakeupPin(wakeupPin), resetPin(resetPin)
{
}

void WaveshareEPD::init()
{
    Serial.begin(115200);
    digitalWrite(wakeupPin, HIGH);
    digitalWrite(resetPin, HIGH);
}