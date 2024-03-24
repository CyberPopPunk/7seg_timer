/*
 * TODO:
 * 1. Change Delay to millis()
 * 2. Add numeric timer and clock mode
 */
#include "Arduino.h"
#include "SevenSegClock.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

SevenSegClock::SevenSegClock(int display_address) {
  _DISPLAY_ADDRESS = display_address;
  Adafruit_7segment clockDisplay = Adafruit_7segment();
}

void SevenSegClock::begin() {
  clockDisplay.begin(_DISPLAY_ADDRESS);
  clockDisplay.setBrightness(15);
}

void SevenSegClock::timeConvert(int total_sec) {
  //converts input seconds into minutes and seconds
  Serial.println("Total Seconds Input:");
  Serial.println(total_sec);
  _setMinutes = _totalSeconds / 60;
  _setSeconds = _totalSeconds % 60;
  Serial.print("Set Minutes: ");
  Serial.print(_setMinutes);
  Serial.print("       Set Seconds: ");
  Serial.println(_setSeconds);
}


void SevenSegClock::error() {
  //displays Err. on clock    // writeDigitRaw() bitmask lelgend [B, decimal,mid,top_left,bot_left,bottom, bot_right, top_right, top]
  clockDisplay.writeDigitRaw(0, B01111001);
  clockDisplay.writeDigitRaw(1, B01010000);
  clockDisplay.writeDigitRaw(3, B11010000);
  clockDisplay.writeDigitRaw(4, B00000000);
  colon = false;
  clockDisplay.writeDisplay();
}

void SevenSegClock::haywire(int duration) {
  //makes clock appear to malfunction with random numbers and random timings
  //TODO: - add letters and symbols
  //      - fix timing so it is consistent

  int maxtime = duration;
  while (duration >= 0) {
    Serial.print("Duration: ");
    Serial.println(duration);
    randomSeed(analogRead(0));
    int randomDigits = random(10000);
    clockDisplay.print(randomDigits, DEC);
    if (randomDigits < 1000) {
      clockDisplay.writeDigitNum(0, 0);
      if (randomDigits < 100) {
        clockDisplay.writeDigitNum(1, 0);
      }
      if (randomDigits < 10) {
        clockDisplay.writeDigitNum(2, 0);
      }
    }
    clockDisplay.drawColon(colon);
    clockDisplay.writeDisplay();
    delay(random(200, 666));
    if (duration < maxtime / 2) {
      clear();
      delay(random(25, 80));
      if (random(10) > 4) {
        //clockDisplay.print(0xERR, HEX);
        //colon != colon;
      }
    }
    duration -= 1;
  }
}

void SevenSegClock::setSegDisplay(int minutes, int seconds) {
  colon = true;
  //makes the input time formatted for display (add two 0 spaces to left digits)
  int displayValue = minutes * 100 + seconds;

  clockDisplay.print(displayValue, DEC);
  // Add zero padding when in 24 hour mode and it's midnight pad zeros.
  if (minutes < 10) {
    // Pad hour 0.
    clockDisplay.writeDigitNum(0, 0);
    if (minutes == 0) {
      clockDisplay.writeDigitNum(1, 0);
      // Also pad when the 10's minute is 0 and should be padded.
      if (seconds < 10) {
        clockDisplay.writeDigitNum(3, 0);
      }
    }
  }
  clockDisplay.drawColon(colon);
  clockDisplay.writeDisplay();
  _currentMinutes = minutes;
  _currentSeconds = seconds;
}

void SevenSegClock::runTimer(int secondsToRun, int clockSpeed) {
  colon = true;
  int time_track = secondsToRun;
  while (time_track != 0) {
    //countdown timer that reduces to 0
    // -1 minutes if for keeping track of minutes after both minutes and secs reach 0
    if (_currentMinutes > -1) {
      _currentSeconds -= secondsToRun / abs(secondsToRun);
      if (_currentSeconds < 0) {
        _currentSeconds = 59;
        _currentMinutes -= 1;
      }
      if (_currentSeconds > 59) {
        _currentSeconds = 0;
        _currentMinutes += 1;
      }
    }
    setSegDisplay(_currentMinutes, _currentSeconds);
    delay(clockSpeed);
    time_track = abs(time_track) - 1;
    Serial.print("time left: ");
    Serial.println(time_track);
  }
  clear();
}

void SevenSegClock::blank() {
  //displays blank line on clock    // writeDigitRaw() bitmask lelgend [B, decimal,mid,top_left,bot_left,bottom, bot_right, top_right, top]
  clockDisplay.writeDigitRaw(0, B01000000);
  clockDisplay.writeDigitRaw(1, B01000000);
  clockDisplay.writeDigitRaw(3, B01000000);
  clockDisplay.writeDigitRaw(4, B01000000);
  clockDisplay.writeDisplay();
  colon = true;
}

void SevenSegClock::clear() {
  //Clears the clock display
  clockDisplay.writeDigitRaw(0, B00000000);
  clockDisplay.writeDigitRaw(1, B00000000);
  clockDisplay.writeDigitRaw(3, B00000000);
  clockDisplay.writeDigitRaw(4, B00000000);
  colon = false;
  clockDisplay.writeDisplay();
}

void SevenSegClock::intConvertTime(int inputInt){
  //takes an int input and converts it to minutes/seconds time
  if (inputInt < 0 || inputInt > 5959){
    Serial.print("Error: invalid input - exiting without setting clock");
  }
  int tempMinutes = inputInt/100;
  int tempSeconds = inputInt % 100;

  if (tempSeconds > 59){
    Serial.print("error, time not in ISO8601 format, converting seconds to minutes");
    tempMinutes += 1;
    tempSeconds -= 60;
  }
  setSegDisplay(tempMinutes, tempSeconds);
}