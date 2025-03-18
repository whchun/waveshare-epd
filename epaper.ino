#include "epd.h"

#define WAKEUP_PIN 3
#define RESET_PIN 4
#define LED_PIN 13

WaveshareEPD epd(WAKEUP_PIN, RESET_PIN);

void setup() {
//  pinMode(LED_PIN, OUTPUT);
//  digitalWrite(LED_PIN, LOW);

  epd.init();
}

void loop() {

}
