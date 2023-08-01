/*TODO:
  1. REFINE COUNTDOWN/COUNTUP FOR TIMER
  2. ADD GLITCH FUNCTIONALITY to input parse
  3. Make into Class
  4. refine methods
*/
#include "SevenSegClock.h"

#define DISPLAY_ADDRESS 0x70
int TEST_INPUT = 4499;

SevenSegClock clockObj = SevenSegClock(DISPLAY_ADDRESS);

void setup() {
  Serial.begin(115200);
  clockObj.begin();
}

void loop() {
  /*setSegDisplay(3, 45);
    runTimer(-10, 500);
  */
  clockObj.haywire(TEST_INPUT/1000);


  
  //timeConvert(clock_set_test);
  //setSegDisplay(_minutes, _seconds);
}
