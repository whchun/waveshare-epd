#include "epd.h"

#define WAKEUP_PIN 3
#define RESET_PIN 4
#define LED_PIN 13

WaveshareEPD epd(WAKEUP_PIN, RESET_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  epd.init();
  epd.wakeup();
  epd.setMemory();
}

void loop() {
  char flag = 0;
  epd.setColor();
  epd.drawCircle(100, 100, 100);
  epd.update();
  epd.sleep();
  while (1)
  {
    if(flag)
    {
      flag = 0;
      digitalWrite(LED_PIN, LOW);
    }
    else
    {
      flag = 1;
      digitalWrite(LED_PIN, HIGH);
    }
    delay(500);
  }
}
