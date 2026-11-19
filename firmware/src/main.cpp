#include <Arduino.h>

int loopCount = 0;
volatile int loopDelay = 500;

void setup()
{
  Serial.begin(115200);
  Serial.println("OpenP1Bridge booted!");
}

void loop()
{
  loopCount++;
  Serial.println("OpenP1Bridge booted!" + String(loopCount));
  delay(loopDelay);
}