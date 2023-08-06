/* Seven Segment Clock Library
 *  This library extends the Adafruit 7-seg LED library to function as a clock or timer. 
 *  Written by Michael Coney
 *  Created: 3/31/19
 *  Updated: 7/30/23
 * 
 * 
 */
#ifndef SevenSegClock_h
#define SevenSegClock_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class SevenSegClock {
  public:
    SevenSegClock(int DISPLAY_ADDRESS);
    void begin();
    void timeConvert(int total_sec);
    void error();
    void blank();
    void haywire(int duration);
    void setSegDisplay(int minutes, int seconds);
    void runTimer(int secondsToRun, int clockSpeed);
    void clear();
    void countUp();
    void countDown();

  private:
    Adafruit_7segment clockDisplay;
    int _DISPLAY_ADDRESS;
    bool colon = true;
    int countDirection;
    int _currentMinutes;
    int _currentSeconds;
    int _setMinutes;
    int _setSeconds;
    int _totalSeconds;

};

#endif SevenSegClock_h
