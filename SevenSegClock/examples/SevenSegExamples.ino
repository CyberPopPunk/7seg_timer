#include "SevenSegClock.h"

#define DISPLAY_ADDRESS 0x70
int TEST_INPUT = 4499;

SevenSegClock clockObj = SevenSegClock(DISPLAY_ADDRESS);

void setup() {
  Serial.begin(115200);
  clockObj.begin();
}

void loop() {
  // count up to 12:00 like regular clock
  clockObj.setSegDisplay(11, 55);
  clockObj.runTimer(-5, 3000);

  //countdown from 1 minute very fast
  clockObj.setSegDisplay(1, 0);
  clockObj.runTimer(60, 100);

  //glitch out for 5 seconds
  clockObj.haywire(5);

  //display error
  clockObj.error();
  delay(3000);

  //display blank line
  clockObj.blank();
  delay(3000);
}
