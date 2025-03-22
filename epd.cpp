#include "epd.h"
#include <Arduino.h>


void WaveshareEPD::init(int wakeupPin, int resetPin)
{
    Serial.begin(115200);
    resetPin = resetPin;
    wakeupPin = wakeupPin;
    // digitalWrite(wakeupPin, HIGH);
    // digitalWrite(resetPin, HIGH);

    Serial.println("INIT");
}